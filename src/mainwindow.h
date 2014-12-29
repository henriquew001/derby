#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtCore/QDir>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString participantName;
    QDir userDir;
    QSqlDatabase m_GameDB;
    QSqlRelationalTableModel *m_GameTableModel;
    void showError(const QSqlError &err);

private slots:
    void newLocalGame();
    void startPage();
    void fillLeagueCB();
    void updateTeamList();
    void addGamester();
    void removeGamester();
    
signals:
    void setStackedWidgetIndex(int);
};

#endif // MAINWINDOW_H
