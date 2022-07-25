#ifndef EXPERISETTINGS_H
#define EXPERISETTINGS_H

#include <QObject>

class ExperiSettings : public QObject
{
    Q_OBJECT
public:
    enum DilutionRatio{
        DILU_RATIO_1_1 = 1,
        DILU_RATIO_1_2,
        DILU_RATIO_1_3,
        DILU_RATIO_1_4,
        DILU_RATIO_1_5,
        DILU_RATIO_1_6,
        DILU_RATIO_1_7,
        DILU_RATIO_1_8,
        DILU_RATIO_1_9,
        DILU_RATIO_1_10,
    };
    enum CellSize {
        SIZE_1_TO_10 = 1,
        SIZE_10_TO_20,
        SIZE_20_TO_30,
        SIZE_30_TO_40,
        SIZE_40_TO_50,
        SIZE_50_TO_60,
    };

    explicit ExperiSettings(QObject *parent = nullptr);

    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getSampleId() const;
    void setSampleId(const QString &newSampleId);
    int getDilutionRatio() const;
    void setDilutionRatio(int newDilutionRatio);
    int getCellSize() const;
    void setCellSize(int newCellSize);
    int getCellType() const;
    void setCellType(int newCellType);

signals:

private:
    QString name;
    QString type;
    QString sampleId;
    int     dilutionRatio;
    int     cellSize;
    int     cellType;
};

#endif // EXPERISETTINGS_H
