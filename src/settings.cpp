#include "settings.h"

#include <QObject>

settings::settings()
{
    QDir us_dir;
    us_dir.mkdir(QDir::homePath() + "/.post");
    set_path = QDir::homePath() + "/.post/db.set";
    QFile tester_ini(set_path);
    db_path = "";
    if (!tester_ini.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("Невозможно найти или сохранить путь к базе даных"));
    }
    QTextStream in_out(&tester_ini);
    QByteArray retar2 = tester_ini.readAll();
    QByteArray retar= QByteArray::fromBase64(retar2);
    db_path.append(retar);
    if (db_path == ""){
        db_path = choise_set_path();
        in_out << db_path;
        retar2.append(db_path);
        retar= QByteArray::fromBase64(retar2);
        db_path.clear();
        db_path.append(retar);
    }
     db_path += "/post";
    _images_dir = db_path + "/docs/";
    _db_dir = db_path + "/data/data.db3";
    QFile tester(_db_dir);
    if (!tester.exists()){ create_base();}
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(_db_dir);
    if(!_db.open()){ QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("База данных не открывается data.db3"));}
}
QString settings::get_img_dir() const
{
    return _images_dir;
}
QString settings::get_db_dir() const
{
    return _db_dir;
}
QSqlDatabase& settings::get_db()
{
    return _db;
}
void settings::create_base()
{
    QDir my_dir(db_path);
    my_dir.mkpath(db_path);
    my_dir.mkdir("docs");
    my_dir.mkdir("data");
    QSqlDatabase temp_db = QSqlDatabase::addDatabase("QSQLITE");
    temp_db.setDatabaseName(_db_dir);
    if(!temp_db.open()){ QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("База данных не открывается data.db3"));}
    QSqlQuery query;
    QString prep = "CREATE TABLE out_data (doc_out_number TEXT UNIQUE NOT NULL, send_rec TEXT, content TEXT, worker TEXT, sys_data INTEGER, fix TEXT, blank_number TEXT UNIQUE, notice TEXT, label_uniq TEXT UNIQUE NOT NULL, inq INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);";
        if (!query.exec(prep)) {
            QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("База данных пуста и не удается создать таблицу in_data"));
        }
        prep = "CREATE TABLE in_data (doc_out_number TEXT, send_rec TEXT, content TEXT, worker TEXT, sys_data INTEGER, fix TEXT, doc_in_number TEXT UNIQUE NOT NULL, in_date INTEGER, recipient TEXT, reception_date INTEGER, control TEXT, label_uniq TEXT UNIQUE NOT NULL, inq INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);";
            if (!query.exec(prep)) {
                QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("База данных пуста и не удается создать таблицу out_data"));
            }
// doc_out TEXT - номер документа, adr_str TEXT - имя файла, uniq_str - тип хранения (пока свободно), im_hash TEXT - хэш картинки
       QString prep2 = "CREATE TABLE out_foto (label_uniq TEXT, adr_str TEXT, uniq_str TEXT, im_hash TEXT, inq INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);";
            if (!query.exec(prep2)) {
                QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("База данных пуста и не удается создать таблицу out_foto"));
            }
        prep2 = "CREATE TABLE in_foto (label_uniq TEXT, adr_str TEXT, uniq_str TEXT, im_hash TEXT, inq INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);";
            if (!query.exec(prep2)) {
                QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("База данных пуста и не удается создать таблицу in_foto"));
            }
    temp_db.close();
}
QString settings::choise_set_path()
{
    QString str{""};
    while(str == "") {
    str = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Выберите папку с данными программы"), QDir::homePath(), QFileDialog::ShowDirsOnly);
    }
    QByteArray retar;
    retar.append(str);
    retar = retar.toBase64();
    str = retar;
    return str;
}
bool settings::choise_patch()
{
    QFile tester_ini(set_path);
    if (!tester_ini.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("Невозможно найти или сохранить путь к базе даных"));
        return false;
    }
    QTextStream in_out(&tester_ini);
    QByteArray retar2;
    QByteArray retar;
    db_path = choise_set_path();
    in_out << db_path;
    retar2.append(db_path);
    retar= QByteArray::fromBase64(retar2);
    db_path.clear();
    db_path.append(retar);
    db_path += "/post";
    _images_dir = db_path + "/docs/";
    _db_dir = db_path + "/data/data.db3";
    QFile tester(_db_dir);
    if (!tester.exists()){ create_base();}
    QSqlDatabase tmp_db = QSqlDatabase::addDatabase("QSQLITE");
    tmp_db.setDatabaseName(_db_dir);
    tmp_db.setDatabaseName(_db_dir);
    if(!tmp_db.open()){
        QMessageBox::information(nullptr, QObject::tr("Внимание"), QObject::tr("База данных не открывается data.db3"));
        return false;
    }
    _db = tmp_db;
    return true;
}
