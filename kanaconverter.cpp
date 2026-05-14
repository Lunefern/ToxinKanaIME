#include <QFile>
#include <QJsonValue>
#include <QJsonArray>
#include "kanaconverter.h"

KanaConverter::KanaConverter(const QString& jsonPath)
{
    cachedMaxLen = 1;
    loadFromJson(jsonPath);
}

void KanaConverter::loadFromJson(const QString& path)
{
    updateMaxKeyLength();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();

    QString defaultMode = root["default_mode"].toString();

    if (defaultMode == "katakana")
        mode = InputMode::Katakana;
    else
        mode = InputMode::Hiragana;

    QJsonArray rules = root["rules"].toArray();

    for (const auto& r : rules)
    {
        QJsonObject obj = r.toObject();

        QString in = obj["in"].toString();
        QJsonObject out = obj["out"].toObject();

        Rule rule;
        rule.hiragana = out["hiragana"].toString();
        rule.katakana = out["katakana"].toString();

        table[in] = rule;
    }
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