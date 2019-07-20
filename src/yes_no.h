#ifndef YES_NO_H
#define YES_NO_H

#include <QObject>
#include <QDialog>

class yes_no : public QDialog
{
    Q_OBJECT
public:
    yes_no(const QString& arg1, const QString& arg2, QWidget* parent = nullptr);
};

#endif // YES_NO_H
