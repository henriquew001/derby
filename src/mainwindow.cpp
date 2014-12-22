#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSql/QSqlDatabase>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(this, "Unable to load database", "This demo needs the SQLITE driver");

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
