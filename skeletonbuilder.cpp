#include "skeletonbuilder.h"

SkeletonBuilder::SkeletonBuilder(QVector<QVector<Joint>> _skeletonData)
{
    this->skeletonData = _skeletonData;
}

QVector<Joint> SkeletonBuilder::build()
{
    QVector<QVector<Joint>> data = this->skeletonData;
    QVector<Joint>  skeleton;
    for(int i=0 ; i <data.size() ; i++)
    {
        skeleton.append(data.at(i).first());
    }
    return skeleton;
}
