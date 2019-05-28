#include "proxy_out.h"

#include <QObject>

proxy_out::proxy_out(QSqlDatabase *arg)
{
    _dbw = *arg;
}
proxy_out::~proxy_out()
{
    _dbw.close();
}
int proxy_out::size() const
{
    return this->count();
}
int proxy_out::count() const
{
    QSqlQuery query(_dbw);
    query.exec("SELECT inq FROM out_data;");
    if (query.last()){
        QSqlRecord rec = query.record();
        return query.value(rec.indexOf("inq")).toInt();
    }
    return 0;
}
letter_out proxy_out::at(int arg) const
{
    ++arg;
    letter_out ret;
    QSqlQuery query(_dbw);
    QSqlRecord rec;
    if (!query.exec("SELECT * FROM out_data WHERE inq = '" + QString::number(arg) + "';")){
         QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("Что-то не то с чтением базы данных data.db3"));
    }
    query.first();
    rec = query.record();
    QDateTime sys_dat;
    sys_dat.setMSecsSinceEpoch(query.value(rec.indexOf("sys_data")).value<qint64>());
    ret.set_doc_out_number(my::base64_minus(query.value(rec.indexOf("doc_out_number")).toString()));
    ret.set_send_rec(my::base64_minus(query.value(rec.indexOf("send_rec")).toString()));
    ret.set_content(my::base64_minus(query.value(rec.indexOf("content")).toString()));
    ret.set_worker(my::base64_minus(query.value(rec.indexOf("worker")).toString()));
    ret.set_inv(query.value(rec.indexOf("label_uniq")).toString());
    ret.set_sys_data(sys_dat.date());
    ret.set_blank_number(my::base64_minus(query.value(rec.indexOf("blank_number")).toString()));
    ret.set_notice(my::base64_minus(query.value(rec.indexOf("notice")).toString()));
    if (query.value(rec.indexOf("fix")).toString() == "true"){ret.set_fix();}
    if (!query.exec("SELECT * FROM out_foto WHERE label_uniq = '" + ret.get_inv() + "';")){
        QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("Что-то не то с чтением базы данных data.db3"));
   }
    rec = query.record();
    while (query.next()){
        doc_image* tmp = new doc_image(img_status::out_foto);
        tmp->set_adr(my::base64_minus(query.value(rec.indexOf("adr_str")).toString()));
        tmp->set_uniq(query.value(rec.indexOf("uniq_str")).toString());
        tmp->set_number_doc(query.value(rec.indexOf("label_uniq")).toString());
        ret.add_images(tmp);
    }
    return ret;
}
void proxy_out::append(letter_out* arg)
{
    QSqlQuery query(_dbw);
    QString fix;
    if (arg->is_fix()){fix = "true";} else {fix = "false";}
    QDateTime sys_dat(arg->get_sys_data());
    if (!query.exec("INSERT INTO out_data(doc_out_number, send_rec, content, worker, sys_data, fix, blank_number, notice, label_uniq) VALUES ('" +
                    my::base64_plus(arg->get_doc_out_number()) + "', '" + my::base64_plus(arg->get_send_rec()) + "', '" + my::base64_plus(arg->get_content()) + "', '" +
                    my::base64_plus(arg->get_worker()) + "', '" + QString::number(sys_dat.toMSecsSinceEpoch()) + "', '" +
                    fix + "', '" + my::base64_plus(arg->get_blank_number()) + "', '"  + my::base64_plus(arg->get_notice()) + "', '" + arg->get_inv() + "');")){
        QMessageBox::information(nullptr, QObject::tr("Внимание"),
                                 QObject::tr("Что-то не то с добавлением записи в базу данных. <br> Возможно не уникальный номер входящего документа или бланка"));
    }
}
void proxy_out::insert(int row, letter_out* arg)
{
    QSqlQuery query(_dbw);
    QString fix;
    if (arg->is_fix()){fix = "true";} else {fix = "false";}
    QDateTime sys_dat(arg->get_sys_data());
    if (!query.exec("UPDATE out_data SET doc_out_number = '" + my::base64_plus(arg->get_doc_out_number()) + "', send_rec = '" +
                    my::base64_plus(arg->get_send_rec()) + "', content = '" + my::base64_plus(arg->get_content()) + "', worker = '" +
                    my::base64_plus(arg->get_worker()) + "', sys_data = '" + QString::number(sys_dat.toMSecsSinceEpoch()) + "', fix = '" +
                    fix + "', blank_number = '" + my::base64_plus(arg->get_blank_number()) + "', notice = '" +
                    my::base64_plus(arg->get_notice()) + "', label_uniq = '" + arg->get_inv() + "' WHERE inq = '" + QString::number(row + 1) + "';")) {
        QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("Что-то не то с добавлением записи в базу данных data.db3"));
    }
}
