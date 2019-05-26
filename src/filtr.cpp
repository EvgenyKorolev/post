#include "filtr.h"

filtr::filtr(QString arg)
{
    this->setWindowTitle(tr("Найти документы:"));
    this->setWindowIcon(QIcon(":/images/KlogoS.png"));

    _type = new QComboBox();
    _field = new QComboBox();
    _obj_include = new QComboBox();
    _object = new QLineEdit();
    _date_status = new QComboBox();
    _date_type = new QComboBox();
    _data_object = new QDateEdit();
    _focus_str = new QCheckBox();      // Ищим ли мы по содержанию
    _focus_str->setCheckState(Qt::Checked);
    _focus_date = new QCheckBox();     // Ищим ли мы по дате
    _focus_date->setChecked(Qt::Unchecked);
// Выбираем где искать - входящие или исходящие
    if (arg == "in"){
        _type->addItem(tr("Входящие"), QVariant("in"));
        _type->addItem(tr("Исходящие"), QVariant("out"));
    } else {
        _type->addItem(tr("Исходящие"), QVariant("out"));
        _type->addItem(tr("Входящие"), QVariant("in"));
    }
// Выбираем по какому атрибуту искать
    _field->addItem(tr("Вход. Номер"), QVariant("in_nom"));
    _field->addItem(tr("Исх. номер"), QVariant("out_nom"));
    _field->addItem(tr("Отправитель"), QVariant("sender"));
    _field->addItem(tr("Содержание"), QVariant("content"));
    _field->addItem(tr("Кому передан"), QVariant("recipient"));
    _field->addItem(tr("Отв. исполнитель"), QVariant("worker"));
    QObject::connect(_type, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_select_type()));
// Выбираем искать точное соответствие или вхождение
    _obj_include->addItem(tr("Содержит"), QVariant("incl"));
    _obj_include->addItem(tr("Точно"), QVariant("eq"));
// Значение атрибута по которому ищем
    _object->setText("");
// Как рассматривать дату - искать то что раньше, искать то что позже или искать точно
    _date_status->addItem(tr("Раньше"), QVariant ("before"));
    _date_status->addItem(tr("Позже"), QVariant ("after"));
    _date_status->addItem(tr("Точно"), QVariant ("equal"));
// По какой именно дате искать
    _date_type->addItem(tr("Дата получения"), QVariant("in_date"));
    _date_type->addItem(tr("Дата документа"), QVariant("doc_date"));
// Последняя кнопка
    QPushButton* ok_button = new QPushButton(tr("Поиск"));
    QPushButton* cancel_button = new QPushButton(tr("отмена"));
    QObject::connect(cancel_button, SIGNAL(clicked(bool)), this, SLOT(reject()));
    QObject::connect(ok_button, SIGNAL(clicked(bool)), this, SLOT(slot_find()));
    QBoxLayout* end_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    end_lay->addWidget(ok_button);
    end_lay->addWidget(cancel_button);
// разместим все виджеты
    QBoxLayout* type_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        type_lay->addWidget(_type);
    QBoxLayout* field_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        field_lay->addWidget(_field);
    QBoxLayout* obj_include_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        obj_include_lay->addWidget(_obj_include);
    QBoxLayout* object_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        object_lay->addWidget(_object);
    QBoxLayout* date_status_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        date_status_lay->addWidget(_date_status);
    QBoxLayout* date_type_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        date_type_lay->addWidget(_date_type);
    QBoxLayout* data_object_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        data_object_lay->addWidget(_data_object);
    QBoxLayout* str_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    str_lay->addLayout(type_lay);
    str_lay->addLayout(field_lay);
    str_lay->addLayout(obj_include_lay);
    str_lay->addLayout(object_lay);
    QBoxLayout* main_str_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    main_str_lay->addLayout(str_lay);
   // main_str_lay->addWidget(_focus_str);
    QBoxLayout* date_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    date_lay->addLayout(date_status_lay);
    date_lay->addLayout(date_type_lay);
    date_lay->addLayout(data_object_lay);
    QBoxLayout* main_date_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    main_date_lay->addLayout(date_lay);
    main_date_lay->addWidget(_focus_date);
QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    main_lay->addLayout(main_str_lay);
  //  main_lay->addLayout(main_date_lay);
    main_lay->addLayout(end_lay);
    this->setLayout(main_lay);
}
void filtr::slot_select_type()
{
    _field->clear();
    _date_type->clear();
    // Выбираем по какому атрибуту искать
    if (_type->itemData(_type->currentIndex()).toString() == "in"){
        _field->addItem(tr("Вход. Номер"), QVariant("in_nom"));
        _field->addItem(tr("Исх. номер"), QVariant("out_nom"));
        _field->addItem(tr("Отправитель"), QVariant("sender"));
        _field->addItem(tr("Содержание"), QVariant("content"));
        _field->addItem(tr("Кому передан"), QVariant("recipient"));
        _field->addItem(tr("Отв. исполнитель"), QVariant("worker"));
// По какой именно дате искать
        _date_type->addItem(tr("Дата получения"), QVariant("in_date"));
        _date_type->addItem(tr("Дата документа"), QVariant("doc_date"));
    } else if (_type->itemData(_type->currentIndex()).toString() == "out"){
        _field->addItem(tr("№ фирм. бланка"), QVariant("blank"));
        _field->addItem(tr("Исх. номер"), QVariant("out_nom"));
        _field->addItem(tr("Адресат"), QVariant("recipient"));
        _field->addItem(tr("Содержание"), QVariant("content"));
        _field->addItem(tr("Отв. исполнитель"), QVariant("worker"));
        _field->addItem(tr("Примечание"), QVariant("notice"));
// По какой именно дате искать
        _date_type->addItem(tr("Дата регистрации"), QVariant("sys_date"));
    }
}
void filtr::slot_find()
{
    emit accept();
}
QString filtr::result_type()
{
    return _type->itemData(_type->currentIndex()).toString();
}
QString filtr::result_field()
{
    return _field->itemData(_type->currentIndex()).toString();
}
bool filtr::result_obj_eq()
{
    if (_obj_include->itemData(_type->currentIndex()).toString() == "eq") {
        return true;
    }
    return false;
}
QString filtr::result_object()
{
    return _object->text();
}
QString filtr::result_date_status()
{
    return _date_status->itemData(_type->currentIndex()).toString();
}
QString filtr::result_date_type()
{
    return _date_type->itemData(_type->currentIndex()).toString();
}
QDate filtr::result_data_object()
{
    return _data_object->date();
}
bool filtr::result_focus_str()
{
    if (_focus_str->checkState() == Qt::Checked) {
        return true;
    }
    return false;
}
bool filtr::result_focus_date()
{
    if (_focus_date->checkState() == Qt::Checked) {
        return true;
    }
    return false;
}
void filtr::set_def(QString arg){
    _type->clear();
    if (arg == "in"){
        _type->addItem(tr("Входящие"), QVariant("in"));
        _type->addItem(tr("Исходящие"), QVariant("out"));
    } else {
        _type->addItem(tr("Исходящие"), QVariant("out"));
        _type->addItem(tr("Входящие"), QVariant("in"));
    }
    slot_select_type();
}
QRegExp filtr::result_obj_reg()
{
    QString focus_str = this->result_object();
    QString res;
    QRegExp tmp_reg;
        for (int i =0; i < focus_str.size(); ++i){
            res.append("[");
            tmp_reg.setPattern("[a-z]");
            bool flag = true;
            if (tmp_reg.exactMatch(focus_str.at(i))) {
                res.append(focus_str.at(i));
                res.append(focus_str.at(i).toUpper());
                flag = false;
            }
            tmp_reg.setPattern("[а-я]");
            if (tmp_reg.exactMatch(focus_str.at(i))) {
                res.append(focus_str.at(i));
                res.append(focus_str.at(i).toUpper());
                flag = false;
            }
            tmp_reg.setPattern("[A-Z]");
            if (tmp_reg.exactMatch(focus_str.at(i))) {
                res.append(focus_str.at(i));
                res.append(focus_str.at(i).toLower());
                flag = false;
            }
            tmp_reg.setPattern("[А-Я]");
            if (tmp_reg.exactMatch(focus_str.at(i))) {
                res.append(focus_str.at(i));
                res.append(focus_str.at(i).toLower());
                flag = false;
            }
            if (flag){
                res.append(focus_str.at(i));
            }
            res.append("]");
        }

        if (this->result_obj_eq()) {
            tmp_reg.setPattern(res);
            return tmp_reg;
        }
    res.push_front(".*");
    res.push_back(".*");
    tmp_reg.setPattern(res);
    return tmp_reg;
}
QRegExp filtr::result_data_reg()
{
    QRegExp ret_reg;
    return ret_reg;
}
