#ifndef MY_VIEW_IN_H
#define MY_VIEW_IN_H

#include <QObject>
#include <QWidget>
#include <QModelIndex>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include <QVariant>
#include "letter_in.h"
#include "items_fabrica.h"
#include "editor_letter_in.h"
#include "editor_letter_out.h"
#include "browser_letter_in.h"
#include "browser_letter_out.h"

class my_view : public QTableView
{
    Q_OBJECT
public:
   explicit  my_view(QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent *arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
public slots:
    void slot_add();
    void slot_edit_in();
    void slot_edit_out();
    void slot_browser_in();
    void slot_browser_out();
    void slot_inv();
    void slot_fix_in();
    void slot_fix_out();
signals:
    void sig_add();
private:
    QPoint _curs;   // Запоминаем местоположение курсора
};

#endif // MY_VIEW_IN_H
