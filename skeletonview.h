#ifndef SKELETONVIEW_H
#define SKELETONVIEW_H

#include <QWidget>

#include <QGuiApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DCore/QSkeleton>
#include <Qt3DCore/QJoint>
#include <Qt3DCore/QArmature>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>

#include <QPropertyAnimation>

#include "qt3dwindow.h"
#include "orbittransformcontroller.h"
#include "qorbitcameracontroller.h"
#include"skeleton.h"
#include <QDebug>

#include <Qt3DCore>
#include<QQuaternion>


#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometry>
#include"orbittransformcontroller.h"



#include"joint.h"
#include"mytimer.h"
#include"skeletonbuilder.h"
class SkeletonView : public QWidget
{
    Q_OBJECT
public:
    SkeletonView(QWidget *parent = 0);

    ~SkeletonView(){}


      QVector<QVector<Joint>> createScene();
};

#endif // SKELETONVIEW_H
