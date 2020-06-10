#include "orbittransformcontroller.h"
#include <Qt3DCore/qtransform.h>



Orbittransformcontroller::Orbittransformcontroller(QObject *parent , Joint* _joint)
    : QObject(parent)
       , m_target(nullptr)
       , m_matrix()
       , m_radius(1.0f)
       , joint(_joint)
{
    //rotStuff

    this->m_angle = joint->getQuaternion().scalar();
    this->m_rotX = joint->getQuaternion().x();
    this->m_rotY = joint->getQuaternion().y();
    this->m_rotZ = joint->getQuaternion().z();

    //posStuff
    this->m_posX = joint->getCoordinates().x();
    this->m_posY = joint->getCoordinates().y();
    this->m_posZ = joint->getCoordinates().z();

}

void Orbittransformcontroller::setTarget(Qt3DCore::QTransform *target)
{
    if (m_target != target) {
        m_target = target;
        emit targetChanged();
    }
}

Qt3DCore::QTransform *Orbittransformcontroller::target() const
{
    return m_target;
}

void Orbittransformcontroller::setRadius(float radius)
{
    if (!qFuzzyCompare(radius, m_radius)) {
        m_radius = radius;
        updateMatrix();
        emit radiusChanged();
    }
}
float Orbittransformcontroller::radius() const
{
    return m_radius;
}
void Orbittransformcontroller::setAngle(float angle)
{
    if (!qFuzzyCompare(angle, m_angle)) {
        m_angle = angle;
        updateMatrix();
        emit angleChanged();
    }
}
float Orbittransformcontroller::angle() const
{
    return m_angle;
}

void Orbittransformcontroller::setRotX(float rotX)
{
    if (!qFuzzyCompare(rotX, m_rotX)) {
        //m_angle = angle;
        m_rotX = rotX;
        updateMatrix();
        emit rotXChanged();
    }
}

float Orbittransformcontroller::rotX() const
{
    return m_rotX;
}

void Orbittransformcontroller::setRotY(float rotY)
{
    if (!qFuzzyCompare(rotY, m_rotY)) {
        //m_angle = angle;
        m_rotY = rotY;
        updateMatrix();
        emit rotYChanged();
    }
}

float Orbittransformcontroller::rotY() const
{
    return m_rotY;
}

void Orbittransformcontroller::setRotZ(float rotZ)
{
    if (!qFuzzyCompare(rotZ, m_rotZ)) {
        //m_angle = angle;
        m_rotZ = rotZ;
        updateMatrix();
        emit rotZChanged();
    }
}

float Orbittransformcontroller::rotZ() const
{
    return m_rotZ;
}

void Orbittransformcontroller::setPosX(float posX)
{
    if (!qFuzzyCompare(posX, m_posX)) {
        //m_angle = angle;
        m_posX = posX;
        updateMatrix();
        emit posXChanged();
    }
}
float Orbittransformcontroller::posX() const
{
    return m_posX;
}

void Orbittransformcontroller::setPosY(float posY)
{
    if (!qFuzzyCompare(posY, m_posY)) {
        //m_angle = angle;
        m_posY = posY;
        updateMatrix();
        emit posYChanged();
    }
}
float Orbittransformcontroller::posY() const
{
    return m_posY;
}

void Orbittransformcontroller::setPosZ(float posZ)
{
    if (!qFuzzyCompare(posZ, m_posZ)) {
        //m_angle = angle;
        m_posZ = posZ;
        updateMatrix();
        emit posZChanged();
    }
}
float Orbittransformcontroller::posZ() const
{
    return m_posZ;
}

void Orbittransformcontroller::updateMatrix()
{
    m_matrix.setToIdentity();
    //m_matrix.rotate(m_angle,joint->getCoordinates());
    m_matrix.rotate(m_angle,m_rotX, m_rotY,m_rotZ);
    //m_matrix.translate(joint->getCoordinates()*10);
    m_matrix.translate(m_posX,m_posY,m_posZ);
    m_target->setMatrix(m_matrix);

}
