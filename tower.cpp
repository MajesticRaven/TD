#include "tower.h"

extern MainMenu* game;

tower::tower() {
    QVector<QPointF> pointPoly;
    pointPoly<<QPointF(1,0)
             <<QPointF(2,0)
             <<QPointF(3,1)
             <<QPointF(3,2)
             <<QPointF(2,3)
             <<QPointF(1,3)
             <<QPointF(0,2)
             <<QPointF(0,1);

      int zoomPoints = 150;

      for(int i = 0; i < pointPoly.size(); i++){
          pointPoly[i] *= zoomPoints;
      }

      QPolygonF polygon(pointPoly);

      field = new QGraphicsPolygonItem(polygon, this);

      QPointF center(1.5, 1.5);
      center *= zoomPoints;
      center = mapToScene(center);
      QPointF centerTower(x() + 110, y() + 110);
      QLineF ln(center, centerTower);
      field->setPos(ln.dx(), ln.dy());
}

double tower::distanceTo(QGraphicsItem *items) {
    QLineF ln(pos(), items->pos());
    return ln.length();
}

void tower::attackTarget() {

}

void tower::tracking() {
    Items = field->collidingItems();
    if(Items.size() < 2) {
        hasTarget = false;
        return;
    }
    else {
        double closest = 280;
        closestPt = QPointF(0,0);

        for(int i = 0; i < Items.size(); i++) {
            unit* vrag = dynamic_cast<unit*>(Items[i]);
            if(vrag) {
                double thisDist = distanceTo(vrag);

                if(thisDist < closest && dynamic_cast<unit*>(vrag)->isAttached == false) {
                    closest = thisDist;
                    closestPt = Items[i]->pos();
                    hasTarget = true;
                    target = Items[i];
                    break;
                }

            }
       }
    }
}

tiTower::tiTower() {
    setPixmap(QPixmap("resources/images/tiTower.png"));
    damage = level * 7 + 10;
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(tracking()));
    timer->start(1000);
}

void tiTower::tracking() {
    tower::tracking();

    if(closestPt != QPointF(0,0)) {
        dynamic_cast<unit*>(target)->isAttached = true;
        attackTarget();
    }
}

void tiTower::attackTarget() {
    bullet* bull = new bullet(target, damage);
    bull->setPixmap(QPixmap("resources/images/fireBullet.png"));
    bull->setPos(x() + 60, y() + 60);
    scene()->addItem(bull);
}

grTower::grTower() {
    setPixmap(QPixmap("resources/images/tomTower.png"));
    damage = level * 9 + 10;
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(tracking()));
    timer->start(1000);
}

void grTower::tracking() {
    tower::tracking();

    if(closestPt != QPointF(0,0)) {
        dynamic_cast<unit*>(target)->isAttached = true;
        attackTarget();
    }
}

void grTower::attackTarget() {
    bullet* bull = new bullet(target, damage);
    bull->setPixmap(QPixmap("resources/images/tombBullet.png"));
    bull->setPos(x() + 60, y() + 60);
    scene()->addItem(bull);
}

void tiTower::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(coins >= levelTower * 10 && levelTower < 11) {
            damage += 10;
            coins -= levelTower * 10;
            textItem->setPlainText(QString::number(coins));
            levelTower++;
        }
    }
}

void grTower::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(coins >= levelTower * 10 && levelTower < 11) {
            damage += 10;
            coins -= levelTower * 10;
            textItem->setPlainText(QString::number(coins));
            levelTower++;
        }
    }
}

guardTower::guardTower() {
    setPixmap(QPixmap("resources/images/guardTower.png"));
    damage = level * 7 + 10;
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(tracking()));
    timer->start(1000);
}

void guardTower::tracking() {
    tower::tracking();

    if(closestPt != QPointF(0,0)) {
        dynamic_cast<unit*>(target)->isAttached = true;
        attackTarget();
    }
}

void guardTower::attackTarget() {
    bullet* bull = new bullet(target, damage);
    bull->setPixmap(QPixmap("resources/images/fireBullet.png"));
    bull->setPos(x() + 60, y() + 60);
    scene()->addItem(bull);
}

void guardTower::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(coins >= levelTower * 10 && levelTower < 11) {
            damage += 10;
            coins -= levelTower * 10;
            textItem->setPlainText(QString::number(coins));
            levelTower++;
        }
    }
}

arcaneTower::arcaneTower() {
    setPixmap(QPixmap("resources/images/arcaneTower.png"));
    damage = level * 9 + 10;
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(tracking()));
    timer->start(1000);
}

void arcaneTower::tracking() {
    tower::tracking();

    if(closestPt != QPointF(0,0)) {
        dynamic_cast<unit*>(target)->isAttached = true;
        attackTarget();
    }
}

void arcaneTower::attackTarget() {
    bullet* bull = new bullet(target, damage);
    bull->setPixmap(QPixmap("resources/images/snowBullet.png"));
    bull->setPos(x() + 60, y() + 60);
    scene()->addItem(bull);
}

void arcaneTower::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(coins >= levelTower * 10 && levelTower < 11) {
            damage += 10;
            coins -= levelTower * 10;
            textItem->setPlainText(QString::number(coins));
            levelTower++;
        }
    }
}
