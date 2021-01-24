#include "umanager.h"

UManager::UManager()
{
    rowNameList<<"Name"<<"Lastname"<<"Age"<<"Address";
}

int UManager::getColumCount(){
    if(userList.empty())
        return 0;

    return (userList.cbegin()->size());
}

int UManager::getRowCount(){

    if(userList.empty())
        return 0;
    return userList.size();
}

const QStringList& UManager::getRowsName() const{
    return this->rowNameList;
}

const ListType::iterator UManager::cBegin(){
   return userList.cbegin();
}


const ListType::iterator UManager::cEnd(){
   return userList.end();
}

bool UManager::LoadJson(const QString& dir){

    QFile jsonFile(dir);

    if(!jsonFile.open(QIODevice::ReadOnly)){ // Try Catch
        QMessageBox::critical(0,"Json file not selected","please select a file");
          return false;

       }
       QByteArray saveData = jsonFile.readAll();
       jsonFile.close();
       QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
       this->jsonObject = jsonDocument.object();
       if(this->jsonObject.empty())
       {
           QMessageBox::critical(0,"Json file Error","File does not match\nOr Json syntax error ");
           return false;
       }
       Json_to_Stl_Set();
       return true;
}

void UManager::Json_to_Stl_Set(){

      QList<QVariant> List_ = jsonObject.toVariantMap()["users"].toList();
      if(List_.empty())
      {
          QMessageBox::warning(0,"File has no users attribute  ","Please check the file");
          return;
      }
      QList<QVariant>::iterator begin_iter = List_.begin();
      QVector<QString> temp_vector;
      userList.clear();

      while (begin_iter != List_.end()) {
          QMap<QString,QVariant> tempIter = begin_iter->toMap();
          if(tempIter["username"].toString().length() > 0){
              temp_vector.push_back(tempIter["username"].toString());
              temp_vector.push_back(tempIter["lastname"].toString());
              temp_vector.push_back(QString::number(tempIter["age"].toInt()));
              temp_vector.push_back(tempIter["address"].toString());
              userList.insert(temp_vector);
              temp_vector.clear();
          }
          begin_iter++;
     }
}
