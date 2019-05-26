#include "my_view.h"

my_view::my_view(QWidget *par) : QTableView(par)
{
}
void my_view::mousePressEvent(QMouseEvent *arg)
{
    if ((arg->buttons() == Qt::RightButton)){
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        if (this->indexAt(arg->pos()).isValid()) {
            _curs = arg->pos();
            if (model()->headerData(0, Qt::Horizontal, Qt::DisplayRole) == tr("Входящий номер")) {
                if (this->indexAt(arg->pos()).data(Qt::EditRole).value<letter_in>().is_fix()){
                    QAction *brow_doc = new QAction((tr("Подробности")), this);
                    QObject::connect(brow_doc, SIGNAL(triggered()), this, SLOT(slot_browser_in()));
                    QAction *con_doc = new QAction(tr("Контроль"), this);
                    QObject::connect(con_doc, SIGNAL(triggered()), this, SLOT(slot_inv()));
                    mnu->addAction(con_doc);
                    mnu->addAction(brow_doc);
                } else {
                    QAction *ed_doc = new QAction(tr("Редактировать"), this);
                    QObject::connect(ed_doc, SIGNAL(triggered()), this, SLOT(slot_edit_in()));
                    QAction *con_doc = new QAction(tr("Контроль"), this);
                    QObject::connect(con_doc, SIGNAL(triggered()), this, SLOT(slot_inv()));
                    QAction *fix_doc = new QAction(tr("Провести"), this);
                    QObject::connect(fix_doc, SIGNAL(triggered()), this, SLOT(slot_fix_in()));
                    mnu->addAction(con_doc);
                    mnu->addAction(ed_doc);
                    mnu->addAction(fix_doc);
                }
            } else if (model()->headerData(0, Qt::Horizontal, Qt::DisplayRole) == tr("№ фирменного бланка")) {
                if (this->indexAt(arg->pos()).data(Qt::EditRole).value<letter_out>().is_fix()){
                    QAction *brow_doc = new QAction(tr("Подробности"), this);
                    QObject::connect(brow_doc, SIGNAL(triggered()), this, SLOT(slot_browser_out()));
                    mnu->addAction(brow_doc);
                } else {
                    QAction *ed_doc = new QAction(tr("Редактировать"), this);
                    QObject::connect(ed_doc, SIGNAL(triggered()), this, SLOT(slot_edit_out()));
                    QAction *fix_doc = new QAction(tr("Провести"), this);
                    QObject::connect(fix_doc, SIGNAL(triggered()), this, SLOT(slot_fix_out()));
                    mnu->addAction(ed_doc);
                    mnu->addAction(fix_doc);
                }
            }
        }
        mnu->popup(arg->globalPos());
        mnu->show();
    }
    QTableView::mousePressEvent(arg);
}
void my_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    _curs = arg->pos();
    if (this->indexAt(_curs).isValid()){
        if (model()->headerData(0, Qt::Horizontal, Qt::DisplayRole) == tr("Входящий номер")){
            if (this->indexAt(_curs).data(Qt::EditRole).value<letter_in>().is_fix()){
                this->slot_browser_in();
            } else {
                this->slot_edit_in();
            }
        } else if (model()->headerData(0, Qt::Horizontal, Qt::DisplayRole) == tr("№ фирменного бланка")){
            if (this->indexAt(_curs).data(Qt::EditRole).value<letter_out>().is_fix()){
                this->slot_browser_out();
            } else {
                this->slot_edit_out();
            }
        }
    }
    QTableView::mouseDoubleClickEvent(arg);
}
void my_view::slot_add()
{
    items_fabrica itfab;
    if (model()->headerData(0, Qt::Horizontal, Qt::DisplayRole) == tr("Входящий номер")){
        letter_in *tmpl = itfab.create_let_in();
        editor_letter_in *edit = new editor_letter_in(tmpl, this);
        if (edit->exec() == QDialog::Accepted){
            int i = model()->rowCount();
            model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(tmpl), Qt::EditRole);
        }
        delete edit;
    }
    if (model()->headerData(0, Qt::Horizontal, Qt::DisplayRole) == tr("№ фирменного бланка")){
        letter_out *tmpl = itfab.create_let_out();
        editor_letter_out *edit = new editor_letter_out(tmpl, this);
        if (edit->exec() == QDialog::Accepted){
            int i = model()->rowCount();
            model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(tmpl), Qt::EditRole);
        }
        delete edit;
    } 
}
void my_view::slot_edit_in()
{
    if (!this->indexAt(_curs).data(Qt::EditRole).value<letter_in>().is_fix()){
       letter_in tmpl = this->indexAt(_curs).data(Qt::EditRole).value<letter_in>();
       editor_letter_in *edit = new editor_letter_in(&tmpl, this);
       if (edit->exec() == QDialog::Accepted){
          int i = this->indexAt(_curs).row();
          model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(&tmpl), Qt::EditRole);
       }
       delete edit;
    } else return;
}
void my_view::slot_edit_out()
{
    if (!this->indexAt(_curs).data(Qt::EditRole).value<letter_out>().is_fix()){
       letter_out tmpl = this->indexAt(_curs).data(Qt::EditRole).value<letter_out>();
       editor_letter_out *edit = new editor_letter_out(&tmpl, this);
       if (edit->exec() == QDialog::Accepted){
          int i = this->indexAt(_curs).row();
          model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(&tmpl), Qt::EditRole);
       }
       delete edit;
    } else return;
}
void my_view::slot_browser_in()
{
    letter_in tmpl = this->indexAt(_curs).data(Qt::EditRole).value<letter_in>();
    browser_letter_in *brows = new browser_letter_in(&tmpl, this);
    if (brows->exec() == QDialog::Accepted){
        int i = this->indexAt(_curs).row();
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(&tmpl), Qt::EditRole);
    }
    delete brows;
}
void my_view::slot_browser_out()
{
       letter_out tmpl = this->indexAt(_curs).data(Qt::EditRole).value<letter_out>();
       browser_letter_out *brows = new browser_letter_out(&tmpl, this);
       if (brows->exec() == QDialog::Accepted){
           int i = this->indexAt(_curs).row();
           model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(&tmpl), Qt::EditRole);
       }
       delete brows;
}
void my_view::slot_inv()
{
    letter_in tmpl = this->indexAt(_curs).data(Qt::EditRole).value<letter_in>();
    tmpl.set_control(!tmpl.is_control());
    int i = this->indexAt(_curs).row();
    model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(&tmpl), Qt::EditRole);
}
void my_view::slot_fix_in()
{
    letter_in tmpl = this->indexAt(_curs).data(Qt::EditRole).value<letter_in>();
    tmpl.set_fix();
    int i = this->indexAt(_curs).row();
    model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(&tmpl), Qt::EditRole);
}
void my_view::slot_fix_out()
{
    letter_out tmpl = this->indexAt(_curs).data(Qt::EditRole).value<letter_out>();
    tmpl.set_fix();
    int i = this->indexAt(_curs).row();
    model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(&tmpl), Qt::EditRole);
}
