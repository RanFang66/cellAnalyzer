#include "ExperiSettings.h"

ExperiSettings::ExperiSettings(QObject *parent) : QObject(parent)
{
    dilutionRatio = DILU_RATIO_1_1;
    cellSize = SIZE_1_TO_10;
    name = QString::null;
    sampleId = QString::null;
}

const QString &ExperiSettings::getName() const
{
    return name;
}

void ExperiSettings::setName(const QString &newName)
{
    name = newName;
}

const QString &ExperiSettings::getSampleId() const
{
    return sampleId;
}

void ExperiSettings::setSampleId(const QString &newSampleId)
{
    sampleId = newSampleId;
}

int ExperiSettings::getDilutionRatio() const
{
    return dilutionRatio;
}

void ExperiSettings::setDilutionRatio(int newDilutionRatio)
{
    dilutionRatio = newDilutionRatio;
}

int ExperiSettings::getCellSize() const
{
    return cellSize;
}

void ExperiSettings::setCellSize(int newCellSize)
{
    cellSize = newCellSize;
}

int ExperiSettings::getCellType() const
{
    return cellType;
}

void ExperiSettings::setCellType(int newCellType)
{
    cellType = newCellType;
}
