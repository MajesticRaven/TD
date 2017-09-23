#include "bullet.h"

bullet::bullet(QGraphicsItem* targ, int dmg) {
    target = targ;
    damage = dmg;
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(9);
}

void bullet::move() {
    double stepSize = 1;

    QPointF posit = dynamic_cast<unit*>(target)->pos();
    destination = QPointF(posit.x() + 30, posit.y() + 30);
    double dx = 0, dy = 0;

    if(x() < destination.x()) { //if we go right
        dx = stepSize;
    }

    if(y() < destination.y()) { //if we go down
        dy = stepSize;
    }

    if(x() > destination.x()) { //if we go left
        dx = -stepSize;
    }

    if(y() > destination.y()) { //if we go up
        dy = -stepSize;
    }

    setPos(x() + dx, y() + dy);

    if(destination == pos()) {
        this->deleteLater();
        dynamic_cast<unit*>(target)->attached(damage);
    }
}
