#include "images_browser.h"

images_browser::images_browser(const QList<doc_image *> &arg, const QString &arg_number, img_status img)
{
    _data_str = arg;
    img_st = img;
    number = arg_number;
    _focus = 0;
    this->setWindowTitle(tr("Сканированная копия письма"));
        this->setWindowIcon(QIcon(":/images/KlogoS.png"));
    _act_prev = new QAction(nullptr);
    _act_prev->setIcon(QIcon(":/images/prev.png"));
    _act_prev->setToolTip(tr("Предидущее изображение"));
    _act_next = new QAction(nullptr);
    _act_next->setIcon(QIcon(":/images/next.png"));
    _act_next->setToolTip(tr("Следующее изображение"));
    _act_add = new QAction(nullptr);
    _act_add->setIcon(QIcon(":/images/pls.png"));
    _act_add->setToolTip(tr("Добавить изображение"));
    _act_print = new QAction(nullptr);
    _act_ok = new QAction(nullptr);
    _act_ok->setIcon(QIcon(":/images/tick.png"));
    _act_ok->setToolTip(tr("Готово"));
    _act_print->setIcon(QIcon(":/images/printer.png"));
    _act_print->setToolTip(tr("Распечатать"));
    _act_save_as = new QAction(nullptr);
    _act_save_as->setIcon(QIcon(":/images/save.png"));
    _act_save_as->setToolTip(tr("Сохранить как..."));
    QObject::connect(_act_prev, SIGNAL(triggered(bool)), this, SLOT(slot_prev()));
    QObject::connect(_act_ok, SIGNAL(triggered(bool)), this, SLOT(slot_ok()));
    QObject::connect(_act_next, SIGNAL(triggered(bool)), this, SLOT(slot_next()));
    QObject::connect(_act_add, SIGNAL(triggered(bool)), this, SLOT(slot_add()));
    QObject::connect(_act_print, SIGNAL(triggered(bool)), this, SLOT(slot_print()));
    QObject::connect(_act_save_as, SIGNAL(triggered(bool)), this, SLOT(slot_save_as()));
    QToolBar* my_toolbar = new QToolBar();
    my_toolbar->addSeparator();
    my_toolbar->addAction(_act_prev);
    my_toolbar->addSeparator();
    my_toolbar->addAction(_act_ok);
    my_toolbar->addSeparator();
    my_toolbar->addAction(_act_print);
    my_toolbar->addSeparator();
    my_toolbar->addAction(_act_save_as);
    my_toolbar->addSeparator();
    my_toolbar->addAction(_act_next);
    my_toolbar->addSeparator();
    my_toolbar->setMovable(false);
    _main_scene = new QGraphicsScene();
    _main_view = new QGraphicsView();
    _main_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    _main_view->setRenderHint(QPainter::Antialiasing);
    _main_view->setCacheMode(QGraphicsView::CacheBackground);
    _main_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    _main_view->setScene(_main_scene);
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    main_lay->addWidget(_main_view);
    main_lay->addWidget(my_toolbar);
    actual_img = QPixmap();
    if (_data_str.size() > 0){
       this->view_img(0);
    }
    this->setLayout(main_lay);
}
images_browser::~images_browser()
{
    delete _main_scene;
    delete _main_view;
    delete _act_prev;
    delete _act_next;
    delete _act_add;
    delete _act_print;
    delete _act_save_as;
    delete _act_ok;
}
void images_browser::view_img(int arg)
{
    if ((_data_str.size() > arg)){
        actual_img.convertFromImage(_data_str.at(arg)->get_image());
        _main_scene->clear();
        _main_scene->addPixmap(actual_img);
        _focus = arg;
    }
}
void images_browser::slot_save()
{

}
void images_browser::slot_add()
{
    QString str = QFileDialog::getOpenFileName(nullptr, tr("Выберите изображение"), "", "*.jpg");
    if (str == "") return;
    QImage add_img = QImage(str, "jpg");
    doc_image* tmp = new doc_image(add_img, number + QString::number(_data_str.count()), number, img_st);
     _data_str.append(tmp);
    _focus = _data_str.size() - 1;
    this->view_img(_focus);
}
void images_browser::ser_str(const QList<doc_image *> &arg)
{
    _data_str = arg;
}
QList<doc_image*> images_browser::result() const
{
    return _data_str;
}
void images_browser::slot_ok()
{
    emit accept();
}
void images_browser::slot_next()
{
    if (_focus < _data_str.count()){
        this->view_img(_focus + 1);
    }
}
void images_browser::slot_prev()
{
    if (_focus > 0){
        this->view_img(_focus - 1);
    }
}
void images_browser::slot_print()
{
    if (_data_str.count() == 0) return;
    QPrinter printer_p;
    QPrintDialog* print_dlg = new QPrintDialog(&printer_p);
    if (print_dlg->exec() == QDialog::Accepted){
        QPainter my_painter(&printer_p);
        my_painter.drawImage(QPoint(0,0), _data_str.at(_focus)->get_image());
        my_painter.end();
    }
    delete print_dlg;
}
void images_browser::slot_save_as()
{
    QString str = QFileDialog::getSaveFileName(nullptr, tr("Сохранить документ как..."), "", "*.png");
    if (str == "") return;
    QImage tmp = _data_str.at(_focus)->get_image();
    tmp.save(str, "png");
}
