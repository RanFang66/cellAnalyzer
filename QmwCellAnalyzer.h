#ifndef QMWCELLANALYZER_H
#define QMWCELLANALYZER_H

#include <QMainWindow>
#include <SysDevices.h>
#include <ExperiSettings.h>
#include <QFormExperiData.h>
#include <QWdgtDebug.h>

QT_BEGIN_NAMESPACE
namespace Ui { class QmwCellAnalyzer; }
QT_END_NAMESPACE

class QmwCellAnalyzer : public QMainWindow
{
    Q_OBJECT

public:
    QmwCellAnalyzer(QWidget *parent = nullptr);
    ~QmwCellAnalyzer();

private slots:
    void on_btnConfirmInfo_clicked();

    void on_btnStart_clicked();

private:
    Ui::QmwCellAnalyzer *ui;

    SysDevices *dev;
    ExperiSettings *settings;
    QFormExperiData *experiData;
    QWdgtDebug *debugPage;

    void cellAnalyzerInit();
};
#endif // QMWCELLANALYZER_H
