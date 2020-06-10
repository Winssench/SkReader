#ifndef JOINT_H
#define JOINT_H

#include<QString>
#include <QVector3D>
#include<QQuaternion>
#include<Qt3DCore>
#include<Qt3DExtras>

class Joint
{
public:
    Joint();
    Joint(const QString _jointname ,const QVector3D _coordiantes,const QQuaternion _quaternion );
    QVector3D getCoordinates();
    QQuaternion getQuaternion();
    QString getName();
    void setCoordinates(const QVector3D _coordiantes);
    void setQuaternion(const QQuaternion _quaternion);
    void paintJoint(Qt3DCore::QEntity* _root);
private:
    QString jointName;
    QVector3D coordinates;
    QQuaternion quaternion;

};

#endif // JOINT_H
