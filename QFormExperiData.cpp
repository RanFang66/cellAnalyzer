#include "QFormExperiData.h"
#include "ui_QFormExperiData.h"

QFormExperiData::QFormExperiData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormExperiData)
{
    ui->setupUi(this);

    ui->dataTbl->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->dataTbl->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dataTbl->setAlternatingRowColors(true);

    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("ExperiData.db");

    if (!DB.open()) {
        QMessageBox::warning(this, "Error", "Open data base failed", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    openTable();
}



QFormExperiData::~QFormExperiData()
{
    DB.close();
    delete ui;
}

void QFormExperiData::openTable()
{
   tblModel = new QSqlTableModel(this, DB);
   tblModel->setTable("ExperiResult");
   tblModel->setSort(tblModel->fieldIndex("startTime"), Qt::DescendingOrder);
   tblModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
   if (!(tblModel->select())) {
       QMessageBox::critical(this, "Error", "Open data table failed, error info: \n" + tblModel->lastError().text(), QMessageBox::Ok, QMessageBox::NoButton);
       return;
   }

   tblModel->setHeaderData(tblModel->fieldIndex("experiName"), Qt::Horizontal, "Experiment Name");
   tblModel->setHeaderData(tblModel->fieldIndex("startTime"), Qt::Horizontal, "Experiment Time");
   tblModel->setHeaderData(tblModel->fieldIndex("sampleId"), Qt::Horizontal, "Sample ID");
   tblModel->setHeaderData(tblModel->fieldIndex("userId"), Qt::Horizontal, "User Name");
   tblModel->setHeaderData(tblModel->fieldIndex("cellType"), Qt::Horizontal, "Cell Type");
   tblModel->setHeaderData(tblModel->fieldIndex("viability"), Qt::Horizontal, "Viability");
   tblModel->setHeaderData(tblModel->fieldIndex("cellConc"), Qt::Horizontal, "Cell Concentration");
   tblModel->setHeaderData(tblModel->fieldIndex("liveCellConc"), Qt::Horizontal, "Live Cell Concentration");
   tblModel->setHeaderData(tblModel->fieldIndex("deadCellConc"), Qt::Horizontal, "Dead Cell Concentration");
   tblModel->setHeaderData(tblModel->fieldIndex("totalCellNum"), Qt::Horizontal, "Total Cell Number");
   tblModel->setHeaderData(tblModel->fieldIndex("liveCellNum"), Qt::Horizontal, "Live Cell Number");
   tblModel->setHeaderData(tblModel->fieldIndex("deadCellNum"), Qt::Horizontal, "Dead Cell Number");
   tblModel->setHeaderData(tblModel->fieldIndex("avgDiameter"), Qt::Horizontal, "Average Diameter");
   tblModel->setHeaderData(tblModel->fieldIndex("avgCompactness"), Qt::Horizontal, "Average Compactness");
   tblModel->setHeaderData(tblModel->fieldIndex("aggregateRate"), Qt::Horizontal, "Aggregate Rate");

   theSelection = new QItemSelectionModel(tblModel);
   ui->dataTbl->setModel(tblModel);
   ui->dataTbl->setSelectionModel(theSelection);

//   dataMapper = new QDataWidgetMapper();
//   dataMapper->setModel(tblModel);
//   dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
//   dataMapper->addMapping(ui->)





}
