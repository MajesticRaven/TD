#ifndef LIBS_H
#define LIBS_H

#include <QLabel>
#include <QPixmap>
#include <QApplication>
#include <QDir>
#include <QString>
#include <QMainWindow>
#include <QSettings>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVector>
#include <QFile>
#include <QTimer>
#include <QStackedWidget>
#include <QTime>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QPoint>
#include <QLineF>
#include <QGraphicsObject>
#include <QGraphicsPolygonItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QXmlStreamWriter>
#include <QTextCodec>

#include "mainmenu.h"
#include "unit.h"
#include "tower.h"
#include "bullet.h"
#include "pit.h"

struct info {
    QString username;
    int level;
    int record;
};

extern int hpTower;
extern int coins;
extern QList<QPointF> points;
extern QVector<info> users;
extern QString user;
extern int level;
extern int record;
extern QSqlDatabase db;
extern QGraphicsView *view;
extern QGraphicsScene *scene;
extern QList<QPointF> points;
extern QList<QGraphicsItem*> Items;
extern int hpCastle;
extern QPointF Castle;
extern int coins;
extern int countOfUnits;
extern bool isOver;
extern QGraphicsTextItem *textItem;
extern QGraphicsPixmapItem *pixmapItem;
extern QGraphicsTextItem *texthp;
extern QGraphicsPixmapItem *pixmaphp;
extern bool isLose;

#endif // LIBS_H
