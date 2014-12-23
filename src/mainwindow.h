#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtCore/QDir>

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
    void showError(const QSqlError &err);

private slots:
    void newLocalGame();
    void startPage();

signals:
    void setStackedWidgetIndex(int);
};

#endif // MAINWINDOW_H
