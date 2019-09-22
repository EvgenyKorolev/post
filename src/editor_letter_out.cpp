#include "editor_letter_out.h"
#include "letter_out.h"

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>

editor_letter_out::editor_letter_out(letter_out *arg, QWidget *pather) : QDialog(pather)
{
    _data = arg;
    this->setWindowTitle(tr("Исходящий документ:"));
    this->setWindowIcon(QIcon(":/images/KlogoS.png"));
    QGridLayout *formLayout = new QGridLayout(this);
// Номер фирменного бланка
    QLabel *numlab = new QLabel();
        numlab->setText(tr("№ фирм. бланка: "));
        numlab->setMinimumWidth(90);
        _blank_number = new QLineEdit();
        _blank_number->setText(_data->get_blank_number());
        _blank_number->setMinimumWidth(200);
// Исходящий № док-та
    QLabel *innumlab = new QLabel();
        innumlab->setText(tr("Исходящий № док-та: "));
        innumlab->setMinimumWidth(115);
        _d_o_number = new QLineEdit();
        _d_o_number->setText(_data->get_doc_out_number());
        _d_o_number->setMinimumWidth(200);
        formLayout->addWidget(numlab, 0, 0);
        formLayout->addWidget(_blank_number, 0, 1);
        formLayout->addWidget(innumlab, 0, 2);
        formLayout->addWidget(_d_o_number, 0, 3);
// Корреспондент (кому направлен документ)
    QLabel *corlab = new QLabel();
        corlab->setText(tr("Корреспондент:"));
        corlab->setMinimumWidth(90);
        _send_rec = new QLineEdit();
        _send_rec->setText(_data->get_send_rec());
        _send_rec->setMinimumWidth(500);
        formLayout->addWidget(corlab, 1, 0);
        formLayout->addWidget(_send_rec, 1, 1, 1, 3);
// Краткое содержание
    QLabel *contlab = new QLabel();
        contlab->setText(tr("Краткое содержание:"));
        contlab->setMinimumWidth(155);
        _cont = new QTextEdit();
        _cont->setPlainText(_data->get_content());
        _cont->setMinimumWidth(300);
        _cont->setMinimumHeight(100);
        _cont->setMaximumHeight(100);
        formLayout->addWidget(contlab, 2, 0, 2, 1);
        formLayout->addWidget(_cont, 2, 1, 2, 2);
// Кнопка просмотра изображений
        QPushButton *image_key = new QPushButton(tr("Изображения..."));
        QObject::connect(image_key, SIGNAL(clicked()), this, SLOT(slot_list_images()));
// Контроль и фиксация документа
    QBoxLayout *fix_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    _fixbox = new QCheckBox();
    QLabel *fixlab = new QLabel(tr("Провести:"));
        _fixbox->setCheckState(Qt::Checked);
    fix_lay->addWidget(fixlab);
    fix_lay->addWidget(_fixbox);
    fix_lay->addStretch();
    formLayout->addLayout(fix_lay, 2, 3);
    formLayout->addWidget(image_key, 3, 3);
// Ответственный исполнитель
    QLabel *worklab = new QLabel();
        worklab->setText(tr("Ответственный исполнитель: "));
        worklab->setMinimumWidth(155);
        _work = new QLineEdit();
        _work->setText(_data->get_worker());
        _work->setMinimumWidth(300);
        formLayout->addWidget(worklab, 4, 0);
        formLayout->addWidget(_work, 4, 1, 1, 3);
// Примечание
    QLabel *notlab = new QLabel();
        notlab->setText(tr("Примечание: "));
        notlab->setMinimumWidth(155);
        _notice = new QLineEdit();
        _notice->setText(_data->get_notice());
        _notice->setMinimumWidth(300);
    QBoxLayout *not_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        not_lay->addWidget(notlab);
        not_lay->addWidget(_notice);
        not_lay->addStretch();
        formLayout->addWidget(notlab, 5, 0);
        formLayout->addWidget(_notice, 5, 1, 1, 3);
// Финальные кнопочки
        QPushButton *ok_key = new QPushButton(tr("Готово"));
        QPushButton *cancel_key = new QPushButton(tr("Отмена"));
        QObject::connect(ok_key, SIGNAL(clicked()), this, SLOT(slot_save()));
        QObject::connect(cancel_key, SIGNAL(clicked()), this, SLOT(reject()));
        formLayout->addWidget(ok_key, 6, 0, 1, 2);
        formLayout->addWidget(cancel_key, 6, 2, 1, 2);
    if (_data->is_fix()){
        _blank_number->setReadOnly(true);
        _d_o_number->setReadOnly(true);
        _send_rec->setReadOnly(true);
        _cont->setReadOnly(true);
        _work->setReadOnly(true);
        _notice->setReadOnly(true);
    }
    this->setLayout(formLayout);
}
editor_letter_out::~editor_letter_out()
{
    _data = nullptr;
    delete _d_o_number;
    delete _send_rec;
    delete _cont;
    delete _work;
    delete _blank_number;
    delete _notice;
    delete _fixbox;
}
void editor_letter_out::slot_save()
{
    if (_d_o_number->text() == ""){
        QMessageBox::information(nullptr, tr("Внимание"), tr("Необходим исходящий номер документа"));
        return;
    }
    if (_send_rec->text() == ""){
        QMessageBox::information(nullptr, tr("Внимание"), tr("Необходимо указать получателя"));
        return;
    }
    _data->set_doc_out_number(_d_o_number->text());   // Исходящий  № док-та
    _data->set_send_rec(_send_rec->text());           // Корреспондент (кому направлен / откуда поступил документ)
    _data->set_content(_cont->toPlainText());         // Краткое содержание
    _data->set_worker(_work->text());                 // Ответственный исполнитель
    _data->set_blank_number(_blank_number->text());   // Номер фирменного бланка
    _data->set_notice(_notice->text());               // Примечание
    if (Qt::Checked == _fixbox->checkState()){        // Провести документ
        _data->set_fix();
    }
    emit accept();
}
letter_out* editor_letter_out::result()
{
    return _data;
}
void editor_letter_out::slot_list_images()
{
    images_editors* imed = new images_editors(_data->get_images_list(), _data->get_inv(), img_status::out_foto);
    if (imed->exec() == QDialog::Accepted){
     _data->set_images_list(imed->result());
    }
}
