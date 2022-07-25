#ifndef QFORMEXPERIDATA_H
#define QFORMEXPERIDATA_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QDataWidgetMapper>

namespace Ui {
class QFormExperiData;
}

class QFormExperiData : public QWidget
{
    Q_OBJECT

public:
    explicit QFormExperiData(QWidget *parent = nullptr);
    ~QFormExperiData();

private:
    Ui::QFormExperiData *ui;

    QSqlDatabase    DB;
    QSqlTableModel  *tblModel;
    QItemSelectionModel *theSelection;
    QDataWidgetMapper *dataMapper;
    void openTable(void);
    void getFieldNames(void);
};

#endif // QFORMEXPERIDATA_H
