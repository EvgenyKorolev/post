#include "yes_no.h"

yes_no::yes_no(const QString &arg1, const QString &arg2, QWidget *parent) : QDialog (parent)
{
    this->setWindowTitle(arg1);
    this->setWindowIcon(QIcon(":/images/KlogoS.png"));
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* push_pay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* inf = new QLabel();
    inf->setText(arg2);
    QPushButton* but_ok = new QPushButton(tr("Да"));
    QPushButton* but_cancel = new QPushButton(tr("Отмена"));
    QObject::connect(but_ok, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(but_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    push_pay->addWidget(but_ok);
    push_pay->addWidget(but_cancel);
    main_lay->addWidget(inf);
    main_lay->addLayout(push_pay);
    this->setLayout(main_lay);
}
