#ifndef PROJECT_GLOBAL_H
#define PROJECT_GLOBAL_H
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <memory>
#include <QDebug>
#include <QList>
#include <QTableWidgetItem>
#include <set>
#include <vector>

#include <QMessageBox>


/*
int criticalMsgBox_(const QString& heading,const QString& message){
    QMessageBox msgBox;
    msgBox.critical(nullptr,heading,message);
    return 1;
}

int criticalMsgBox_(const QString& heading,const QString& message){
    QMessageBox msgBox;
    int n = msgBox.critical(nullptr,heading,message,QMessageBox::Yes | QMessageBox::No);

    return n;
}*/


#endif // PROJECT_GLOBAL_H
