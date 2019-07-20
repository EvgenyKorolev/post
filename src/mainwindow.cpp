#include "mainwindow.h"
#include "languegemenu.h"

#include <QHeaderView>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QEvent>
#include <QSqlDatabase>
#include <QList>
#include <QBoxLayout>
#include <QHeaderView>
#include <QToolBar>
#include <QMenuBar>
#include <QScrollBar>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(1300, 700);
    this->setWindowTitle(tr("Регистрация входящих и исходящих писем"));
        this->setWindowIcon(QIcon(":/images/KlogoS.png"));
    settings& set = settings::getInatance();
        QSqlDatabase& db = set.get_db();

    _prin = new proxy_in(&db);
    _prout = new proxy_out(&db);
    _inmodel = new my_model_in(_prin);
    _outmodel = new my_model_out(_prout);
    _main_area = new QMdiArea(this);
    QMdiSubWindow* in_sub = new QMdiSubWindow(_main_area);
    QMdiSubWindow* out_sub = new QMdiSubWindow(_main_area);
    _inview = new my_view(in_sub);
    _inview->setWindowTitle(tr("Входящие документы"));
    _outview = new my_view(out_sub);
    _outview->setWindowTitle(tr("Исходящие документы"));
    QSortFilterProxyModel *in_pr_model = new QSortFilterProxyModel();
    QSortFilterProxyModel *out_pr_model = new QSortFilterProxyModel();
    in_pr_model->setSourceModel(_inmodel);
    out_pr_model->setSourceModel(_outmodel);
    _inview->setModel(in_pr_model);
    _outview->setModel(out_pr_model);
    _inview->setSortingEnabled(true);
    _outview->setSortingEnabled(true);
    this->setCentralWidget(_main_area);
    in_sub->setWidget(_inview);
    out_sub->setWidget(_outview);
    in_sub->setWindowTitle(tr("Входящие документы"));
    out_sub->setWindowTitle(tr("Исходящие документы"));
    _main_area->setViewMode(QMdiArea::TabbedView);
    _main_area->addSubWindow(in_sub);
    _main_area->addSubWindow(out_sub);

    QList<QMdiSubWindow*> tmp_window = _main_area->subWindowList();
    tmp_window.at(0)->setWindowIcon(QIcon(":/images/cloud_upload.png"));
    tmp_window.at(1)->setWindowIcon(QIcon(":/images/cloud_download.png"));
    _inview->setColumnWidth(0, 130);
    _inview->setColumnWidth(1, 130);
    _inview->setColumnWidth(2, 100);
    _inview->setColumnWidth(3, 200);
    _inview->setColumnWidth(4, 170);
    _inview->setColumnWidth(5, 170);
    _inview->setColumnWidth(6, 100);
    _inview->setColumnWidth(7, 170);
    _inview->horizontalHeader()->setStretchLastSection(true);
    _outview->setColumnWidth(0, 160);
    _outview->setColumnWidth(1, 160);
    _outview->setColumnWidth(2, 220);
    _outview->setColumnWidth(3, 200);
    _outview->setColumnWidth(4, 200);
    _outview->setColumnWidth(5, 200);
    _outview->horizontalHeader()->setStretchLastSection(true);
    QObject::connect(_main_area, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(slot_active_window()));

    _act_add = new QAction(nullptr);
    _act_filtr = new QAction(nullptr);
    _act_about = new QAction(nullptr);
    _act_print = new QAction(nullptr);
    _act_close_filtr = new QAction(nullptr);
    _act_set = new QAction(nullptr);
    _act_help = new QAction(nullptr);
    _act_languege = new QAction(nullptr);
    _act_add->setIcon(QIcon(":/images/folder-add.png"));
    _act_add->setToolTip(tr("Добавить документ"));
    _act_filtr->setIcon(QIcon(":/images/zoom.png"));
    _act_filtr->setToolTip(tr("Найти"));
    _act_close_filtr->setIcon(QIcon(":/images/times.png"));
    _act_close_filtr->setToolTip(tr("Сбросить фильтр"));
    _act_about->setIcon(QIcon(":/images/info-large.png"));
    _act_about->setToolTip(tr("О программе"));
    _act_print->setIcon(QIcon(":/images/printer.png"));
    _act_print->setToolTip(tr("Печать"));
    _act_set->setIcon(QIcon(":/images/cog-outline.png"));
    _act_set->setToolTip(tr("Настройка"));
    _act_help->setIcon(QIcon(":/images/help.png"));
    _act_help->setToolTip(tr("Справка"));
    _act_help->setIcon(QIcon(":/images/help.png"));
    _act_languege->setToolTip(tr("Язык"));
    _act_languege->setIcon(QIcon(":/images/len.png"));

    QObject::connect(_act_about, SIGNAL(triggered(bool)), this, SLOT(slot_about()));
    QObject::connect(_act_add, SIGNAL(triggered(bool)), this, SLOT(slot_add()));
    QObject::connect(_act_filtr, SIGNAL(triggered(bool)), this, SLOT(slot_filtr()));
    QObject::connect(_act_print, SIGNAL(triggered(bool)), this, SLOT(slot_print()));
    QObject::connect(_act_close_filtr, SIGNAL(triggered(bool)), this, SLOT(slot_close_filtr()));
    QObject::connect(_act_set, SIGNAL(triggered(bool)), this, SLOT(slot_set()));
    QObject::connect(_act_help, SIGNAL(triggered(bool)), this, SLOT(slot_help()));
    QObject::connect(_act_languege, SIGNAL(triggered(bool)), this, SLOT(slot_languege()));

    _in_work_panel = new QToolBar();
    _out_work_panel = new QToolBar();
    this->addToolBar(_in_work_panel);
    this->addToolBar(_out_work_panel);
    _in_work_panel->hide();
    _out_work_panel->hide();
    _in_work_panel->addSeparator();
    _in_work_panel->addAction(_act_add);
    _in_work_panel->addSeparator();
    _in_work_panel->addAction(_act_filtr);
    _in_work_panel->addSeparator();
    _in_work_panel->addAction(_act_close_filtr);
    _in_work_panel->addSeparator();
    _in_work_panel->addAction(_act_print);
    _in_work_panel->addSeparator();
    _in_work_panel->addAction(_act_about);
    _in_work_panel->addSeparator();
    _in_work_panel->addAction(_act_set);
    _in_work_panel->addSeparator();
    _in_work_panel->addAction(_act_help);
    _in_work_panel->addSeparator();
    _in_work_panel->addAction(_act_languege);
    _in_work_panel->addSeparator();
    _out_work_panel->addSeparator();
    _out_work_panel->addAction(_act_add);
    _out_work_panel->addSeparator();
    _out_work_panel->addAction(_act_filtr);
    _out_work_panel->addSeparator();
    _out_work_panel->addAction(_act_close_filtr);
    _out_work_panel->addSeparator();
    _out_work_panel->addAction(_act_print);
    _out_work_panel->addSeparator();
    _out_work_panel->addAction(_act_about);
    _out_work_panel->addSeparator();
    _out_work_panel->addAction(_act_set);
    _out_work_panel->addSeparator();
    _out_work_panel->addAction(_act_help);
    _out_work_panel->addSeparator();
    _out_work_panel->addAction(_act_languege);
    _out_work_panel->addSeparator();

    _inview->scrollToBottom();
    _outview->scrollToBottom();
}
MainWindow::~MainWindow()
{
    delete _prin;
    delete _prout;
    delete _inmodel;
    delete _outmodel;
    delete _inview;
    delete _outview;
    delete _act_add;
    delete _act_filtr;
    delete _act_close_filtr;
    delete _act_print;
    delete _act_about;
    delete _act_set;
    delete _act_help;
    delete _in_work_panel;
    delete _out_work_panel;
}
void MainWindow::slot_active_window()
{
    if (_main_area->activeSubWindow() == nullptr) return;
    if (_main_area->activeSubWindow()->windowTitle() == tr("Входящие документы")) {
        _out_work_panel->hide();
        _in_work_panel->show();
        _type_view = "in";
    } else if (_main_area->activeSubWindow()->windowTitle() == tr("Исходящие документы")) {
        _in_work_panel->hide();
        _out_work_panel->show();
        _type_view = "out";
    }
}
void MainWindow::slot_add()
{
    if (_type_view == "in"){
        _inview->slot_add();
    } else if (_type_view == "out"){
        _outview->slot_add();
    }
    this->slot_close_filtr();
}
void MainWindow::slot_filtr()
{
    QSortFilterProxyModel *main_filtr_model = new QSortFilterProxyModel();
    filtr* my_filter = new filtr("in");
    if (_type_view == "in"){
        my_filter->set_def("in");
        }  else if (_type_view == "out"){
                 my_filter->set_def("out");
    } else {QMessageBox::information(nullptr, tr("Внимание"), tr("Не получается создать окошко фильтра"));}
    if (my_filter->exec() == QDialog::Accepted){
        QRegExp my_reg_string = my_filter->result_obj_reg();
// Создаём модели посредники для поиска и сортировки
        if (my_filter->result_type() == "in"){
            main_filtr_model->setSourceModel(_inmodel);
// Модель будет для входящих
         if (my_filter->result_focus_str()){
            QString fld = my_filter->result_field();
// "Вход. Номер" - "in_nom"
            if (fld == "in_nom"){main_filtr_model->setFilterKeyColumn(0);}
// "Исх. номер" - "out_nom"
            if (fld == "out_nom"){main_filtr_model->setFilterKeyColumn(1);}
// "Отправитель" - "sender"
            if (fld == "sender"){main_filtr_model->setFilterKeyColumn(3);}
// "Содержание" - "content"
            if (fld == "content"){main_filtr_model->setFilterKeyColumn(4);}
// "Кому передан" - "recipient"
            if (fld == "recipient"){main_filtr_model->setFilterKeyColumn(5);}
// "Отв. исполнитель" - "worker"
            if (fld == "worker"){main_filtr_model->setFilterKeyColumn(7);}
         }
        main_filtr_model->setFilterRegExp(my_reg_string);

    if (!my_filter->result_focus_date()) {_inview->setModel(main_filtr_model);}
        }
     else if (my_filter->result_type() == "out") {
            main_filtr_model->setSourceModel(_outmodel);
// Модель будет для исходящих
         if (my_filter->result_focus_str()) {
            QString fld = my_filter->result_field();
// "№ фирм. бланка" - "blank"
            if (fld == "blank"){main_filtr_model->setFilterKeyColumn(0);}
// "Исх. номер" - "out_nom"
            if (fld == "out_nom"){main_filtr_model->setFilterKeyColumn(1);}
// "Адресат" - "recipient"
            if (fld == "recipient"){main_filtr_model->setFilterKeyColumn(2);}
// "Содержание" - "content"
            if (fld == "content"){main_filtr_model->setFilterKeyColumn(3);}
// "Отв. исполнитель" - "worker"
            if (fld == "worker"){main_filtr_model->setFilterKeyColumn(4);}
// "Примечание" - "notice"
            if (fld == "notice"){main_filtr_model->setFilterKeyColumn(5);}
         }
         main_filtr_model->setFilterRegExp(my_reg_string);

    if (!my_filter->result_focus_date()) {_outview->setModel(main_filtr_model);}
        }
    }
    delete my_filter;
}
void MainWindow::slot_about()
{
    QMessageBox about;
    about.setText("<table><tr><th>"
                  "<img src=\":/images/KlogoS.png\"> </th> <th>Регистрация документов 0.9.9 <br>"
                  "Программу разработал Евгений Королёв <br> "
                  "Cайт: <a href = 'http://kyrych.ru/44-dev/app/158-post'>kyrych.ru</a><br> "
                  "E-mail: <a href = 'mailto:root@kyrych.ru'>root@kyrych.ru</a> <br> "
                  "XMPP: kyrych@xmpp.ru "
                  "</th></tr></table>");
    about.setWindowIcon(QIcon(":/images/KlogoS.png"));
    about.setWindowTitle(tr("О программе:"));
    about.exec();
}
void MainWindow::slot_close_filtr()
{
    QSortFilterProxyModel *in_pr_model = new QSortFilterProxyModel();
    QSortFilterProxyModel *out_pr_model = new QSortFilterProxyModel();
    in_pr_model->setSourceModel(_inmodel);
    out_pr_model->setSourceModel(_outmodel);
    _inview->setModel(in_pr_model);
    _outview->setModel(out_pr_model);
    _inview->scrollToBottom();
    _outview->scrollToBottom();
}
void MainWindow::slot_print()
{
    my_view* view_tmp;
    if (_type_view == "in"){
        view_tmp = _inview;
    } else if (_type_view == "out"){
        view_tmp = _outview;
    } else return;

    QString strStream;
        QTextStream out(&strStream);

        const int rowCount = view_tmp->model()->rowCount();
        const int columnCount = view_tmp->model()->columnCount();

        out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("strTitle")
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
        out << "<thead><tr bgcolor=#f0f0f0>";
        for (int column = 0; column < columnCount; column++)
            if (!view_tmp->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(view_tmp->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column = 0; column < columnCount; column++) {
                if (!view_tmp->isColumnHidden(column)) {
                    QString data = view_tmp->model()->data(view_tmp->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer;

        QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
        if (dialog->exec() == QDialog::Accepted) {
            document->print(&printer);
        }
        delete document;
}
void MainWindow::slot_set()
{
    yes_no* pmbx = new yes_no(tr("Настройка"),
                        tr("<HTML><HEAD><BODY><p align='center'><b>Внимание!</b></p><br>"
                        "Данная функция предназначена для указания пути к каталогу post с базой <br>"
                        "данных приложения (каталоги docs и data) в случае если он был перемещён.<br> "
                        "Если вы укажите пустой каталог, то будет создана новая база объединение<br>"
                        "которой с предидущей базой будет невозможно. Можно будет снова выбрать<br>"
                        "предыдущую базу, но документы внесённую в новую перенесены не будут.<br></BODY></HEAD></HTML>"),
                        this);
    if (pmbx->exec() == QDialog::Accepted)
    {
        settings& set = settings::getInatance();
        set.choise_patch();
        slot_close_filtr();
    }
    delete pmbx;
}
void MainWindow::slot_help()
{
    QMessageBox about;
    about.setText(tr("<p align=\"center\"><b>Назначения кнопок панели управления:<b><br></p>"
                  "<table style=\"margin-right: auto; margin-left: auto; height: 286px; width: 800px;\" border=\"1\">"
                     "<tbody>"
                          "<tr>"
                              "<td><img src=\":/images/folder-add.png\" />&nbsp;</td>"
                              "<td>&nbsp;Добавить документ в текущую вкладку (Входящий или исходящий)</td>"
                          "</tr>"
                          "<tr>"
                              "<td>&nbsp;<img src=\":/images/zoom.png\" />"
                              "</td>"
                              "<td>"
                                  "<p>&nbsp;Найти документы (фильтр). Позволяет искать документ или группу документов по различным полям, как то номер, адресат и т.д."
                                  "Результат для входящих и исходящих писем выводится в соотвествующей вкладке. Регистр не различается</p>"
                              "</td>"
                          "</tr>"
                          "<tr>"
                              "<td>&nbsp;<img src=\":/images/times.png\" />"
                              "</td>"
                              "<td>"
                                  "<p>&nbsp;Сбросить фильтр. Выводит во всех вкладках полный список документов. Это действие имеет смысл только когда хотя бы в одной из вкладок отображены результаты поиска.</p>"
                              "</td>"
                          "</tr>"
                          "<tr>"
                              "<td>&nbsp;<img src=\":/images/printer.png\" />"
                              "</td>"
                              "<td>&nbsp;Распечатать список документов текущей вкладки.</td>"
                          "</tr>"

                  "<tr>"
                      "<td>&nbsp;<img src=\":/images/cog-outline.png\" />"
                      "</td>"
                      "<td>&nbsp;Выбрать расположение каталога с данными приложения.(Его стоит изменять только если вы понимаете что делаете.)</td>"
                  "</tr>"
                  "<tr>"
                      "<td>&nbsp;<img src=\":/images/help.png\" />"
                      "</td>"
                      "<td>&nbsp;Показать эту справку.</td>"
                  "</tr>"
                     "<tr>"
                         "<td><img src=\":/images/len.png\" width=\"40\" height=\"40\" align=\"middle\" />"
                         "</td>"
                         "<td>Выбор языка</td>"
                     "</tr>"
                          "<tr>"
                              "<td><img src=\":/images/info-large.png\" />"
                              "</td>"
                              "<td>Тут можно узнать моё имя и email и jabber</td>"
                          "</tr>"
                      "</tbody>"
                  "</table><br>"
                  "<p align=\"center\">Более подробную справку можно найти на <a href=\"http://kyrych.ru/44-dev/app/158-post\">kyrych.ru</a></p><br>"));
    about.setWindowIcon(QIcon(":/images/KlogoS.png"));
    about.setWindowTitle(tr("Справка:"));
    about.exec();
}

void MainWindow::slot_languege()
{
    LanguegeMenu* pmbl = new LanguegeMenu(this);
    if (pmbl->exec() == QDialog::Accepted)
    {

    }
    delete pmbl;
}
