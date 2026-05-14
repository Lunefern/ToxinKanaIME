#ifndef KANACONVERTER_H
#define KANACONVERTER_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include "inputmode.h"

class KanaConverter
{
public:
    KanaConverter(const QString& jsonPath);

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

    QMap<QString, Rule> table;

    InputMode mode;

    QString buffer;
    QString preeditText;
    QString commitText;

    void loadFromJson(const QString& path);
    void processBuffer();
    void updateMaxKeyLength();

    int computeMaxKeyLength() const;
    int maxKeyLength() const;
    int cachedMaxLen;
};

#endif