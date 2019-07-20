#include "mainwindow.h"
#include <QSplashScreen>
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QFile>
#include "settings.h"

static const QString SYSTEM_LOCALE = QLocale::system().name();

QString generateTrFileName( const QString& locale ) {
    return QString( "i18ndemo_%1" ).arg( locale );
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap(":/images/st0.png"));
    QTranslator translator;
    if(translator.load(generateTrFileName(SYSTEM_LOCALE), ".")) {
        a.installTranslator( &translator );
    }
    settings::getInatance();
    splash.show();
    MainWindow w;
    splash.finish(&w);
    w.show();
    return a.exec();
}
