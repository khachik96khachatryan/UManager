#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadJson("/home/linux/Documents/TextPars/Users.json");
    read();
    showWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
   exit(1);
}

void MainWindow::LoadJson(const QString &dir){
    QFile jsonFile(dir);
    if(!jsonFile.open(QIODevice::ReadOnly)){ // Try Catch
        /*int checkCode = criticalMsgBox_("file not found","please select a file or file does not match ");
        if(checkCode == QMessageBox :: Yes){
            MainWindow::on_actionOpen_file_json_triggered();
        }else if(checkCode == QMessageBox ::No){
            exit(1);
        }else{
            exit(0);
        }*/
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

void MainWindow::on_actionOpen_file_json_triggered()
{
    QString FileDir = QFileDialog::getOpenFileName(this,"Open Json File",QString(),"*json");
    if(FileDir.isEmpty()){ // Try Catch
       /*int checkCode = criticalMsgBox_("file not found","please select a file or file does not match ");

        if(checkCode == QMessageBox :: Yes){
            MainWindow::on_actionOpen_file_json_triggered();
        }else if(checkCode == QMessageBox ::No){
            exit(1);
        }else{
            exit(0);
        }**/
    }
    LoadJson(FileDir);
    read();
    showWidget();
}

void MainWindow::on_actionExit_triggered()
{
        exit(1);
}
