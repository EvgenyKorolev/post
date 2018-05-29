#ifndef MY_MODEL_H
#define MY_MODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QVariant>
#include <QList>
#include <memory>
#include "proxy_in.h"

class my_model_in : public QAbstractTableModel
{
public:
    my_model_in(proxy_in* arg, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    proxy_in* _model_data;
};

#endif // MY_MODEL_H
