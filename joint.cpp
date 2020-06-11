#include "joint.h"
#include<Qt3DCore/QEntity>

#include <Qt3DRender>

#include<QCylinderMesh>
#include<Qt3DExtras/QCylinderMesh>
#include<QQuaternion>

Joint::Joint()
{

}

Joint::Joint(const QString _jointname, const QVector3D _coordiantes, const QQuaternion _quaternion , const QString _jointStatus)
{
    this->jointName = _jointname;
    this->coordinates = _coordiantes;
    this->quaternion = _quaternion;
    this->jointStatus = _jointStatus;
}



QVector3D Joint::getCoordinates()
{
    return coordinates;
}

QQuaternion Joint::getQuaternion()
{
    return quaternion;
}

QString Joint::getName()
{
    return jointName;
}

QString Joint::getStatus()
{
    return jointStatus;
}


void Joint::setCoordinates(const QVector3D _coordiantes)
{
    this->coordinates = _coordiantes;
}


void Joint::setQuaternion(const QQuaternion _quaternion)
{
    this->quaternion = _quaternion;
}

void Joint::paintJoint(Qt3DCore::QEntity * _root)
{
    /*
        Qt3DExtras::QPhongMaterial *cylinderMaterial = new Qt3DExtras::QPhongMaterial();
        cylinderMaterial->setDiffuse(QColor(255, 0, 0, 127));

       Qt3DExtras::QCylinderMesh *cylinder = new  Qt3DExtras::QCylinderMesh();
       cylinder->setRadius(0.4);
       cylinder->setLength(2);
       cylinder->setRings(2);
       cylinder->setSlices(20);
       // CylinderMesh Transform
       Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform;
       cylinderTransform->setScale(0.5f);
       cylinderTransform->setRotation(quaternion);
       cylinderTransform->setTranslation(coordinates *10);




       _root->addComponent(cylinder);
       _root->addComponent(cylinderTransform);
       _root->addComponent(cylinderMaterial);

       */

}


