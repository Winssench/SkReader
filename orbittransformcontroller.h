#ifndef ORBITTRANSFORMCONTROLLER_H
#define ORBITTRANSFORMCONTROLLER_H

#include <QObject>
#include <QMatrix4x4>
#include"joint.h"

namespace Qt3DCore {
class QTransform;

}
class Orbittransformcontroller  : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QTransform* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)

    //Quaternion
    Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(float rotX READ rotX WRITE setRotX NOTIFY rotXChanged)
    Q_PROPERTY(float rotY READ rotY WRITE setRotY NOTIFY rotYChanged)
    Q_PROPERTY(float rotZ READ rotZ WRITE setRotZ NOTIFY rotZChanged)
    //Position
    Q_PROPERTY(float posX READ posX WRITE setPosX NOTIFY posXChanged)
    Q_PROPERTY(float posY READ posY WRITE setPosY NOTIFY posYChanged)
    Q_PROPERTY(float posZ READ posZ WRITE setPosZ NOTIFY posZChanged)
public:
    Orbittransformcontroller(QObject *parent , Joint * _joint);
    void setTarget(Qt3DCore::QTransform *target);
    Qt3DCore::QTransform *target() const;

    void setRadius(float radius);
    float radius() const;

    //rotStuff
    void setAngle(float angle);
    float angle() const;
    void setRotX(float rotX);
    float rotX() const;
    void setRotY(float rotY);
    float rotY() const;
    void setRotZ(float rotZ);
    float rotZ() const;

    //posStuff
    void setPosX(float posX);
    float posX() const;
    void setPosY(float posY);
    float posY() const;
    void setPosZ(float posZ);
    float posZ() const;
signals:
    void targetChanged();
    void radiusChanged();
    //rotStuff
    void angleChanged();
    void rotXChanged();
    void rotYChanged();
    void rotZChanged();
    //posStuff
    void posXChanged();
    void posYChanged();
    void posZChanged();

protected:
    void updateMatrix();

private:
    Qt3DCore::QTransform *m_target;
    QMatrix4x4 m_matrix;
    float m_radius;
    //rotStuff
    float m_angle;
    float m_rotX;
    float m_rotY;
    float m_rotZ;

    //posStuff
    float m_posX;
    float m_posY;
    float m_posZ;

    //others
    Joint *joint;
};

#endif // ORBITTRANSFORMCONTROLLER_H
