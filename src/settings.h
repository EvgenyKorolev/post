#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QSqlDatabase>

class settings
{
public:
    static settings& getInatance(){
        static settings _instance;
        return _instance;
    }
    QString get_img_dir() const;
    QString get_db_dir() const;
    QSqlDatabase& get_db();
    bool choise_patch();
private:
    settings();
    settings(const settings&);
    settings& operator=(const settings&);
    void create_base();
    void prepare_database();
    QString choise_set_path();
    // Переменные для хранения разных настроек
    QString _images_dir;
    QString _db_dir;
    QString set_path;
    QString db_path;
    QSqlDatabase _db;
    QString m_currentVersion;
};

#endif // SETTINGS_H
