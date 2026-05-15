#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <utility>
#include "kanaconverter.h"

KanaConverter::KanaConverter(const QString& jsonPath)
    : jsonPath(jsonPath)
    , mode(InputMode::Hiragana)
    , defaultInputMode(InputMode::Hiragana)
    , cachedMaxLen(1)
{
    if (loadFromJson(jsonPath))
        mode = defaultInputMode;
}

bool KanaConverter::loadFromJson(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject())
        return false;

    QJsonObject root = doc.object();

    QString defaultMode = root["default_mode"].toString();
    InputMode loadedDefaultMode = InputMode::Hiragana;

    if (defaultMode == "katakana")
        loadedDefaultMode = InputMode::Katakana;

    QMap<QString, Rule> newTable;

    QJsonArray rules = root["rules"].toArray();

    for (const auto& r : rules)
    {
        QJsonObject obj = r.toObject();

        QString in = obj["in"].toString();
        QJsonObject out = obj["out"].toObject();

        Rule rule;
        rule.hiragana = out["hiragana"].toString();
        rule.katakana = out["katakana"].toString();

        if (!in.isEmpty())
            newTable[in] = rule;
    }

    table = std::move(newTable);
    defaultInputMode = loadedDefaultMode;
    updateMaxKeyLength();
    if (table.isEmpty())
        cachedMaxLen = 1;

    return true;
}

bool KanaConverter::reload()
{
    const InputMode preservedMode = mode;
    const bool loaded = loadFromJson(jsonPath);
    if (loaded)
        mode = preservedMode;

    return loaded;
}

QString KanaConverter::convert(const QString& text)
{
    const Composition composition = compose(text);
    return composition.commit + composition.preedit;
}

KanaConverter::Composition KanaConverter::compose(const QString& text)
{
    clear();

    for (const QChar c : text)
        pushChar(c);

    Composition composition{commitText, buffer};
    clear();
    return composition;
}

InputMode KanaConverter::currentMode() const
{
    return mode;
}

InputMode KanaConverter::defaultMode() const
{
    return defaultInputMode;
}

QString KanaConverter::rulesPath() const
{
    return jsonPath;
}

void KanaConverter::setMode(InputMode newMode)
{
    mode = newMode;
}

void KanaConverter::pushChar(QChar c)
{
    buffer += c;
    processBuffer();
}

void KanaConverter::processBuffer()
{
    int i = 0;
    QString result;

    while (i < buffer.length())
    {
        QString match;
        QString out;
        bool found = false;

        int maxLen = cachedMaxLen;

        for (int len = maxLen; len >= 1; len--)
        {
            if (i + len > buffer.length())
                continue;

            QString sub = buffer.mid(i, len);

            if (table.contains(sub))
            {
                match = sub;

                const Rule& rule = table[sub];

                out = (mode == InputMode::Hiragana)
                          ? rule.hiragana
                          : rule.katakana;

                found = true;
                break;
            }
        }

        if (found)
        {
            result += out;
            i += match.length();
        }
        else
        {
            // ❗关键：保留未确定输入（例如 k / n / t）
            break;
        }
    }

    // 已确认输出
    commitText += result;

    // 未处理部分 = preedit
    buffer = buffer.mid(i);
}

QString KanaConverter::preedit() const
{
    return buffer;
}

QString KanaConverter::commit()
{
    QString out = commitText;
    commitText.clear();
    return out;
}

void KanaConverter::clear()
{
    buffer.clear();
    commitText.clear();
}

int KanaConverter::computeMaxKeyLength() const
{
    int maxLen = 1;

    for (auto it = table.begin(); it != table.end(); ++it)
    {
        maxLen = qMax(maxLen, it.key().length());
    }

    return maxLen;
}

void KanaConverter::updateMaxKeyLength()
{
    cachedMaxLen = computeMaxKeyLength();
}

int KanaConverter::maxKeyLength() const
{
    return cachedMaxLen;
}
