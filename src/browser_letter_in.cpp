#include "browser_letter_in.h"

browser_letter_in::browser_letter_in(letter_in *arg, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("Входящий документ:"));
    this->setWindowIcon(QIcon(":/images/KlogoS.png"));
    _data =arg;
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QLabel* doc_in_number = new QLabel(tr(("Входящий номер документа: " + _data->get_doc_in_number()).toUtf8()));         // Входящий номер документа
    QLabel* d_o_number = new QLabel(tr(("Исходящий № док-та: " + _data->get_doc_out_number()).toUtf8()));                 // Исходящий № док-та
    QLabel* in_date = new QLabel(tr(("Дата поступившего документа: " + _data->get_in_date().toString()).toUtf8()));       // Дата поступившего документа
    QLabel* send_rec = new QLabel(tr(("Корреспондент (откуда поступил документ): " + _data->get_send_rec()).toUtf8()));   // Корреспондент (откуда поступил документ)
    QLabel* cont = new QLabel(tr(("Краткое содержание: " + _data->get_content()).toUtf8()));                              // Краткое содержание
    QLabel* recipient = new QLabel(tr(("Кому передан документ: " + _data->get_recipient()).toUtf8()));                    // Кому передан документ
    QLabel* reception_date = new QLabel(tr(("Дата получения: " + _data->get_reception_date().toString()).toUtf8()));      // Дата получения
    QLabel* work = new QLabel(tr(("Ответственный исполнитель: " + _data->get_worker()).toUtf8()));                        // Ответственный исполнитель
    QLabel* reg_date = new QLabel(tr(("Дата Регистрации: " + _data->get_sys_data().toString()).toUtf8()));

    QLabel *controllab = new QLabel(tr("На контроле:"));
    _controlbox = new QCheckBox();      // Поставлен ли на контроль
    if (_data->is_control()){
        _controlbox->setCheckState(Qt::Checked);
    }
    QBoxLayout* one_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* two_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* three_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    one_lay->addWidget(doc_in_number);
    one_lay->addWidget(d_o_number);
    two_lay->addWidget(in_date);
    two_lay->addWidget(reception_date);
    three_lay->addWidget(controllab);
    three_lay->addWidget(_controlbox);
// Кнопка просмотра изображений
        QPushButton *image_key = new QPushButton(tr("Изображения..."));
        QObject::connect(image_key, SIGNAL(clicked()), this, SLOT(slot_list_images()));
        three_lay->addSpacing(100);
        three_lay->addWidget(image_key);
// Финальные кнопочки
        QPushButton *ok_key = new QPushButton(tr("Готово"));
        QObject::connect(ok_key, SIGNAL(clicked()), this, SLOT(slot_save()));
    main_lay->addLayout(one_lay);
    main_lay->addLayout(two_lay);
    main_lay->addWidget(send_rec);
    main_lay->addWidget(reg_date);
    main_lay->addWidget(cont);
    main_lay->addWidget(recipient);
    main_lay->addWidget(work);
    main_lay->addLayout(three_lay);
    main_lay->addWidget(ok_key);
    this->setLayout(main_lay);
}
letter_in* browser_letter_in::result() const
{
    return _data;
}
void browser_letter_in::slot_save()
{
    if (Qt::Checked == _controlbox->checkState()){  // Поставлен ли на контроль
        _data->set_control(true);
    } else {
        _data->set_control(false);
    }
    emit accept();
}
void browser_letter_in::slot_list_images()
{
    images_browser* imed = new images_browser(_data->get_images_list(), _data->get_inv(), img_status::in_foto);
    if (imed->exec() == QDialog::Accepted){
     _data->set_images_list(imed->result());
    }
}
