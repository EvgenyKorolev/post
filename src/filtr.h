#ifndef FILTR_H
#define FILTR_H

#include <QObject>
#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QDate>
#include <QLineEdit>
#include <QVariant>
#include <QBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QRegExp>
#include <QMessageBox>

class filtr : public QDialog
{
    Q_OBJECT
public:
    explicit filtr(QString arg);
    void set_def(QString arg);
    QString result_type();
    QString result_field();
    bool result_obj_eq();
    QString result_object();
    QString result_date_status();
    QString result_date_type();
    QDate result_data_object();
    QRegExp result_obj_reg();
    QRegExp result_data_reg();
    bool result_focus_str();
    bool result_focus_date();
public slots:
    void slot_select_type();
    void slot_find();
private:
    QComboBox* _type;           // Выбираем где искать - входящие или исходящие
    QComboBox* _field;          // Выбираем по какому атрибуту искать
    QComboBox* _obj_include;    // Выбираем искать точное соответствие или вхождение
    QLineEdit* _object;         // Значение атрибута по которому ищем
    QComboBox* _date_status;    // Как рассматривать дату - искать то что раньше, искать то что позже или искать точно
    QComboBox* _date_type;      // По какой именно дате искать
    QDateEdit* _data_object;    // Вводим дату для поиска
    QCheckBox* _focus_str;      // Ищим ли мы по содержанию
    QCheckBox* _focus_date;     // Ищим ли мы по дате
};

#endif // FILTR_H
