#ifndef PIT_H
#define PIT_H

#include "libs.h"

class pit: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    pit();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

class pitWinter: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    pitWinter();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PIT_H
