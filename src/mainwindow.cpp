#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newLocalGame() {
    emit setStackedWidgetIndex(1);
}

void MainWindow::startPage() {
    emit setStackedWidgetIndex(0);
}
