#include "my_model_out.h"

my_model_out::my_model_out(proxy_out *arg, QObject *parent) : QAbstractTableModel(parent)
{
    _model_data = arg;
}
int my_model_out::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
     return _model_data->count();
}
int my_model_out::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 7;
}
QVariant my_model_out::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
    if (role == Qt::DisplayRole){
        if (index.column() == 0){
            return QVariant::fromValue(_model_data->at(index.row()).get_blank_number());
        }
        if (index.column() == 1){
            return QVariant::fromValue(_model_data->at(index.row()).get_doc_out_number());
        }
        if (index.column() == 2){
            return QVariant::fromValue(_model_data->at(index.row()).get_send_rec());
        }
        if (index.column() == 3){
            return QVariant::fromValue(_model_data->at(index.row()).get_content());
        }
        if (index.column() == 4){
            return QVariant::fromValue(_model_data->at(index.row()).get_worker());
        }
        if (index.column() == 5){
            return QVariant::fromValue(_model_data->at(index.row()).get_notice());
        }
        if (index.column() == 6){
            return QVariant::fromValue(_model_data->at(index.row()).get_sys_data());
        }
    }
    if (role ==  Qt::EditRole) {
        return QVariant::fromValue(_model_data->at(index.row()));
    }
    if (role == Qt::UserRole) {
        return QVariant("out");
    }
    }
    return QVariant();
}
bool my_model_out::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        if (!index.isValid()){
            _model_data->append(value.value<letter_out*>());
            return true;
        } else {
            _model_data->insert(index.row(), value.value<letter_out*>());
            return true;
        }
    }
    return false;
}
QVariant my_model_out::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch (section){
        case 0:
            return QVariant(tr("№ фирменного бланка"));
        case 1:
            return QVariant(tr("Исходящий № док-та"));
        case 2:
            return QVariant(tr("Корреспондент (кому направлен)"));
        case 3:
            return QVariant(tr("Краткое содержание"));
        case 4:
            return QVariant(tr("Ответственный исполнитель"));
        case 5:
            return QVariant(tr("Примечание"));
        case 6:
            return QVariant(tr("Дата регистрации"));
        }
    }
    return QVariant();
}
Qt::ItemFlags my_model_out::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::ItemIsSelectable;
    }
    return flags;
}
