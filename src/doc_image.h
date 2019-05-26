#ifndef DOC_IMAGE_H
#define DOC_IMAGE_H

#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QPainter>
#include <QDir>
#include "settings.h"
#include "declaration.h"
// Адаптер представляющий картинку документа
class doc_image
{
public:
    explicit doc_image(img_status ims);
    doc_image(const QImage &arg, const QString &adr, const QString &arg_number, img_status ims);
    bool set_image(const QImage &arg, const QString &adr,  const QString& number, img_status ims);
    void set_adr(const QString& arg);
    void set_uniq(const QString& arg);
    void set_number_doc(const QString& arg);
    QString get_adr() const;
    QString get_uniq() const;
    QString get_type() const;
    QString get_number_doc() const;
    QImage get_image() const;
    void del_image();
private:
    void set_type(img_status ims);
    QString im_hash(const QImage &arg) const;
    QString _adr_str{""};
    QString _uniq_str{""};
    QString type{""};
    QString number_doc{""};
    QString hash{""};
};

#endif // DOC_IMAGE_H
