#ifndef SKELETONBUILDER_H
#define SKELETONBUILDER_H

#include"joint.h"
#include <QObject>
#include <QVector3D>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include<QQuaternion>
class SkeletonBuilder
{
public:
    SkeletonBuilder(QVector<QVector<Joint>> _skeletonData);
    QVector<Joint> build();
private:
    QVector<QVector<Joint>> skeletonData;
    int time;
};

#endif // SKELETONBUILDER_H
