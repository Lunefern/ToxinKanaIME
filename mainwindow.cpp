#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->inputEdit, &QLineEdit::textChanged,
            this, &MainWindow::updateKana);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateKana()
{
    QString text = ui->inputEdit->text();

    ui->outputLabel->setText(
        converter.convert(text)
        );
}
