#ifndef EDITOR_LETTER_OUT_H
#define EDITOR_LETTER_OUT_H

#include <QObject>
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>
#include "images_editors.h"
#include "letter_out.h"

class editor_letter_out : public QDialog
{
    Q_OBJECT
public:
    editor_letter_out(letter_out* arg, QWidget *pather = nullptr);
    ~editor_letter_out();
    letter_out* result();
private:
    letter_out* _data;
    QLineEdit* _d_o_number;      // Исходящий  № док-та
    QLineEdit* _send_rec;         // Корреспондент (кому направлен / откуда поступил документ)
    QTextEdit* _cont;          // Краткое содержание
    QLineEdit* _work;           // Ответственный исполнитель
    QDateEdit* _sys_data;         // Системная отметка времени
    QLineEdit* _blank_number;    // Номер фирменного бланка
    QLineEdit* _notice;           // Примечание
    QCheckBox* _fixbox;             // Можно ли редактировать докмент ("проведён" ли он, после фиксации редактировать нельзя)
public slots:
    void slot_save();
    void slot_list_images();
};

#endif // EDITOR_LETTER_OUT_H
