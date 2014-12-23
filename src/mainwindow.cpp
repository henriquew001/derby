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
    if (QFile::exists(userDir.absolutePath() + "/derbycurrent.sqlite")) QFile::remove(userDir.absolutePath() + "/derbycurrent.sqlite");
    QFile::copy(userDir.absolutePath() + "/definitions.sqlite", userDir.absolutePath() + "/derbycurrent.sqlite");
    db.setDatabaseName(userDir.absolutePath() + "/derbycurrent.sqlite");

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
    ui->countryCB->setModel(getdDefinitionsList("SELECT NationName" + qApp->property("gameLanguage").toString() +" FROM Associations"));
    emit setStackedWidgetIndex(1);
}

void MainWindow::startPage() {
    emit setStackedWidgetIndex(0);
}

void MainWindow::fillLeagueCB() {
    QString querydef = "SELECT LeagueName FROM Associations INNER JOIN Leagues ON Associations.NationID = Leagues.LeagueAssociation WHERE NationName" + qApp->property("gameLanguage").toString() +" = \"" + ui->countryCB->currentText() + "\"";
    ui->leagueCB->setModel(getdDefinitionsList(querydef));
    ui->startLeagueCB->setModel(getdDefinitionsList(querydef));
}

void MainWindow::updateTeamList() {
    QString querydef = "SELECT TeamName, Logo FROM Leagues INNER JOIN Teams ON Leagues.LeagueID = Teams.League WHERE Leagues.LeagueName = \"" + ui->leagueCB->currentText() + "\"";
    DefinitionsQSqlQueryModel* dbModel = new DefinitionsQSqlQueryModel();
    dbModel->setQuery(querydef);
    ui->teamListView->setModel(dbModel);
}

void MainWindow::addGamester(){

}

void MainWindow::removeGamester(){

}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
}
