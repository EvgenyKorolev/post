#include "my_model_in.h"

my_model_in::my_model_in(proxy_in *arg, QObject *parent) : QAbstractTableModel(parent)
{
    _model_data = arg;
}
int my_model_in::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
     return _model_data->count();
}
int my_model_in::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 9;
}
QVariant my_model_in::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
    if (role == Qt::DisplayRole){
        if (index.column() == 0){
            return QVariant::fromValue(_model_data->at(index.row()).get_doc_in_number());
        }
        if (index.column() == 1){
            return QVariant::fromValue(_model_data->at(index.row()).get_doc_out_number());
        }
        if (index.column() == 2){
            return QVariant::fromValue(_model_data->at(index.row()).get_in_date());
        }
        if (index.column() == 3){
            return QVariant::fromValue(_model_data->at(index.row()).get_send_rec());
        }
        if (index.column() == 4){
            return QVariant::fromValue(_model_data->at(index.row()).get_content());
        }
        if (index.column() == 5){
            return QVariant::fromValue(_model_data->at(index.row()).get_recipient());
        }
        if (index.column() == 6){
            return QVariant::fromValue(_model_data->at(index.row()).get_reception_date());
        }
        if (index.column() == 7){
            return QVariant::fromValue(_model_data->at(index.row()).get_worker());
        }
        if (index.column() == 8){
            if (_model_data->at(index.row()).is_control()){
                return QVariant(tr("Да"));
            } return QVariant("-");
        }
    }
    if (role ==  Qt::EditRole) {
        return QVariant::fromValue(_model_data->at(index.row()));

    }
    if (role == Qt::UserRole) {
        return QVariant("in");
    }
    }
    return QVariant();
}
bool my_model_in::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        if (!index.isValid()){
            _model_data->append(value.value<letter_in*>());
            return true;
        } else {
            _model_data->insert(index.row(), value.value<letter_in*>());
            return true;
        }
    }
    return false;
}
QVariant my_model_in::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch (section){
        case 0:
            return QVariant(tr("Входящий номер"));
        case 1:
            return QVariant(tr("Номер (исходящий)"));
        case 2:
            return QVariant(tr("Дата документа"));
        case 3:
            return QVariant(tr("Откуда поступил документ"));
        case 4:
            return QVariant(tr("Краткое содержание"));
        case 5:
            return QVariant(tr("Кому передан документ"));
        case 6:
            return QVariant(tr("Дата получения"));
        case 7:
            return QVariant(tr("Ответственный исполнитель"));
        case 8:
            return QVariant(tr("Контроль"));
        }
    }
    return QVariant();
}
Qt::ItemFlags my_model_in::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::ItemIsSelectable;
    }
    return flags;
}
