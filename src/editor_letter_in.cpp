#include "editor_letter_in.h"

editor_letter_in::editor_letter_in(letter_in *arg, QWidget *parent) : QDialog(parent)
{
    _data = arg;
    this->setWindowTitle(tr("Входящий документ:"));
    this->setWindowIcon(QIcon(":/images/KlogoS.png"));
// Входящий номер документа
    QLabel *numlab = new QLabel();
        numlab->setText(tr("Входящий номер: "));
        numlab->setMinimumWidth(90);
        numlab->setMaximumWidth(90);
        _doc_in_number = new QLineEdit();
        _doc_in_number->setText(_data->get_doc_in_number());
        _doc_in_number->setMinimumWidth(200);
        _doc_in_number->setMaximumWidth(200);
    QBoxLayout *num_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        num_lay->addWidget(numlab);
        num_lay->addWidget(_doc_in_number);
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
        _in_date->setMaximumWidth(80);
    QBoxLayout *dat_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    dat_lay->setAlignment(Qt::AlignLeft);
        dat_lay->addWidget(indnumlab);
        dat_lay->addWidget(_in_date);
// Дата получения
    QLabel *rdlab = new QLabel();
        rdlab->setText(tr("Дата получения: "));
        _reception_date = new QDateEdit();
        if ( tmp == _data->get_in_date()){
            _reception_date->setDate(QDate::currentDate());
        } else {
            _reception_date->setDate(_data->get_reception_date());
        }
        _reception_date->setMaximumWidth(80);
        _reception_date->setMinimumWidth(80);
        dat_lay->addWidget(rdlab);
        dat_lay->addWidget(_reception_date);
// Корреспондент (откуда поступил документ)
    QLabel *corlab = new QLabel();
        corlab->setText(tr("Корреспондент:   "));
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
    control_lay->addStretch();
    control_lay->addWidget(_controlbox);
    fix_lay->addWidget(fixlab);
    fix_lay->addStretch();
    fix_lay->addWidget(_fixbox);
    check_lay->addLayout(control_lay);
    check_lay->addLayout(fix_lay);
    check_lay->addWidget(image_key);
    cont_lay->addLayout(check_lay);
    cont_lay->addStretch();
// Кому передан документ
    QLabel *reclab = new QLabel();
        reclab->setText(tr("Кому передан документ:"));
        reclab->setMinimumWidth(155);
        reclab->setMaximumWidth(155);
        _recipient = new QLineEdit();
        _recipient->setText(_data->get_recipient());
        _recipient->setMinimumWidth(300);
        _recipient->setMaximumWidth(300);
    QBoxLayout *rec_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        rec_lay->addWidget(reclab);
        rec_lay->addWidget(_recipient);
        rec_lay->addStretch();
// Ответственный исполнитель
    QLabel *worklab = new QLabel();
        worklab->setText(tr("Ответственный исполнитель: "));
        worklab->setMinimumWidth(155);
        worklab->setMaximumWidth(155);
        _work = new QLineEdit();
        _work->setText(_data->get_recipient());
        _work->setMinimumWidth(300);
        _work->setMaximumWidth(300);
    QBoxLayout *work_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        work_lay->addWidget(worklab);
        work_lay->addWidget(_work);
        work_lay->addStretch();
// Финальные кнопочки
    QBoxLayout *end_key = new QBoxLayout(QBoxLayout::LeftToRight);
        QPushButton *ok_key = new QPushButton(tr("Готово"));
        QPushButton *cancel_key = new QPushButton(tr("Отмена"));
        QObject::connect(ok_key, SIGNAL(clicked()), this, SLOT(slot_save()));
        QObject::connect(cancel_key, SIGNAL(clicked()), this, SLOT(reject()));
        end_key->addWidget(ok_key);
        end_key->addWidget(cancel_key);
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
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    main_lay->addLayout(num_lay);
    main_lay->addLayout(dat_lay);
    main_lay->addLayout(cor_lay);
    main_lay->addLayout(cont_lay);
    main_lay->addLayout(rec_lay);
    main_lay->addLayout(work_lay);
    main_lay->addLayout(end_key);
    this->setLayout(main_lay);
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
