#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemWatcher>
#include <QMainWindow>
#include <QTimer>

#include "kanaconverter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &rulesPath, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    KanaConverter converter;
    QFileSystemWatcher rulesWatcher;
    QTimer reloadTimer;

    void updateComposition();
    void updateModeUi();
    void watchRulesFile();

private slots:
    void updateKana();
    void switchMode();
    void reloadRules();
};
#endif // MAINWINDOW_H
