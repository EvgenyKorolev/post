#include "editor_letter_in.h"
#include "letter_in.h"

#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>

editor_letter_in::editor_letter_in(letter_in *arg, QWidget *parent) : QDialog(parent)
{
    _data = arg;
    this->setWindowTitle(tr("Входящий документ:"));
    this->setWindowIcon(QIcon(":/images/KlogoS.png"));
    QGridLayout *formLayout = new QGridLayout(this);
// Входящий номер документа
    QLabel *numlab = new QLabel();
        numlab->setText(tr("Входящий номер: "));
        numlab->setMinimumWidth(90);
        _doc_in_number = new QLineEdit();
        _doc_in_number->setText(_data->get_doc_in_number());
        _doc_in_number->setMinimumWidth(200);
// Исходящий № док-та
    QLabel *innumlab = new QLabel();
        innumlab->setText(tr("Исходящий № док-та: "));
        innumlab->setMinimumWidth(115);
        _d_o_number = new QLineEdit();
        _d_o_number->setText(_data->get_doc_out_number());
        _d_o_number->setMinimumWidth(200);
        formLayout->addWidget(numlab, 0, 0);
        formLayout->addWidget(_doc_in_number, 0, 1);
        formLayout->addWidget(innumlab, 0, 2);
        formLayout->addWidget(_d_o_number, 0, 3);
// Дата документа
    QLabel *indnumlab = new QLabel();
        indnumlab->setText(tr("Дата док-та:"));
        indnumlab->setMinimumWidth(90);
        indnumlab->setMaximumWidth(90);
        _in_date = new QDateEdit();
        QDate tmp = QDate(0,0,0);
        if ( tmp == _data->get_in_date()){
            _in_date->setDate(QDate::currentDate());
        } else {
            _in_date->setDate(_data->get_in_date());
        }
        _in_date->setMinimumWidth(80);
// Дата получения
    QLabel *rdlab = new QLabel();
        rdlab->setText(tr("Дата получения: "));
        _reception_date = new QDateEdit();
        if ( tmp == _data->get_in_date()){
            _reception_date->setDate(QDate::currentDate());
        } else {
            _reception_date->setDate(_data->get_reception_date());
        }
        _reception_date->setMinimumWidth(80);
        formLayout->addWidget(indnumlab, 1, 0);
        formLayout->addWidget(_in_date, 1, 1);
        formLayout->addWidget(rdlab, 1, 2);
        formLayout->addWidget(_reception_date, 1, 3);
// Корреспондент (откуда поступил документ)
    QLabel *corlab = new QLabel();
        corlab->setText(tr("Корреспондент:   "));
        corlab->setMinimumWidth(90);
        _send_rec = new QLineEdit();
        _send_rec->setText(_data->get_send_rec());
        _send_rec->setMinimumWidth(527);
        formLayout->addWidget(corlab, 2, 0);
        formLayout->addWidget(_send_rec, 2, 1, 1, 3);
// Краткое содержание
    QLabel *contlab = new QLabel();
        contlab->setText(tr("Краткое содержание:"));
        contlab->setMinimumWidth(155);
        _cont = new QTextEdit();
        _cont->setPlainText(_data->get_content());
        _cont->setMinimumWidth(300);
        _cont->setMinimumHeight(100);
        _cont->setMaximumHeight(100);
// Кнопка просмотра изображений
        QPushButton *image_key = new QPushButton(tr("Изображения..."));
        QObject::connect(image_key, SIGNAL(clicked()), this, SLOT(slot_list_images()));
// Контроль и фиксация документа
    QBoxLayout *control_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *fix_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    _controlbox = new QCheckBox();
    _fixbox = new QCheckBox();
    QLabel *controllab = new QLabel(tr("На контроль:"));
    QLabel *fixlab = new QLabel(tr("Провести:"));
    if (_data->is_control()){
        _controlbox->setCheckState(Qt::Checked);
    } else _controlbox->setCheckState(Qt::Unchecked);
        _fixbox->setCheckState(Qt::Checked);
    control_lay->addWidget(controllab);
    control_lay->addWidget(_controlbox);
    control_lay->addStretch();
    fix_lay->addWidget(fixlab);
    fix_lay->addWidget(_fixbox);
    fix_lay->addStretch();
    formLayout->addWidget(contlab, 3, 0, 3, 1);
    formLayout->addWidget(_cont, 3, 1, 3, 2);
    formLayout->addLayout(control_lay, 3, 3);
    formLayout->addLayout(fix_lay, 4, 3);
    formLayout->addWidget(image_key, 5, 3);
// Кому передан документ
    QLabel *reclab = new QLabel();
        reclab->setText(tr("Кому передан документ:"));
        reclab->setMinimumWidth(155);
        _recipient = new QLineEdit();
        _recipient->setText(_data->get_recipient());
        _recipient->setMinimumWidth(300);
        formLayout->addWidget(reclab, 6, 0);
        formLayout->addWidget(_recipient, 6, 1, 1, 3);
// Ответственный исполнитель
    QLabel *worklab = new QLabel();
        worklab->setText(tr("Ответственный исполнитель: "));
        worklab->setMinimumWidth(155);
        _work = new QLineEdit();
        _work->setText(_data->get_recipient());
        _work->setMinimumWidth(300);
        formLayout->addWidget(worklab, 7, 0);
        formLayout->addWidget(_work, 7, 1, 1, 3);
// Финальные кнопочки
        QPushButton *ok_key = new QPushButton(tr("Готово"));
        QPushButton *cancel_key = new QPushButton(tr("Отмена"));
        QObject::connect(ok_key, SIGNAL(clicked()), this, SLOT(slot_save()));
        QObject::connect(cancel_key, SIGNAL(clicked()), this, SLOT(reject()));
        formLayout->addWidget(ok_key, 8, 0, 1, 2);
        formLayout->addWidget(cancel_key, 8, 2, 1, 2);
    if (_data->is_fix()){
        _doc_in_number->setReadOnly(true);
        _d_o_number->setReadOnly(true);
        _in_date->setReadOnly(true);
        _send_rec->setReadOnly(true);
        _cont->setReadOnly(true);
        _recipient->setReadOnly(true);
        _reception_date->setReadOnly(true);
        _work->setReadOnly(true);
    }
    this->setLayout(formLayout);
}
editor_letter_in::~editor_letter_in()
{
    _data = nullptr;
    delete _doc_in_number;
    delete _d_o_number;
    delete _in_date;
    delete _send_rec;
    delete _cont;
    delete _recipient;
    delete _reception_date;
    delete _work;
    delete _controlbox;
    delete _fixbox;
}
void editor_letter_in::slot_save()
{
    if (_doc_in_number->text() == ""){
        QMessageBox::information(nullptr, tr("Внимание"), tr("Необходим входящий номер документа"));
        return;
    }
    if (_d_o_number->text() == ""){
        QMessageBox::information(nullptr, tr("Внимание"), tr("Необходим исходящий номер документа"));
        return;
    }
    if (_send_rec->text() == ""){
        QMessageBox::information(nullptr, tr("Внимание"), tr("Необходимо указать отправителя"));
        return;
    }
    _data->set_doc_in_number(_doc_in_number->text());   // Входящий номер документа
    _data->set_doc_out_number(_d_o_number->text());      // Исходящий  № док-та
    _data->set_in_date(_in_date->date());         // Дата поступившего документа
    _data->set_send_rec(_send_rec->text());        // Корреспондент (откуда поступил документ)
    _data->set_content(_cont->toPlainText());            // Краткое содержание
    _data->set_recipient(_recipient->text());       // Кому передан документ
    _data->set_reception_date(_reception_date->date());  // Дата получения
    _data->set_worker(_work->text());            // Ответственный исполнитель
    if (Qt::Checked == _controlbox->checkState()){  // Поставлен ли на контроль
        _data->set_control(true);
    } else {
        _data->set_control(false);
    }
    if (Qt::Checked == _fixbox->checkState()){      // Провести документ
        _data->set_fix();
    }
    emit accept();
}
letter_in* editor_letter_in::result() const
{
    return _data;
}     
void editor_letter_in::slot_list_images()
{
    images_editors* imed = new images_editors(_data->get_images_list(), _data->get_inv(), img_status::in_foto);
    if (imed->exec() == QDialog::Accepted){
     _data->set_images_list(imed->result());
    }
}
