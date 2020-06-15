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
    SkeletonBuilder(QVector<QVector<Joint>> _skeletonData , int _instant ,  Qt3DCore::QEntity* _root);
    ~SkeletonBuilder();
    QVector<Joint> build();

    Qt3DCore::QEntity * paintSkeleton( Qt3DCore::QEntity*  ls);
    void unpaintSkeleton(Qt3DCore::QEntity* _deletingEntity);

    int getInstant();
    void setInstant(int _instantt);
    Qt3DCore::QEntity*  getRoot();
    void setRoot(Qt3DCore::QEntity* _root);
private:
    QVector<QVector<Joint>> skeletonData;

    int instantt;
     Qt3DCore::QEntity* root;
};

#endif // SKELETONBUILDER_H
