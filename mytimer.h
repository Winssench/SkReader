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

class MyTimer : public QObject
{
   Q_OBJECT

public:
    MyTimer( Qt3DCore::QEntity* root , QVector<Joint> _Current);
    QTimer *timer;

    Qt3DCore::QEntity* getRoot();
    void setRoot(Qt3DCore::QEntity* _a);
    void setBase(QVector<Joint> _base);
    QVector<Joint> getBase();
    void setI(int* _i);
    int* getI();
     void myslot(QVector<Joint> Current );
     void startTimer();

private:
    QVector<Joint> current;
    int* i ;
    Qt3DCore::QEntity* _root;
    QVector<Joint> spineBase;
public slots:

    void threadbuild();
};

#endif // MYTIMER_H
