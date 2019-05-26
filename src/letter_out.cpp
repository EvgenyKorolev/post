#include "letter_out.h"

letter_out::letter_out()
{
    _blank_number = "";
    _notice = "";
    _doc_out_number = "";
    _send_rec = "";
    _content = "";
    _worker = "";
    _sys_data = QDate::currentDate();
    _fix = false;
    _col = 6;
    _image_list = QList<doc_image*>();
}
letter_out::letter_out(const letter_out &arg) : letter (arg)
{
    _blank_number = arg._blank_number;
    _notice = arg._notice;
}
letter_out &letter_out::operator=(const letter_out &arg)
{
    _blank_number = arg._blank_number;
    _notice = arg._notice;
    _doc_out_number = arg._doc_out_number;
    _send_rec = arg._send_rec;
    _content = arg._content;
    _worker = arg._worker;
    _sys_data = arg._sys_data;
    _fix = arg._fix;
    _col = arg._col;
    _hash_label = arg._hash_label;
    _image_list = arg._image_list;
    return *this;
}
QString letter_out::get_blank_number() const
{
    return _blank_number;
}
void letter_out::set_blank_number(QString arg)
{
    if (!_fix) {
        _blank_number = arg;
    }
}
QString letter_out::get_notice() const
{
    return _notice;
}
void letter_out::set_notice(QString arg)
{
    if (!_fix) {
        _notice = arg;
    }
}

