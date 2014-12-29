#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "definitionsdb.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QSqlRelationalDelegate>
#include <QListIterator>

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

    // initialize the database - Need to change dir
    QSqlError err = connectDefinitionsDb(userDir.absolutePath() + "/definitions.sqlite");
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
    // initialize the database
    QSqlError err = connectGameDb(userDir.absolutePath() + "/derbycurrent.sqlite");
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }
    QSqlDatabase m_GameDB = QSqlDatabase::database("Game");
    m_GameTableModel = new QSqlRelationalTableModel(ui->gamesterTableView, m_GameDB);
    m_GameTableModel->setTable("Gamester");
    m_GameTableModel->select();

    ui->gamesterTableView->setModel(m_GameTableModel);
    ui->gamesterTableView->setItemDelegate(new QSqlRelationalDelegate(ui->gamesterTableView));
    ui->gamesterTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->gamesterTableView->hideColumn(0);

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
    QString querydef = "SELECT TeamName, Logo, TeamID FROM Leagues INNER JOIN Teams ON Leagues.LeagueID = Teams.League WHERE Leagues.LeagueName = \"" + ui->leagueCB->currentText() + "\"";
    DefinitionsQSqlQueryModel* dbModel = new DefinitionsQSqlQueryModel();
    dbModel->setQuery(querydef);
    ui->teamListView->setModel(dbModel);
    qDebug() << m_GameTableModel->rowCount();
    for (int i=0; i<m_GameTableModel->rowCount(); i++){
        QString selteam = m_GameTableModel->data(m_GameTableModel->index(i, 2), Qt::DisplayRole).toString();
        for (int j=0; j < dbModel->rowCount(); j++){
            QString str = dbModel->data(dbModel->index(j,0), Qt::DisplayRole).toString();
            if (str == selteam) ui->teamListView->setRowHidden(j,true);
            //qDebug() << selteam << str;
        }
    }
    //ui->teamListView->verticalScrollBar()->setSliderPosition(1);
}

void MainWindow::addGamester(){
    QModelIndex mi = ui->teamListView->currentIndex();

    if (mi.isValid()){
        if (ui->gamesterLE->text().isEmpty()) return;
        QSqlRecord record;

        QSqlField nameField(QStringLiteral("GamesterName"), QVariant::String);
        nameField.setValue(ui->gamesterLE->text());
        record.append(nameField);

        QSqlField teamField(QStringLiteral("GamesterTeam"), QVariant::String);
        teamField.setValue(mi.data().toString());
        record.append(teamField);

        QSqlField startLeagueField(QStringLiteral("StartLeague"), QVariant::String);
        startLeagueField.setValue(ui->startLeagueCB->currentText());
        record.append(startLeagueField);

        const bool ok = m_GameTableModel->insertRecord(-1, record);
        if (!ok) {
            qDebug() << m_GameTableModel->lastError();
            return;
        }
        ui->teamListView->setRowHidden(mi.row(), true);
    }
    ui->gamesterLE->setText("");
}

void MainWindow::removeGamester(){
    QModelIndex mi = ui->gamesterTableView->currentIndex();
    for (int i=0; i<m_GameTableModel->rowCount(); i++){
        QString selteam = m_GameTableModel->data(m_GameTableModel->index(i, 2), Qt::DisplayRole).toString();
        for (int j=0; j < ui->teamListView->model()->rowCount(); j++){
            QString str = ui->teamListView->model()->data(ui->teamListView->model()->index(j,0), Qt::DisplayRole).toString();
            if (str == selteam) ui->teamListView->setRowHidden(j,false);
        }
    }
    m_GameTableModel->removeRow(mi.row());
    ui->gamesterTableView->hideRow(mi.row());
}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
}
