#include "skeletonbuilder.h"
#include <QObjectPicker>




SkeletonBuilder::SkeletonBuilder(QVector<QVector<Joint> > _skeletonData, int _instant, Qt3DCore::QEntity *_root)
{
    this->skeletonData = _skeletonData;
    this->instantt = _instant;
    this->root = _root;
}

SkeletonBuilder::~SkeletonBuilder()
{
    delete this->root;
}

QVector<Joint> SkeletonBuilder::build()
{

    QVector<QVector<Joint>> data = this->skeletonData;
    QVector<Joint>  skeleton;
    for(int i=0 ; i <data.size() ; i++)
    {
        skeleton.append(data.at(i).at(instantt));
    }
    return skeleton;

}

Qt3DCore::QEntity * SkeletonBuilder::paintSkeleton( Qt3DCore::QEntity  *ls)
{
    this->root = ls;

    QVector<Joint> skeletonBase = this->build();
    ls= new Qt3DCore::QEntity(ls);

    Qt3DRender::QObjectPicker* picker = new Qt3DRender::QObjectPicker;
    ls->addComponent(picker);


    for(int i=0 ; i <skeletonBase.size() ; i++)
    {
        Qt3DCore::QEntity *sphereEntity = new Qt3DCore::QEntity(this->root);
        Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
       sphereMesh->setRadius(0.3);
       sphereMesh->setGenerateTangents(true);

        Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform;
        sphereTransform->setScale(0.98f);

           Joint Currento  = skeletonBase.at(i);

           QString jointName = Currento.getName();
           qDebug() <<Currento.getCoordinates() << Currento.getName()<< Qt::endl;
           sphereTransform->setTranslation(Currento.getCoordinates()*10);
           sphereTransform->setRotation(Currento.getQuaternion());


           auto *materialSphere = new Qt3DExtras::QPhongMaterial(sphereMesh);
           //materialSphere->setAmbient(QColor(0, 155, 0, 127));
          // QString jointName = Currento.getName();
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
               sphereEntity->addComponent(sphereMesh);
               sphereEntity->addComponent(sphereTransform);
               sphereEntity->addComponent(materialSphere);



              //sphereEntity->setParent(global);

           //}
    }

    return this->root;
}

void SkeletonBuilder::unpaintSkeleton(Qt3DCore::QEntity* _deletingEntity )
{
    qDebug() << "im called here ---------------------------";
    //delete this->root;
    //this->root = this->paintSkeleton(new Qt3DCore::QEntity);
    foreach(Qt3DCore::QComponent* component, _deletingEntity->components()){
        _deletingEntity->removeComponent(component);
        delete(component);
        component = NULL;
    }


}

int SkeletonBuilder::getInstant()
{
    return instantt;
}

void SkeletonBuilder::setInstant(int _instantt)
{
    this->instantt = _instantt;
}

Qt3DCore::QEntity *SkeletonBuilder::getRoot()
{
    return root;
}

void SkeletonBuilder::setRoot(Qt3DCore::QEntity *_root)
{
    this->root = _root;
}


