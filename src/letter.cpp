#include "letter.h"
letter::letter()
{
    _doc_out_number = "";
    _send_rec = "";
    _content = "";
    _worker = "";
    _sys_data = QDate::currentDate();
    _fix = false;
    _col = 0;
    _image_list = QList<doc_image*>();
    _hash_label = QString();
    _hash_label.append(QString::number(QDateTime::currentSecsSinceEpoch()));
    std::random_device gensc;
    std::mt19937 gen;
    gen.seed(gensc());
    _hash_label.append(QString::number(gen()));
}
letter::letter(const letter &arg)
{
    _doc_out_number = arg._doc_out_number;
    _send_rec = arg._send_rec;
    _content = arg._content;
    _worker = arg._worker;
    _sys_data = arg._sys_data;
    _fix = arg._fix;
    _col = arg._col;
    _image_list = arg._image_list;
    _hash_label = arg._hash_label;
}
letter::letter(const letter&& arg)
{
    _doc_out_number = std::move(arg._doc_out_number);
    _send_rec = std::move(arg._send_rec);
    _content = std::move(arg._content);
    _worker = std::move(arg._worker);
    _sys_data = std::move(arg._sys_data);
    _fix = std::move(arg._fix);
    _col = std::move(arg._col);
    _image_list = std::move(arg._image_list);
    _hash_label = std::move(arg._hash_label);
}
letter& letter::operator=(const letter& arg)
{
    _doc_out_number = arg._doc_out_number;
    _send_rec = arg._send_rec;
    _content = arg._content;
    _worker = arg._worker;
    _sys_data = arg._sys_data;
    _fix = arg._fix;
    _col = arg._col;
    _image_list = arg._image_list;
    _hash_label = arg._hash_label;
    return *this;
}
letter& letter::operator=(letter&& arg)
{
    _doc_out_number = std::move(arg._doc_out_number);
    _send_rec = std::move(arg._send_rec);
    _content = std::move(arg._content);
    _worker = std::move(arg._worker);
    _sys_data = std::move(arg._sys_data);
    _fix = std::move(arg._fix);
    _col = std::move(arg._col);
    _image_list = std::move(arg._image_list);
    _hash_label = std::move(arg._hash_label);
    return *this;
}
QString letter::get_doc_out_number() const
{
    return _doc_out_number;
}
void letter::set_doc_out_number(const QString &arg)
{
    if (!_fix) {
        _doc_out_number = arg;
    }
}
QString letter::get_send_rec() const
{
    return _send_rec;
}
void letter::set_send_rec(const QString& arg)
{
    if (!_fix) {
        _send_rec = arg;
    }
}
QString letter::get_content() const
{
    return _content;
}
void letter::set_content(const QString &arg)
{
    if (!_fix) {
        _content = arg;
    }
}
QString letter::get_worker() const
{
    return _worker;
}
void letter::set_worker(const QString& arg)
{
    if (!_fix) {
        _worker = arg;
    }
}
QDate letter::get_sys_data() const
{
    return _sys_data;
}
void letter::set_fix()
{
    _fix = true;
}
bool letter::is_fix() const
{
    return _fix;
}
int letter::get_col() const
{
    return _col;
}
void letter::set_sys_data(QDate arg)
{
    _sys_data = arg;
}
void letter::add_images(doc_image *arg)
{
    _image_list.append(arg);
}
void letter::clear_images_list()
{
    _image_list.clear();
}
QList<doc_image*> letter::get_images_list() const
{
    return _image_list;
}
QString letter::get_inv() const
{
    return _hash_label;
}
void letter::set_inv(const QString& arg)
{
    _hash_label = arg;
}
void letter::set_images_list(QList<doc_image*> arg)
{
    _image_list = arg;
}
