#ifndef KANACONVERTER_H
#define KANACONVERTER_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include "inputmode.h"

class KanaConverter
{
public:
    struct Composition {
        QString commit;
        QString preedit;
    };

    KanaConverter(const QString& jsonPath);

    QString convert(const QString& text);
    Composition compose(const QString& text);

    bool reload();
    InputMode currentMode() const;
    InputMode defaultMode() const;
    QString rulesPath() const;

    void setMode(InputMode mode);

    void pushChar(QChar c);

    QString preedit() const;
    QString commit();

    void clear();

private:
    struct Rule {
        QString hiragana;
        QString katakana;
    };

    QString jsonPath;
    QMap<QString, Rule> table;

    InputMode mode;
    InputMode defaultInputMode;

    QString buffer;
    QString commitText;

    bool loadFromJson(const QString& path);
    void processBuffer();
    void updateMaxKeyLength();

    int computeMaxKeyLength() const;
    int maxKeyLength() const;
    int cachedMaxLen;
};

#endif
