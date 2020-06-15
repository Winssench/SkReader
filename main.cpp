/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
#include"skeletonview.h"

#include <QApplication>

float value = -2;
float divideValue = 6 ;

void drawLine(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity *_rootEntity)
{
    {
    auto *geometry = new Qt3DRender::QGeometry(_rootEntity);

    // position vertices (start and end)
    QByteArray bufferBytes;
    bufferBytes.resize(3 * 2 * sizeof(float)); // start.x, start.y, start.end + end.x, end.y, end.z
    float *positions = reinterpret_cast<float*>(bufferBytes.data());


     *positions++ = start.x() * divideValue;
     *positions++ = start.y() * divideValue;
    *positions++ = start.z()* divideValue;
    *positions++ = end.x() * divideValue;
    *positions++ = end.y() * divideValue;
    *positions++ = end.z() * divideValue;



     //qDebug()<< "start after" << "( " << start.x()<<  ","<<start.y()<< ","<< start.z()<<  ")"<< Qt::endl;

    auto *buf = new Qt3DRender::QBuffer(geometry);
    buf->setData(bufferBytes);

    auto *positionAttribute = new Qt3DRender::QAttribute(geometry);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(buf);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(2);
    geometry->addAttribute(positionAttribute); // We add the vertices in the geometry

    // connectivity between vertices
    QByteArray indexBytes;
    indexBytes.resize(2 * sizeof(unsigned int)); // start to end
    unsigned int *indices = reinterpret_cast<unsigned int*>(indexBytes.data());
    *indices++ = 0;
    *indices++ = 1;

    auto *indexBuffer = new Qt3DRender::QBuffer(geometry);
    indexBuffer->setData(indexBytes);

    auto *indexAttribute = new Qt3DRender::QAttribute(geometry);
    indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
    indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setCount(2);
    geometry->addAttribute(indexAttribute); // We add the indices linking the points in the geometry

    // mesh
    auto *line = new Qt3DRender::QGeometryRenderer(_rootEntity);
    line->setGeometry(geometry);
    line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    auto *materialos = new Qt3DExtras::QPhongMaterial(_rootEntity);
    materialos->setAmbient(color);



    // entity
    auto *lineEntity = new Qt3DCore::QEntity(_rootEntity);
    lineEntity->addComponent(line);
    //lineEntity->addComponent(sphereMesh);
    lineEntity->addComponent(materialos);
    }

}
QVector<QVector<Joint>> createScene()
{

    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;


    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);

    Skeleton *sk = new Skeleton("/Users/chichaouiomar/Documents/Projet2A/Mskeleton.csv.txt");
    QVector<QVector3D> vectors = sk->getVectors();
    QVector<QString> names = sk->getNames();
    QVector<QString> status = sk->getStatus();
    QVector<QQuaternion> quaternions = sk->getQuaternions();
    QVector<float> timesImported = sk->getTimes();

    QVectorIterator<QVector3D> i(vectors);
    QVectorIterator<QString> j(names);
    QVectorIterator<QQuaternion> k(quaternions);
    QVectorIterator<float> t(timesImported);


    QVector3D current = QVector3D(-0.1100359,-0.1038915,2.965061);
    QVector3D jointCoordinates = QVector3D(0,0,0);

    QString jointName ="";
    QString jointStatus = "";

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    int vartest = 0;

    int o = 1;
    int p = 0;


    // creation
    Qt3DCore::QEntity *sphereEntity = new Qt3DCore::QEntity(rootEntity);

    Qt3DExtras::QCylinderMesh *sphereMesh= new  Qt3DExtras::QCylinderMesh();
    sphereMesh->setRadius(0.4);
    sphereMesh->setLength(2);
    sphereMesh->setRings(2);
    sphereMesh->setSlices(20);


    Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform;
    sphereTransform->setScale(0.5f);
    sphereTransform->setRotation(QQuaternion(0,QVector3D(0,0,0)));



    sphereTransform->setTranslation(jointCoordinates*10);

    auto *materialSphere = new Qt3DExtras::QPhongMaterial(rootEntity);
    materialSphere->setAmbient(QColor(0, 0, 0, 127));


    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(sphereTransform);
    sphereEntity->addComponent(materialSphere);
    Joint *jtest ;
    QVector<Joint> spinBaseJoint;
    QVector<Joint> spinMidJoint;
    QVector<Joint> neckJoint;
    QVector<Joint> headJoint;
    QVector<Joint> shoulderLeftJoint;
    QVector<Joint> elbowLeftJoint;
    QVector<Joint> wristLeftJoint;
    QVector<Joint> handLeftJoint;
    QVector<Joint> shoulderRightJoint;
    QVector<Joint> elbowRightJoint;
    QVector<Joint> wristRightJoint;
    QVector<Joint> handRightJoint;
    QVector<Joint> hipLeftJoint;
    QVector<Joint> kneeLeftJoint;
    QVector<Joint> ankleLLeftJoint;
    QVector<Joint> footLeftJoint;
    QVector<Joint> hipRightJoint;
    QVector<Joint> kneeRightJoint;
    QVector<Joint> ankleLRightJoint;
    QVector<Joint> footRightJoint;

    QVector<Joint> spineShoulderJoint;
    QVector<Joint> handTipLeftJoint;
    QVector<Joint> thumbLeftJoint;
    QVector<Joint> handTipRightJoing;
    QVector<Joint> thumbRightJoing;








    //refacturing
    while(o<= 218)
    {
        while(p<25 * o)
        {
            jointCoordinates = vectors.at(p);
            jointName = names.at(p);
            jointStatus = status.at(p);
            QQuaternion jointQuaternion = quaternions.at(p);

            if(jointName == "SpineBase"){
                jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                spinBaseJoint.append(*jtest);

            }
            if(jointName == "SpineMid")
            {
                 jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                spinMidJoint.append(*jtest);
            }

            if(jointName == "Neck")
            {
                   jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                  neckJoint.append(*jtest);
            }
            if(jointName == "Head")
            {
                   jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                  headJoint.append(*jtest);
            }
            if(jointName == "ShoulderLeft")
            {
                  jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                 shoulderLeftJoint.append(*jtest);
            }

            if(jointName == "ElbowLeft")
            {
                  jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                 elbowLeftJoint.append(*jtest);
            }
            if(jointName == "WristLeft")
            {
                  jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                 wristLeftJoint.append(*jtest);
            }

            if(jointName == "HandLeft")
            {
                 jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                handLeftJoint.append(*jtest);
            }
            if(jointName == "ShoulderRight")
            {
                 jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                shoulderRightJoint.append(*jtest);
            }
            if(jointName == "ElbowRight")
            {
                  jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                 elbowRightJoint.append(*jtest);
            }

            if(jointName == "WristRight")
            {
                 jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                wristRightJoint.append(*jtest);
            }
            if(jointName == "HandRight")
            {
                jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                handRightJoint.append(*jtest);
            }
            if(jointName == "HipLeft")
            {
                jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                hipLeftJoint.append(*jtest);

            }
            if(jointName == "KneeLeft")
            {
              jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
               kneeLeftJoint.append(*jtest);
            }
            if(jointName == "AnkleLeft")
            {
                 jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                ankleLLeftJoint.append(*jtest);
            }
            if(jointName == "FootLeft")
            {
                jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
               footLeftJoint.append(*jtest);
            }

            if(jointName == "HipRight")
            {
                 jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                hipRightJoint.append(*jtest);

            }
            if(jointName == "KneeRight")
            {
                jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
               kneeRightJoint.append(*jtest);
            }
            if(jointName == "AnkleRight")
            {
                 jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                ankleLRightJoint.append(*jtest);
            }
            if(jointName == "FootRight")
            {
                jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
               footRightJoint.append(*jtest);
            }

            if(jointName == "SpineShoulder")
            {
                jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
               spineShoulderJoint.append(*jtest);
            }
            if(jointName == "HandTipLeft")
            {
                  jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                 handTipLeftJoint.append(*jtest);
            }
            if(jointName == "ThumbLeft")
            {
                  jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                 thumbLeftJoint.append(*jtest);
            }
            if(jointName == "HandTipRight")
            {
                  jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                 handTipRightJoing.append(*jtest);
            }
            if(jointName == "ThumbRight")
            {
                  jtest = new Joint(jointName,jointCoordinates, jointQuaternion , jointStatus);
                 thumbRightJoing.append(*jtest);
            }
            p++;
        }
        o++;
    }


    QVector<QVector<Joint>> Skeleton ;


    Skeleton.append(spinBaseJoint);
    Skeleton.append(spinMidJoint);
    Skeleton.append(neckJoint);
    Skeleton.append(headJoint);
    Skeleton.append(shoulderLeftJoint);
    Skeleton.append(elbowLeftJoint);
    Skeleton.append(wristLeftJoint);
    Skeleton.append(handLeftJoint);
    Skeleton.append(shoulderRightJoint);
    Skeleton.append(elbowRightJoint);
    Skeleton.append(wristRightJoint);
    Skeleton.append(handRightJoint);

    Skeleton.append(hipLeftJoint);
    Skeleton.append(kneeLeftJoint);
    Skeleton.append(ankleLLeftJoint);
    Skeleton.append(footLeftJoint);
    Skeleton.append(hipRightJoint);
    Skeleton.append(kneeRightJoint);
    Skeleton.append(ankleLRightJoint);
    Skeleton.append(footRightJoint);

    Skeleton.append(spineShoulderJoint);
    Skeleton.append(handTipLeftJoint);
    Skeleton.append(thumbLeftJoint);
    Skeleton.append(handTipRightJoing);
    Skeleton.append(thumbRightJoing);




    /*

    while (i.hasNext() && j.hasNext() && k.hasNext() ) {
        // Sphere
        //line
        jointCoordinates = i.next();
        jointName = j.next();
        QQuaternion jointQuaternion = k.next();
        qDebug() << k.next() << Qt::endl;
        //Joint(const QString _jointname ,const QVector3D _coordiantes,const QQuaternion _quaternion );
        Joint *jtest = new Joint(jointName,jointCoordinates, jointQuaternion);

        Qt3DCore::QEntity *cylindreEntity = new Qt3DCore::QEntity(rootEntity);
        jtest->paintJoint(cylindreEntity);

        //drawLine(current , end, QColor(255, 0, 0, 127), rootEntity);


        Qt3DCore::QEntity *sphereEntity = new Qt3DCore::QEntity(rootEntity);

        Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
        sphereMesh->setRadius(0.3);
        sphereMesh->setGenerateTangents(true);

        Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform;
        sphereTransform->setScale(0.5f);
        sphereTransform->setRotation(jointQuaternion);



        sphereTransform->setTranslation(jointCoordinates*10);

        auto *materialSphere = new Qt3DExtras::QPhongMaterial(rootEntity);
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

        Orbittransformcontroller *controller = new Orbittransformcontroller(sphereTransform,jtest);
        controller->setTarget(sphereTransform);
        controller->setRadius(1.0f);

        //Animation
        QPropertyAnimation *sphereRotateTransformAnimation = new QPropertyAnimation(sphereTransform);
        sphereRotateTransformAnimation->setTargetObject(controller);
        sphereRotateTransformAnimation->setPropertyName("angle");
        sphereRotateTransformAnimation->setStartValue(QVariant::fromValue(0));
        sphereRotateTransformAnimation->setEndValue(QVariant::fromValue(360));
        sphereRotateTransformAnimation->setDuration(10000);
        sphereRotateTransformAnimation->setLoopCount(-1);


        //sphereRotateTransformAnimation->start();


        group->addAnimation(sphereRotateTransformAnimation);
        sphereEntity->addComponent(sphereMesh);
        sphereEntity->addComponent(sphereTransform);
        sphereEntity->addComponent(materialSphere);


        {
        // text
        auto *text2dTransform = new Qt3DCore::QTransform;
        text2dTransform->setScale(0.01f);
        QVector3D *textvector = new QVector3D(10*jointCoordinates.x(),10*jointCoordinates.y(),10*jointCoordinates.z() +0.5);
           text2dTransform->setTranslation(*textvector);

       auto *text2d = new Qt3DExtras::QText2DEntity(rootEntity);
       text2d->setFont(QFont("monospace"));
           text2d->setHeight(20);
           text2d->setWidth(100);
           text2d->setText(jointName);
           text2d->setColor(Qt::red);
           text2d->addComponent(text2dTransform);
       //current = end;
        }


    }
    */
    //group->start();



    return Skeleton;
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    Qt3DCore::QEntity* rootEntity = new Qt3DCore::QEntity ;

     Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow;;
    QVector<QVector<Joint>> skeletonData= createScene();
    QVector<SkeletonBuilder*> test;


    for(int i = 0 ; i< 218; i++)
    {
       Qt3DCore::QEntity *tamp = new Qt3DCore::QEntity;
       SkeletonBuilder* sb = new SkeletonBuilder(skeletonData,i,tamp);
       test.append(sb);
    }

    MyTimer *myTimer = new MyTimer( new Qt3DCore::QEntity,test);

    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(myTimer->getRoot());
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);


    view->setRootEntity(myTimer->getRoot());

    //view.hide();
    view->show();

    return app.exec();
}
