#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

namespace {

QString resolveRulesPath()
{
    const QString appDirRules =
        QDir(QCoreApplication::applicationDirPath()).filePath("rules.json");
    if (QFileInfo::exists(appDirRules))
        return appDirRules;

    return QStringLiteral(TOXIN_RULES_PATH);
}

} // namespace

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(resolveRulesPath());
    w.show();
    return a.exec();
}
