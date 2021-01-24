#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    um(new UManager)
{
    ui->setupUi(this);
    ui->userTableWidget->clear();
    MainWindow::setWindowTitle("UManager");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete itemUser;

}

void MainWindow::showTable(){
    ui->userTableWidget->setRowCount(um->getRowCount());
    if(!um->getRowCount()){
        return;
    }
    ListType::iterator rowIterator = um->cBegin();
    int columCount = um->cBegin()->size();
    int i = 0;

    while (rowIterator != um->cEnd()) {
      auto tempIter = rowIterator->cbegin();
      for (int j = 0; j < columCount; ++j) {
          itemUser = new QTableWidgetItem;
          itemUser->setText(*tempIter);
          ui->userTableWidget->setItem(i,j,itemUser);
          tempIter++;
      }
      rowIterator++;
      i++;
    }
}

void MainWindow::find_(const QString &str){


    if(str.length() == 0){
         showTable();
         return;
     }
     ui->userTableWidget->setColumnCount(um->getColumCount());
     ui->userTableWidget->setRowCount(0);
     int rowcount = 1;
     ListType::iterator rowIterator = um->cBegin();
     int i = 0;
     while (rowIterator != um->cEnd()){
       auto tempIter = rowIterator->begin();
       if(tempIter->toLower().contains(str.toLower())){
           ui->userTableWidget->setRowCount(rowcount);
           rowcount++;
           for (int j = 0; j < um->getColumCount(); ++j) {
               itemUser = new QTableWidgetItem;
               itemUser->setText(*tempIter);
               ui->userTableWidget->setItem(i,j,itemUser);
               tempIter++;
           }
           i++;
       }
       rowIterator++;
     }
}

void MainWindow::on_findButton_clicked()
{
    QString search_value = ui->findLineEdit->text();
    find_(search_value);
}

void MainWindow::on_actionExit_triggered()
{
    exit(1);
}

void MainWindow::on_actionOpen_json_triggered()
{
    QString FileDir = QFileDialog::getOpenFileName(this,"Open Json File",QString(),"*json");
       if(FileDir.isEmpty()){ // Try Catch
           return;
    }
    if(um->LoadJson(FileDir)){
        ui->userTableWidget->clear();
        ui->userTableWidget->setColumnCount(um->getColumCount());
        ui->userTableWidget->setHorizontalHeaderLabels(um->getRowsName());
        showTable();
    }
}
