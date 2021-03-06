#ifndef IMAGES_EDITORS_H
#define IMAGES_EDITORS_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QAction>
#include <QGraphicsScene>
#include <QBoxLayout>
#include <QPrintDialog>
#include <QPrinter>
#include <QFile>
#include <QFileDialog>
#include <QToolBar>
#include <QWidget>
#include <QGraphicsView>
#include <QPixmap>
#include <algorithm>
#include "letter.h"
#include "declaration.h"

class images_editors : public QDialog
{
    Q_OBJECT
public:
    images_editors(const QList<doc_image *> &arg, const QString &arg_number, img_status img);
    ~images_editors();
    void ser_str(const QList<doc_image*> &arg);
    QList<doc_image*> result() const;
public slots:
    void slot_save();
    void slot_add();
    void slot_del();
    void slot_next();
    void slot_prev();
    void slot_print();
    void slot_save_as();
    void slot_ok();
private:
    void view_img(int arg);
    QList<doc_image*> _data_str;
    QGraphicsScene* _main_scene;
    QGraphicsView* _main_view;
    QAction* _act_prev;
    QAction* _act_next;
    QAction* _act_add;
    QAction* _act_print;
    QAction* _act_save_as;
    QAction* _act_del;
    QAction* _act_ok;
    QPixmap actual_img;
    img_status img_st;
    QString number;
    int _focus;
};

#endif // IMAGES_EDITORS_H
