#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "project_global.h"
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
    void LoadJson(const QString& dir);

    void read();

    void showWidget();

private slots:
    void on_exitButton_clicked();
    void on_actionOpen_file_json_triggered();
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    std::multiset<QVector<QString>> userList;
    QTableWidgetItem    *itemUser;
    QJsonObject     jsonObject;
};

#endif // MAINWINDOW_H
