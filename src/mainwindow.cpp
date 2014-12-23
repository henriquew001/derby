#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "definitionsdb.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    userDir.setPath(QDir::homePath() + "/.config/derby");
    if (!userDir.exists())
        userDir.mkpath(userDir.absolutePath());

    ui->setupUi(this);

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(this, "Unable to load database", "Derby needs the SQLITE driver");


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // Need to change to install definitions dir
    db.setDatabaseName(userDir.absolutePath() + "/definitions.sqlite");

    // initialize the database
    QSqlError err = connectDefinitionsDb(userDir);
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newLocalGame() {
    ui->countryCB->setModel(getdDefinitionsList("SELECT NationNameEN FROM Associations"));

    emit setStackedWidgetIndex(1);
}

void MainWindow::startPage() {
    emit setStackedWidgetIndex(0);
}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
}
