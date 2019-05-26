#ifndef PROXY_OUT_H
#define PROXY_OUT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDate>
#include <QDateTime>
#include <QString>
#include <QByteArray>
#include "items_fabrica.h"
#include "letter_out.h"
#include "doc_image.h"
#include "functions.h"

class proxy_out
{
public:
    explicit proxy_out(QSqlDatabase *arg);
    ~proxy_out();
    int size() const;
    int count() const;
    letter_out at(int arg) const;
    void append(letter_out* arg);
    void insert(int row, letter_out* arg);
private:
    QSqlDatabase _dbw;
};

#endif // PROXY_OUT_H
