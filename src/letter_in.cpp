#include "letter_in.h"

letter_in::letter_in()
{
    _doc_out_number = "";
    _send_rec = "";
    _content = "";
    _worker = "";
    _sys_data.currentDate();
    _fix = false;
    _col = 8;
    _doc_in_number = "";
    _in_date = QDate(0,0,0);
    _recipient = "";
    _reception_date = QDate(0,0,0);
    _control = false;
}
letter_in::letter_in(const letter_in &arg) : letter (arg)
{
    _col = arg._col;
    _doc_in_number = arg._doc_in_number;
    _in_date = arg._in_date;
    _recipient = arg._recipient;
    _reception_date = arg._reception_date;
    _control = arg._control;
}
letter_in &letter_in::operator=(const letter_in &arg)
{
    _doc_out_number = arg._doc_out_number;
    _send_rec = arg._send_rec;
    _content = arg._content;
    _worker = arg._worker;
    _sys_data = arg._sys_data;
    _fix = arg._fix;
    _col = arg._col;
    _doc_in_number = arg._doc_in_number;
    _in_date = arg._in_date;
    _recipient = arg._recipient;
    _reception_date = arg._reception_date;
    _hash_label = arg._hash_label;
    _image_list = arg._image_list;
    _control = arg._control;
    return *this;
}
QString letter_in::get_doc_in_number() const
{
    return _doc_in_number;
}
void letter_in::set_doc_in_number(QString arg)
{
    if (!_fix) {
        _doc_in_number = arg;
    }
}
QDate letter_in::get_in_date() const
{
    return _in_date;
}
void letter_in::set_in_date(QDate arg)
{
    if (!_fix) {
        _in_date = arg;
    }
}
QString letter_in::get_recipient() const
{
    return _recipient;
}
void letter_in::set_recipient(QString arg)
{
    if (!_fix) {
        _recipient = arg;
    }
}
QDate letter_in::get_reception_date() const
{
    return _reception_date;
}
void letter_in::set_reception_date(QDate arg)
{
    if (!_fix) {
        _reception_date = arg;
    }
}
bool letter_in::is_control() const
{
    return _control;
}
void letter_in::set_control(bool arg)
{
    _control = arg;
}

