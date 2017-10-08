#ifndef TOWER_H
#define TOWER_H

#include "libs.h"

class towerBase {
public:
    virtual double distanceTo(QGraphicsItem* items);
    virtual void attackTarget();
    QGraphicsPolygonItem* field;
    bool hasTarget;
    QGraphicsItem* target;
    QPointF closestPt;
    int damage;
    QGraphicsPixmapItem *backHp;
    QGraphicsTextItem *showHp;
    int levelTower = 1;
};

class tower: public QObject, public QGraphicsPixmapItem, public towerBase {
    Q_OBJECT

public:
    tower();
    double distanceTo(QGraphicsItem* items);
    void attackTarget();

public slots:
    void tracking();
};

class tiTower: public tower {
    Q_OBJECT
public:
    tiTower();
    void attackTarget();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void tracking();
};

class grTower: public tower {
    Q_OBJECT
public:
    grTower();
    void attackTarget();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void tracking();
};

class guardTower: public tower {
    Q_OBJECT
public:
    guardTower();
    void attackTarget();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void tracking();
};

class arcaneTower: public tower {
    Q_OBJECT
public:
    arcaneTower();
    void attackTarget();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void tracking();
};

#endif // TOWER_H
