#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

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

private slots:
    void newLocalGame();
    void startPage();

signals:
    void setStackedWidgetIndex(int);
};

#endif // MAINWINDOW_H
