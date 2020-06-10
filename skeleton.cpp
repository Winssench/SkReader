#include "skeleton.h"
#include <QDebug>

Skeleton::Skeleton()
{

}

Skeleton::Skeleton(QString file) : QObject()
{
    qDebug() << file;
    QFile skeletonFile(file);
       bool firstLine = true ;     // to avoid the first line of headers
       QString line;       // to store a line
       QStringList dataList;       // to store the the data of the line after the split
       if (skeletonFile.open(QIODevice::ReadOnly))
       {

           QTextStream textStream(&skeletonFile);
           int i = 0;
           while (!textStream.atEnd())
           {

               if(i == 2)
               {
                   //return;
               }
               line = textStream.readLine();

               if (firstLine)
               {
                   dataList = line.split(",");     // split the data with the separator used
                   nbColumns = dataList.size();        // get the number of columns
                   firstLine = false;
               }
               else
               {
                   dataList = line.split(",");
                   times.append(dataList.at(1).toFloat());
                   for (int i = 9; i < nbColumns; i = i+9)
                   {
                       //if(dataList.at(i - 1) == "TRACKED")
                      // {
                           jointsStatus.append(dataList.at(i-1));
                           jointsNames.append(dataList.at(i - 2));
                           skeletonPoints.append(QVector3D(dataList.at(i).toFloat(), dataList.at(i+1).toFloat(), dataList.at(i+2).toFloat()));


                           jointQuaternion.append(QQuaternion(dataList.at(i+3).toFloat()
                                                              ,dataList.at(i+4).toFloat()
                                                              ,dataList.at(i+5).toFloat()
                                                              ,dataList.at(i+6).toFloat()));

                      // }

                   }


               }

               i++;


           }


           skeletonFile.close();
       }
}

QVector<QVector3D> Skeleton::getVectors()
{
    return skeletonPoints;
}

QVector<QString> Skeleton::getNames()
{
    return jointsNames;
}

QVector<QString> Skeleton::getStatus()
{
    return  jointsStatus;
}


QVector<QQuaternion> Skeleton::getQuaternions()
{
    return jointQuaternion;
}

QVector<float> Skeleton::getTimes()
{
    return times;
}


int Skeleton::getColumns()
{
    return nbColumns;
}
