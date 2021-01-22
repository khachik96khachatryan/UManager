#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadJson(const QString &dir){
    QFile jsonFile(dir);
    if(!jsonFile.open(QIODevice::ReadOnly)){ // Try Catch
      int check = QMessageBox::critical(0,"Json Error","@ntrel nor json file?",QMessageBox::Cancel| QMessageBox::Yes);

      if(check == QMessageBox::Yes){
          MainWindow::on_actionOpen_file_json_triggered();
          return;
      }
    }
    QByteArray saveData = jsonFile.readAll();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
    jsonObject.erase(jsonObject.begin());
    this->jsonObject = jsonDocument.object();
}

void MainWindow::read(){

    QList<QVariant> List_ = jsonObject.toVariantMap()["users"].toList();

      QList<QVariant>::iterator beg = List_.begin();
      QVector<QString> vec;
      userList.clear();
      while (beg != List_.end()) {
          QMap<QString,QVariant> t = beg->toMap();
          vec.push_back(t["username"].toString());
          vec.push_back(t["lastname"].toString());
          vec.push_back(QString::number(t["age"].toInt()));
          vec.push_back(t["address"].toString());
          userList.insert(vec);
          vec.clear();
          beg++;
     }
  }

void MainWindow::showWidget(){

    ui->userTableWidget->clear();
    ui->userTableWidget->setColumnCount(userList.begin()->size());
    ui->userTableWidget->setRowCount(userList.size());

    auto rowIterator = userList.begin();
    int col = userList.begin()->size();
    int i = 0;

    while (rowIterator != userList.end()) {
      auto t = rowIterator->begin();
      for (int j = 0; j < col; ++j) {
          itemUser = new QTableWidgetItem;
          itemUser->setText(*t);
          ui->userTableWidget->setItem(i,j,itemUser);
          t++;
      }
      rowIterator++;
      i++;
    }
}

void MainWindow::find_(const QString &str){

    if(str.length() == 0){
        showWidget();
        return;
    }
    ui->userTableWidget->setColumnCount(userList.begin()->size());
    ui->userTableWidget->setRowCount(0);
    int rowcount = 1;
    auto rowIterator = userList.begin();
    int col = userList.begin()->size();
    int i = 0;
    while (rowIterator != userList.end()){
      auto t = rowIterator->begin();
      if(t->toLower().contains(str.toLower())){
          ui->userTableWidget->setRowCount(rowcount);
          rowcount++;
          for (int j = 0; j < col; ++j) {
              itemUser = new QTableWidgetItem;
              itemUser->setText(*t);
              qDebug()<<"Cout = "<<rowcount;
              ui->userTableWidget->setItem(i,j,itemUser);
              t++;
          }
          i++;
      }
      rowIterator++;
    }

    qDebug()<<"Cout = "<<rowcount;
}


void MainWindow::on_actionOpen_file_json_triggered()
{
    QString FileDir = QFileDialog::getOpenFileName(this,"Open Json File",QString(),"*json");
    if(FileDir.isEmpty()){ // Try Catch
        return;
    }
    show_project(FileDir);
}

void MainWindow::show_project(const QString& dir){
    LoadJson(dir);
    read();
    showWidget();
}

void MainWindow::on_actionExit_triggered()
{
        exit(1);
}

void MainWindow::on_findButton_clicked()
{
    const QString str = ui->findLineEdit->text();
    ui->userTableWidget->clear();
    find_(str);

}
