#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileInfo>

namespace {

QString modeText(InputMode mode)
{
    return mode == InputMode::Katakana ? QObject::tr("片假名") : QObject::tr("平假名");
}

} // namespace

MainWindow::MainWindow(const QString &rulesPath, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , converter(rulesPath)
{
    ui->setupUi(this);
    ui->inputEdit->setPlaceholderText(tr("输入 romaji，例如 ka / ki / ku"));
    ui->commitLabel->setText(QString());
    ui->preeditLabel->setText(QString());
    ui->modeButton->setText(tr("切换到片假名"));
    ui->rulesPathLabel->setText(QDir::toNativeSeparators(rulesPath));
    reloadTimer.setInterval(150);
    reloadTimer.setSingleShot(true);

    connect(ui->inputEdit, &QLineEdit::textChanged,
            this, &MainWindow::updateKana);
    connect(ui->modeButton, &QPushButton::clicked,
            this, &MainWindow::switchMode);
    connect(&rulesWatcher, &QFileSystemWatcher::fileChanged,
            this, [this] { reloadTimer.start(); });
    connect(&rulesWatcher, &QFileSystemWatcher::directoryChanged,
            this, [this] { reloadTimer.start(); });
    connect(&reloadTimer, &QTimer::timeout,
            this, &MainWindow::reloadRules);

    watchRulesFile();
    updateModeUi();
    updateComposition();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateKana()
{
    updateComposition();
}

void MainWindow::switchMode()
{
    if (converter.currentMode() == InputMode::Hiragana)
        converter.setMode(InputMode::Katakana);
    else
        converter.setMode(InputMode::Hiragana);

    updateModeUi();
    updateComposition();
}

void MainWindow::reloadRules()
{
    watchRulesFile();

    if (converter.reload())
    {
        statusBar()->showMessage(tr("rules.json 已重新加载"), 2000);
        updateModeUi();
        updateComposition();
        return;
    }

    statusBar()->showMessage(tr("rules.json 重载失败，继续使用当前规则"), 3000);
}

void MainWindow::updateComposition()
{
    const KanaConverter::Composition composition =
        converter.compose(ui->inputEdit->text());

    ui->commitLabel->setText(composition.commit);
    ui->preeditLabel->setText(composition.preedit);
}

void MainWindow::updateModeUi()
{
    const bool isKatakana = converter.currentMode() == InputMode::Katakana;

    ui->modeValueLabel->setText(modeText(converter.currentMode()));
    ui->modeButton->setText(
        isKatakana ? tr("切换到平假名") : tr("切换到片假名"));
    statusBar()->showMessage(
        tr("当前输入模式：%1").arg(modeText(converter.currentMode())), 2000);
}

void MainWindow::watchRulesFile()
{
    const QString path = converter.rulesPath();
    const QFileInfo info(path);
    const QString absolutePath = info.absoluteFilePath();
    const QString absoluteDir = info.absolutePath();

    rulesWatcher.removePaths(rulesWatcher.files());
    rulesWatcher.removePaths(rulesWatcher.directories());

    if (QFileInfo::exists(absolutePath))
        rulesWatcher.addPath(absolutePath);

    if (QDir(absoluteDir).exists())
        rulesWatcher.addPath(absoluteDir);
}
