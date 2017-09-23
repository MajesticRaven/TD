#include "pit.h"

extern MainMenu* game;

pit::pit() {
    setPixmap(QPixmap("resources/images/pit.png"));
}

void pit::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(coins >= 25) {
            coins -= 25;
            textItem->setPlainText(QString::number(coins));
            tiTower* tow = new tiTower();
            tow->setPos(pos().x(), pos().y() - 45);
            scene()->addItem(tow);
            this->deleteLater();
        }
    }
    else if(event->button() == Qt::RightButton) {
        if(coins >= 40) {
            coins -= 40;
            textItem->setPlainText(QString::number(coins));
            grTower* tow = new grTower();
            tow->setPos(pos().x(), pos().y() - 45);
            scene()->addItem(tow);
            this->deleteLater();
        }
    }
}

pitWinter::pitWinter() {
    setPixmap(QPixmap("resources/images/pit.png"));
}

void pitWinter::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(coins >= 30) {
            coins -= 30;
            textItem->setPlainText(QString::number(coins));
            arcaneTower* tow = new arcaneTower();
            tow->setPos(pos().x(), pos().y() - 45);
            scene()->addItem(tow);
            this->deleteLater();
        }
    }
    else if(event->button() == Qt::RightButton) {
        if(coins >= 40) {
            coins -= 40;
            textItem->setPlainText(QString::number(coins));
            guardTower* tow = new guardTower();
            tow->setPos(pos().x(), pos().y() -45);
            scene()->addItem(tow);
            this->deleteLater();
        }
    }
}
