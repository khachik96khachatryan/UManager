#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "umanager.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showTable();
    void find_(const QString& str);
private slots:
    void on_findButton_clicked();

    void on_actionExit_triggered();

    void on_actionOpen_json_triggered();

private:
    Ui::MainWindow *ui;
    UManager       *um;
    QTableWidgetItem    *itemUser;
};

#endif // MAINWINDOW_H
