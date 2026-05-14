#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    KanaConverter converter;

private slots:
    void updateKana();
};
#endif // MAINWINDOW_H
