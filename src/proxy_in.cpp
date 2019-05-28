#include "proxy_in.h"

#include <QObject>

proxy_in::proxy_in(QSqlDatabase *arg)
{
    _dbw = *arg;
}
proxy_in::~proxy_in()
{
    _dbw.close();
}
int proxy_in::size() const
{
    return this->count();
}
int proxy_in::count() const
{
    QSqlQuery query(_dbw);
    query.exec("SELECT inq FROM in_data;");
    if (query.last()){
        QSqlRecord rec = query.record();
        return query.value(rec.indexOf("inq")).toInt();
    }
    return 0;
}
letter_in proxy_in::at(int arg) const
{
    ++arg;
    letter_in ret;
    QSqlQuery query(_dbw);
    QSqlRecord rec;
    if (!query.exec("SELECT * FROM in_data WHERE inq = '" + QString::number(arg) + "';")){
         QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("Что-то не то с чтением базы данных data.db3"));
    }
    query.first();
    rec = query.record();
    QDateTime sys_dat, in_dat, rec_dat;
    sys_dat.setMSecsSinceEpoch(query.value(rec.indexOf("sys_data")).value<qint64>());
    in_dat.setMSecsSinceEpoch(query.value(rec.indexOf("in_date")).value<qint64>());
    rec_dat.setMSecsSinceEpoch(query.value(rec.indexOf("reception_date")).value<qint64>());
    if (query.value(rec.indexOf("control")).toString() == "true"){
        ret.set_control(true);} else {
        ret.set_control(false);}
    ret.set_doc_out_number(my::base64_minus(query.value(rec.indexOf("doc_out_number")).toString()));
    ret.set_send_rec(my::base64_minus(query.value(rec.indexOf("send_rec")).toString()));
    ret.set_content(my::base64_minus(query.value(rec.indexOf("content")).toString()));
    ret.set_worker(my::base64_minus(query.value(rec.indexOf("worker")).toString()));
    ret.set_inv(query.value(rec.indexOf("label_uniq")).toString());
    ret.set_sys_data(sys_dat.date());
    ret.set_doc_in_number(my::base64_minus(query.value(rec.indexOf("doc_in_number")).toString()));
    ret.set_in_date(in_dat.date());
    ret.set_recipient(my::base64_minus(query.value(rec.indexOf("recipient")).toString()));
    ret.set_reception_date(rec_dat.date());
    if (query.value(rec.indexOf("fix")).toString() == "true"){ret.set_fix();}
    if (!query.exec("SELECT * FROM in_foto WHERE label_uniq = '" + ret.get_inv() + "';")){
        QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("Что-то не то с чтением базы данных data.db3"));
   }
    rec = query.record();
    while (query.next()){
        doc_image* tmp = new doc_image(img_status::in_foto);
        tmp->set_adr(my::base64_minus(query.value(rec.indexOf("adr_str")).toString()));
        tmp->set_uniq(query.value(rec.indexOf("uniq_str")).toString());
        tmp->set_number_doc(query.value(rec.indexOf("label_uniq")).toString());
        ret.add_images(tmp);
    }
    return ret;
}
void proxy_in::append(letter_in* arg)
{
    QSqlQuery query(_dbw);
    QString fix, control;
    if (arg->is_fix()){fix = "true";} else {fix = "false";}
    if (arg->is_control()){control = "true";} else {control = "false";}
    QDateTime sys_dat(arg->get_sys_data());
    QDateTime in_dat(arg->get_in_date());
    QDateTime rec_dat(arg->get_reception_date());
    if (!query.exec("INSERT INTO in_data(doc_out_number, send_rec, content, worker, sys_data, fix, doc_in_number, in_date, recipient, reception_date, control, label_uniq) VALUES ('" +
                    my::base64_plus(arg->get_doc_out_number()) + "', '" + my::base64_plus(arg->get_send_rec()) + "', '" + my::base64_plus(arg->get_content()) + "', '" +
                    my::base64_plus(arg->get_worker()) + "', '" + QString::number(sys_dat.toMSecsSinceEpoch()) + "', '" +
                    fix + "', '" + my::base64_plus(arg->get_doc_in_number()) + "', '" + QString::number(in_dat.toMSecsSinceEpoch()) + "', '" +
                    my::base64_plus(arg->get_recipient()) + "', '" + QString::number(rec_dat.toMSecsSinceEpoch()) + "', '" + control + "', '" + arg->get_inv() + "');")){
        QMessageBox::information(nullptr, QObject::tr("Внимание"),
                                 QObject::tr("Что-то не то с добавлением записи в базу данных. <br> Возможно не уникальный номер входящего документа"));
    }
}
void proxy_in::insert(int row, letter_in* arg)
{
    QSqlQuery query(_dbw);
    QString fix, control;
    if (arg->is_fix()){fix = "true";} else {fix = "false";}
    if (arg->is_control()){control = "true";} else {control = "false";}
    QDateTime sys_dat(arg->get_sys_data());
    QDateTime in_dat(arg->get_in_date());
    QDateTime rec_dat(arg->get_reception_date());
    if (!query.exec("UPDATE in_data SET doc_out_number = '" + my::base64_plus(arg->get_doc_out_number()) + "', send_rec = '" +
                    my::base64_plus(arg->get_send_rec()) + "', content = '" + my::base64_plus(arg->get_content()) + "', worker = '" +
                    my::base64_plus(arg->get_worker()) + "', sys_data = '" + QString::number(sys_dat.toMSecsSinceEpoch()) + "', fix = '" +
                    fix + "', doc_in_number = '" + my::base64_plus(arg->get_doc_in_number()) + "', in_date = '" +
                    QString::number(in_dat.toMSecsSinceEpoch()) + "', recipient = '" + my::base64_plus(arg->get_recipient()) + "', reception_date ='" +
                    QString::number(rec_dat.toMSecsSinceEpoch()) + "', control = '"+ control + "', label_uniq = '" + arg->get_inv() + "' WHERE inq ='" + QString::number(row + 1) + "';")) {
        QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("Что-то не то с добавлением записи в базу данных data.db3"));
    }
}
