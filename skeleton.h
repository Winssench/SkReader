#ifndef SKELETON_H
#define SKELETON_H


#include <QObject>
#include <QVector3D>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include<QQuaternion>
class Skeleton : public QObject
{
    Q_OBJECT
public:
    Skeleton();
    Skeleton(QString file);
    QVector<QVector3D> getVectors();
    QVector<QString> getNames();
    QVector<QString> getStatus();
    QVector<QQuaternion> getQuaternions();
    QVector<float> getTimes();
    int getColumns();

private:
    /**
         * @brief skeletonPoints    Vector to store the 3D skeleton points
         */
        QVector<QVector3D> skeletonPoints;

        QVector<QString> jointsNames;

        QVector<QString> jointsStatus;

        QVector<QQuaternion> jointQuaternion;

        QVector<float> times;

        /**
         * @brief nbColumns Number of columns in the skeleton file
         */
        int nbColumns;
};


#endif // SKELETON_H
