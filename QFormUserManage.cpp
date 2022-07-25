#include "QFormUserManage.h"
#include "ui_QFormUserManage.h"

QFormUserManage::QFormUserManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormUserManage)
{
    ui->setupUi(this);
}

QFormUserManage::~QFormUserManage()
{
    delete ui;
}

void QFormUserManage::on_btnAddUser_clicked()
{

}
