#ifndef UMANAGER_H
#define UMANAGER_H


#include "project_global.h"

class UManager
{

public:
    UManager();

    bool LoadJson(const QString& dir);

    int getColumCount();
    int getRowCount();
    const QStringList& getRowsName()const;

    const ListType::iterator cBegin();
    const ListType::iterator cEnd();
private:
    void Json_to_Stl_Set();

    QJsonObject     jsonObject;
    std::multiset<QVector<QString>> userList;
    QStringList     rowNameList;
};

#endif // UMANAGER_H
