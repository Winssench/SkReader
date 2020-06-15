#ifndef MYTIMER_H
#define MYTIMER_H
#include<QtCore>
#include<QDebug>
#include<QtCore>
#include<QDebug>
#include<Qt3DCore/QEntity>

#include <Qt3DRender>

#include<QCylinderMesh>
#include<Qt3DExtras/QCylinderMesh>
#include<QQuaternion>

#include<QString>
#include <QVector3D>
#include<QQuaternion>
#include<Qt3DCore>
#include<Qt3DExtras>
#include <QRandomGenerator>
#include <qglobal.h>
#include"joint.h"
#include"skeletonbuilder.h"

class MyTimer : public QObject
{
   Q_OBJECT

public:
    MyTimer( Qt3DCore::QEntity* root , QVector<Joint> _Current);
    MyTimer( Qt3DCore::QEntity* root , QVector<SkeletonBuilder*> _CurrentBuilder);
    QTimer *timer;

    Qt3DCore::QEntity* getRoot();
    void setRoot(Qt3DCore::QEntity* _a);
    void setBase(QVector<Joint> _base);
    QVector<Joint> getBase();
    void setI(int _i);
    int getI();
     void myslot(QVector<Joint> Current );
      Qt3DCore::QEntity* myslot(QVector<SkeletonBuilder*> _CurrentBuilder);
     void startTimer();

    QVector<SkeletonBuilder*> getSkeletonBuilder();
    void setSkeletonBuilder(QVector<SkeletonBuilder*>   _CurrentBuilder);

    void deleteChildrenRecursively(Qt3DCore::QNodeVector& vector);
    void delete_entity_recursively(Qt3DCore::QNode *node);

private:
    QVector<Joint> current;
    int i ;
    Qt3DCore::QEntity* _root;
    QVector<Joint> spineBase;

    QVector<Qt3DCore::QEntity> entites;

    QVector<SkeletonBuilder*> CurrentBuilder;
public slots:
    void threadSkeletonbuild();

    void threadbuild();
};

#endif // MYTIMER_H
