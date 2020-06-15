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


#include <Qt3DCore/QEntity>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QLayer>
#include <Qt3DRender/QLayerFilter>
#include <Qt3DRender/QViewport>



MyTimer::MyTimer( Qt3DCore::QEntity* root , QVector<Joint> current)
{
    //timer = new QTimer(this);

   // this->current = current;

    //this->_root = root;

    //this->spineBase = _base;
     //this->_root = new Qt3DCore::QEntity;
   // connect(timer,SIGNAL(timeout()), this,SLOT(threadbuild()));
  //  this->_root = new Qt3DCore::QEntity;

    //timer->start(1000);
    //this->timer->start(500);


}

MyTimer::MyTimer(Qt3DCore::QEntity *root, QVector<SkeletonBuilder*> _CurrentBuilder)
{

    //delete_entity_recursively(_root);
    timer = new QTimer(this);

    this->CurrentBuilder = _CurrentBuilder;
    this->i = 0;




    //this->spineBase = _base;
     this->_root = new Qt3DCore::QEntity;
    //this->_root = new Qt3DCore::QEntity;
    connect(timer,SIGNAL(timeout()), this,SLOT(threadSkeletonbuild()));


    //timer->start(1000);
    this->timer->start(900);



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

void MyTimer::setI(int _i)
{
    this->i= _i;
}

int MyTimer::getI()
{
    return this->i;
}

void MyTimer::threadbuild()
{


   //Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity(_root);
   //Qt3DExtras::Qt3DWindow view;
   // Camera



       this->_root = new Qt3DCore::QEntity;

       myslot(this->current );












}

void MyTimer::myslot(QVector<Joint> Current  )
{

    if(Current.first().getStatus() == "TRACKED")
    {
        Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
       sphereMesh->setRadius(0.3);
       sphereMesh->setGenerateTangents(true);

        Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform;
        sphereTransform->setScale(0.98f);
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

           qDebug() <<Currento.getCoordinates() << Currento.getName()<< Qt::endl;
           sphereTransform->setTranslation(Currento.getCoordinates()*10);
           sphereTransform->setRotation(Currento.getQuaternion());
           //this->current.removeFirst();

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

           //if(Currento.getStatus() == "TRACKED")
           //{
               _root->addComponent(sphereMesh);
               _root->addComponent(sphereTransform);
               _root->addComponent(materialSphere);
           //}



    }









}

 Qt3DCore::QEntity * MyTimer::myslot(QVector<SkeletonBuilder*> _CurrentBuilder)
{
    SkeletonBuilder* Currento = _CurrentBuilder.first();

     Qt3DCore::QEntity* test = new Qt3DCore::QEntity(_root);

     Currento->paintSkeleton(test);
     CurrentBuilder.removeFirst();

     Currento->unpaintSkeleton(_root);

     return test;
}

void MyTimer::startTimer()
{
    this->timer->start(500);
}

QVector<SkeletonBuilder*> MyTimer::getSkeletonBuilder()
{
    return this->CurrentBuilder;
}

void MyTimer::setSkeletonBuilder(QVector<SkeletonBuilder*> _CurrentBuilder)
{
    this->CurrentBuilder = _CurrentBuilder;
}

void MyTimer::deleteChildrenRecursively(Qt3DCore::QNodeVector &
vector)
{
    foreach(Qt3DCore::QNode* node, vector){
            Qt3DCore::QEntity* entity = (Qt3DCore::QEntity*)node;
            QList<Qt3DCore::QComponent*> componentsToDelete;
            foreach(Qt3DCore::QComponent* component, entity->components()){
                entity->removeComponent(component);
                delete(component);
                component = NULL;
            }
            //deleteChildrenRecursively(node->childNodes());
            delete(node);
            node = NULL;
        }
}

void MyTimer::threadSkeletonbuild()
{
    //this->_root = new Qt3DCore::QEntity();
    myslot(this->CurrentBuilder);
}

void delete_entity_recursively(Qt3DCore::QNode *node){
    Qt3DCore::QEntity* entity = dynamic_cast<Qt3DCore::QEntity*>(node);
    if(entity == nullptr){
        return;
    }
    auto components_to_delete = entity->components();
    foreach(auto *component,components_to_delete){
        entity->removeComponent(component);
        delete(component);
        component = nullptr;
    }
    auto children_nodes = entity->childNodes();
    foreach(auto *child_node, children_nodes){
        delete_entity_recursively(child_node);
    }
    delete entity;
    entity = nullptr;
}
