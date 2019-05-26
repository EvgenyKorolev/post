#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QList>
#include <QWidget>
#include <QBoxLayout>
#include <QMdiArea>
#include <QHeaderView>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QScrollBar>
#include <QMdiSubWindow>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QEvent>
#include "settings.h"
#include "items_fabrica.h"
#include "letter_in.h"
#include "letter_out.h"
#include "my_model_in.h"
#include "my_model_out.h"
#include "my_view.h"
#include "proxy_in.h"
#include "filtr.h"
#include "yes_no.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slot_active_window();
    void slot_about();
    void slot_add();
    void slot_filtr();
    void slot_close_filtr();
    void slot_print();
    void slot_set();
    void slot_help();
private:
    QString _type_view;
    proxy_in* _prin;
    proxy_out* _prout;
    my_model_in* _inmodel;
    my_model_out* _outmodel;
    my_view* _inview;
    my_view* _outview;
    QMdiArea* _main_area;
    QAction* _act_add;
    QAction* _act_filtr;
    QAction* _act_close_filtr;
    QAction* _act_print;
    QAction* _act_about;
    QAction* _act_set;
    QAction* _act_help;
    QToolBar* _in_work_panel;
    QToolBar* _out_work_panel;
};

#endif // MAINWINDOW_H
