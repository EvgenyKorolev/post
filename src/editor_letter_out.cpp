#include "editor_letter_out.h"

editor_letter_out::editor_letter_out(letter_out *arg, QWidget *pather) : QDialog(pather)
{
    _data = arg;
    this->setWindowTitle(tr("Исходящий документ:"));
    this->setWindowIcon(QIcon(":/images/KlogoS.png"));
// Номер фирменного бланка
    QLabel *numlab = new QLabel();
        numlab->setText(tr("№ фирм. бланка: "));
        numlab->setMinimumWidth(90);
        numlab->setMaximumWidth(90);
        _blank_number = new QLineEdit();
        _blank_number->setText(_data->get_blank_number());
        _blank_number->setMinimumWidth(200);
        _blank_number->setMaximumWidth(200);
    QBoxLayout *num_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        num_lay->addWidget(numlab);
        num_lay->addWidget(_blank_number);
// Исходящий № док-та
    QLabel *innumlab = new QLabel();
        innumlab->setText(tr("Исходящий № док-та: "));
        innumlab->setMinimumWidth(115);
        innumlab->setMaximumWidth(115);
        _d_o_number = new QLineEdit();
        _d_o_number->setText(_data->get_doc_out_number());
        _d_o_number->setMinimumWidth(200);
        _d_o_number->setMaximumWidth(200);
        num_lay->addWidget(innumlab);
        num_lay->addWidget(_d_o_number);
        num_lay->addStretch();
// Корреспондент (кому направлен документ)
    QLabel *corlab = new QLabel();
        corlab->setText(tr("Корреспондент:"));
        corlab->setMinimumWidth(90);
        corlab->setMaximumWidth(90);
        _send_rec = new QLineEdit();
        _send_rec->setText(_data->get_send_rec());
        _send_rec->setMinimumWidth(527);
        _send_rec->setMaximumWidth(527);
    QBoxLayout *cor_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        cor_lay->addWidget(corlab);
        cor_lay->addWidget(_send_rec);
        cor_lay->setAlignment(Qt::AlignLeft);
        cor_lay->addStretch();
// Краткое содержание
    QLabel *contlab = new QLabel();
        contlab->setText(tr("Краткое содержание:"));
        contlab->setMinimumWidth(155);
        contlab->setMaximumWidth(155);
        _cont = new QTextEdit();
        _cont->setPlainText(_data->get_content());
        _cont->setMinimumWidth(300);
        _cont->setMaximumWidth(300);
        _cont->setMinimumHeight(100);
        _cont->setMaximumHeight(100);
    QBoxLayout *cont_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        cont_lay->setAlignment(Qt::AlignLeft);
        cont_lay->addWidget(contlab);
        cont_lay->addWidget(_cont);
// Кнопка просмотра изображений
        QPushButton *image_key = new QPushButton(tr("Изображения..."));
        QObject::connect(image_key, SIGNAL(clicked()), this, SLOT(slot_list_images()));
// Контроль и фиксация документа
    QBoxLayout *check_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *fix_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    _fixbox = new QCheckBox();
    QLabel *fixlab = new QLabel(tr("Провести:"));
        _fixbox->setCheckState(Qt::Checked);
    fix_lay->addWidget(fixlab);
    fix_lay->addStretch();
    fix_lay->addWidget(_fixbox);
    check_lay->addLayout(fix_lay);
    check_lay->addWidget(image_key);
    cont_lay->addLayout(check_lay);
    cont_lay->addStretch();
// Ответственный исполнитель
    QLabel *worklab = new QLabel();
        worklab->setText(tr("Ответственный исполнитель: "));
        worklab->setMinimumWidth(155);
        worklab->setMaximumWidth(155);
        _work = new QLineEdit();
        _work->setText(_data->get_worker());
        _work->setMinimumWidth(300);
        _work->setMaximumWidth(300);
    QBoxLayout *work_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        work_lay->addWidget(worklab);
        work_lay->addWidget(_work);
        work_lay->addStretch();
// Примечание
    QLabel *notlab = new QLabel();
        notlab->setText(tr("Примечание: "));
        notlab->setMinimumWidth(155);
        notlab->setMaximumWidth(155);
        _notice = new QLineEdit();
        _notice->setText(_data->get_notice());
        _notice->setMinimumWidth(300);
        _notice->setMaximumWidth(300);
    QBoxLayout *not_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        not_lay->addWidget(notlab);
        not_lay->addWidget(_notice);
        not_lay->addStretch();
// Финальные кнопочки
    QBoxLayout *end_key = new QBoxLayout(QBoxLayout::LeftToRight);
        QPushButton *ok_key = new QPushButton(tr("Готово"));
        QPushButton *cancel_key = new QPushButton(tr("Отмена"));
        QObject::connect(ok_key, SIGNAL(clicked()), this, SLOT(slot_save()));
        QObject::connect(cancel_key, SIGNAL(clicked()), this, SLOT(reject()));
        end_key->addWidget(ok_key);
        end_key->addWidget(cancel_key);
    if (_data->is_fix()){
        _blank_number->setReadOnly(true);
        _d_o_number->setReadOnly(true);
        _send_rec->setReadOnly(true);
        _cont->setReadOnly(true);
        _work->setReadOnly(true);
        _notice->setReadOnly(true);
    }
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    main_lay->addLayout(num_lay);
    main_lay->addLayout(cor_lay);
    main_lay->addLayout(cont_lay);
    main_lay->addLayout(work_lay);
    main_lay->addLayout(not_lay);
    main_lay->addLayout(end_key);
    this->setLayout(main_lay);
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
