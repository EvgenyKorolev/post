#include "languegemenu.h"

#include <QIcon>

LanguegeMenu::LanguegeMenu(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("Выбор языка"));
    this->setWindowIcon(QIcon(":/images/KlogoS.png"));
}
