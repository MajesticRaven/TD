#ifndef BULLET_H
#define BULLET_H

#include "libs.h"

class bulletBase {
public:
    QPointF destination;
    int damage;
    QGraphicsItem* target;
};

class bullet: public QObject, public QGraphicsPixmapItem, public bulletBase {
    Q_OBJECT

public:
    bullet(QGraphicsItem* targ, int dmg);

    double getMaxRange();
    double getDistanceTravelled();
    void setMaxRange(double range);
    void setDistanceTravelled(double distance);

public slots:
    void move();
};

#endif // BULLET_H
