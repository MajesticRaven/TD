#include "libs.h"

QVector<info> users;
QString user = "Guest";
int level = 1;
int record = 0;
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
QGraphicsView *view;
QGraphicsScene *scene;
QList<QPointF> points;
QList<QGraphicsItem*> Items;
int hpCastle;
QPointF Castle;
int coins;
int countOfUnits;
bool isOver;
QGraphicsTextItem *textItem;
QGraphicsPixmapItem *pixmapItem;
QGraphicsTextItem *texthp;
QGraphicsPixmapItem *pixmaphp;
