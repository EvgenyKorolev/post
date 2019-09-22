#ifndef EDITOR_LETTER_IN_H
#define EDITOR_LETTER_IN_H

#include "images_editors.h"

#include <QObject>

class letter_in;
class QLineEdit;
class QDateEdit;
class QCheckBox;
class QTextEdit;

class editor_letter_in : public QDialog
{
    Q_OBJECT
public:
    editor_letter_in(letter_in *arg, QWidget *parent = nullptr);
    ~editor_letter_in();
    letter_in* result() const;
private:
    letter_in* _data;            // Данные
    QLineEdit* _doc_in_number;   // Входящий номер документа
    QLineEdit* _d_o_number;      // Исходящий № док-та
    QDateEdit* _in_date;         // Дата поступившего документа
    QLineEdit* _send_rec;        // Корреспондент (откуда поступил документ)
    QTextEdit* _cont;            // Краткое содержание
    QLineEdit* _recipient;       // Кому передан документ
    QDateEdit* _reception_date;  // Дата получения
    QLineEdit* _work;            // Ответственный исполнитель
    QCheckBox* _controlbox;      // Поставлен ли на контроль
    QCheckBox* _fixbox;          // Провести документ
public slots:
    void slot_save();
    void slot_list_images();
};

#endif // EDITOR_LETTER_IN_H
