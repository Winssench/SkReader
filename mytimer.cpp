#include "mytimer.h"

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



MyTimer::MyTimer( Qt3DCore::QEntity* root , QVector<Joint> current)
{
    timer = new QTimer(this);

    this->current = current;

    this->_root = root;

    //this->spineBase = _base;
     //this->_root = new Qt3DCore::QEntity;
    connect(timer,SIGNAL(timeout()), this,SLOT(threadbuild()));
  //  this->_root = new Qt3DCore::QEntity;

    //timer->start(1000);
    this->timer->start(500);


}

Qt3DCore::QEntity *MyTimer::getRoot()
{
    return _root;
}

void MyTimer::setRoot(Qt3DCore::QEntity *_a)
{
    this->_root->setParent(_a);
}

void MyTimer::setBase(QVector<Joint> _base)
{
    this->spineBase = _base;
}

QVector<Joint> MyTimer::getBase()
{
    return this->spineBase;
}

/*
void MyTimer::setBase(QVector<Joint> *_base)
{
    spineBase = _base;
}

QVector<Joint> *MyTimer::getBase()
{
    return spineBase;
}
*/

void MyTimer::setI(int *_i)
{
    this->i= _i;
}

int *MyTimer::getI()
{
    return this->i;
}

void MyTimer::threadbuild()
{


   //Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity(_root);
   //Qt3DExtras::Qt3DWindow view;
   // Camera


        //this->_root = new Qt3DCore::QEntity;
       myslot(this->current );









}

void MyTimer::myslot(QVector<Joint> Current  )
{

     Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(0.3);
    sphereMesh->setGenerateTangents(true);

     Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform;
      sphereTransform->setScale(0.9f);
        //sphereTransform->setRotation(jointQuaternion);


        /*
        Qt3DExtras::QCylinderMesh *sphereMesh= new  Qt3DExtras::QCylinderMesh;
        sphereMesh->setRadius(0.4);
        sphereMesh->setLength(2);
        sphereMesh->setRings(2);
        sphereMesh->setSlices(20);


        Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform;
        sphereTransform->setScale(0.5f);
        */
        //Joint Current = this->spineBase.at(i).at(j);
        //QVector<Joint> test = this->spineBase.at(i);
        /*
        Joint Currento  = test.at(j);
        test.removeAt(j);

        this->spineBase.removeAt(i);
        this->spineBase.insert(i,test);
        */
     //   Joint Current = this->spineBase.at(8);
        Joint Currento  = Current.first();
        qDebug() << Currento.getName() << Qt::endl;
        sphereTransform->setTranslation(Currento.getCoordinates()*10);
        sphereTransform->setRotation(Currento.getQuaternion());
        this->current.removeFirst();

        auto *materialSphere = new Qt3DExtras::QPhongMaterial(sphereMesh);
        //materialSphere->setAmbient(QColor(0, 155, 0, 127));
        QString jointName = Currento.getName();
        {

        if(jointName == "SpineBase")
        {
            materialSphere->setAmbient(QColor(0, 0, 0, 127));
        }
        if(jointName == "SpineMid")
        {
            materialSphere->setAmbient(QColor(0, 0, 0, 127));
        }

        if(jointName == "Neck")
        {
            materialSphere->setAmbient(QColor(0, 0, 255, 127));
        }
        if(jointName == "Head")
        {
            materialSphere->setAmbient(QColor(0, 0, 255, 127));
        }


        // Lefthand
        if(jointName == "ShoulderLeft")
        {
            materialSphere->setAmbient(QColor(255, 0, 255, 127));
        }

        if(jointName == "ElbowLeft")
        {
            materialSphere->setAmbient(QColor(255, 0, 255, 127));
        }
        if(jointName == "WristLeft")
        {
            materialSphere->setAmbient(QColor(255, 0, 255, 127));
        }

        //Probleme in Handleft
        if(jointName == "HandLeft")
        {
            materialSphere->setAmbient(QColor(255, 0, 255, 127));
        }


        //Right Hands
        if(jointName == "ShoulderRight")
        {
            materialSphere->setAmbient(QColor(255, 0, 255, 127));
        }




        if(jointName == "ElbowRight")
        {
            materialSphere->setAmbient(QColor(255, 0, 255, 127));
        }

        //Problem Wrist and Hand Right
        if(jointName == "WristRight")
        {
            materialSphere->setAmbient(QColor(255, 0, 0, 127));
        }
        if(jointName == "HandRight")
        {
            materialSphere->setAmbient(QColor(255, 0, 0, 127));
        }


        // legs Part
        if(jointName == "HipLeft")
        {
            materialSphere->setAmbient(QColor(0, 0, 255, 127));
        }
        if(jointName == "KneeLeft")
        {
            materialSphere->setAmbient(QColor(0, 0, 255, 127));
        }
        //Problme here
        if(jointName == "AnkleLeft")
        {
            materialSphere->setAmbient(QColor(0, 0, 255, 127));
        }
        //Problem here too
        if(jointName == "FootLeft")
        {
            materialSphere->setAmbient(QColor(0, 0, 255, 127));
        }


        //Probleme here
        if(jointName == "HipRight")
        {
            materialSphere->setAmbient(QColor(0, 255, 0, 127));
        }

        if(jointName == "KneeRight")
        {
            materialSphere->setAmbient(QColor(0, 255, 0, 127));
        }
        //Problem here
        if(jointName == "AnkleRight")
        {
            materialSphere->setAmbient(QColor(0, 255, 0, 127));
        }
        if(jointName == "FootRight")
        {
            materialSphere->setAmbient(QColor(0, 255, 0, 127));
        }

        }


        _root->addComponent(sphereMesh);
        _root->addComponent(sphereTransform);
        _root->addComponent(materialSphere);



}

void MyTimer::startTimer()
{
        this->timer->start(2000);
}
