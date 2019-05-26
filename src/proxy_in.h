#ifndef PROXY_IN_H
#define PROXY_IN_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDate>
#include <QDateTime>
#include <QString>
#include <QList>
#include <QByteArray>
#include "items_fabrica.h"
#include "letter_in.h"
#include "doc_image.h"
#include "declaration.h"
#include "functions.h"

class proxy_in
{
public:
    explicit proxy_in(QSqlDatabase *arg);
    ~proxy_in();
    int size() const;
    int count() const;
    letter_in at(int arg) const;
    void append(letter_in* arg);
    void insert(int row, letter_in* arg);
private:
    QSqlDatabase _dbw;
};

#endif // PROXY_IN_H
