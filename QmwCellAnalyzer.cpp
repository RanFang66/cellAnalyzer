#include "QmwCellAnalyzer.h"
#include "ui_QmwCellAnalyzer.h"

QmwCellAnalyzer::QmwCellAnalyzer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QmwCellAnalyzer)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowFullscreenButtonHint);
    int debugTabIndex = 0;
    int dataTabIndex = 0;

    dev = new SysDevices(this);
    debugPage = new QWdgtDebug(this);
    experiData = new QFormExperiData(this);
    debugPage->setDev(dev);
    debugTabIndex = ui->tabWidget->addTab(debugPage, "Debug");
    dataTabIndex = ui->tabWidget->addTab(experiData, "Data");

    cellAnalyzerInit();


//    dev->serial()->connect();
//    dev->camera()->open();
}

QmwCellAnalyzer::~QmwCellAnalyzer()
{
    delete ui;
}

void QmwCellAnalyzer::cellAnalyzerInit()
{
    ui->comboExpriType->clear();
    ui->comboExpriType->addItem("AOPI Cell Viability");
    ui->comboExpriType->addItem("Cell Counter");

    ui->comboCellType->clear();
    ui->comboCellType->addItem("Human T");
    ui->comboCellType->addItem("Plant");

    ui->comboDilutionRatio->clear();
    ui->comboCellType->addItem("1:1");

    ui->comboSize->clear();
    ui->comboSize->addItem("1-5");
    ui->comboSize->addItem("5-10");
}


void QmwCellAnalyzer::on_btnConfirmInfo_clicked()
{
    settings->setName(ui->editExpriName->text());
    settings->setSampleId(ui->editSampleId->text());
    settings->setCellSize(ui->comboSize->currentIndex());
    settings->setCellType(ui->comboCellType->currentIndex());
    settings->setDilutionRatio(ui->comboDilutionRatio->currentIndex());
}

void QmwCellAnalyzer::on_btnStart_clicked()
{
    if (dev->chipState()) {

    } else {

    }
}

