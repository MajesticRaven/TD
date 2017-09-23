#ifndef UNIT_H
#define UNIT_H

#include "libs.h"

class unitBase {
public:
    QPointF destination;
    int point_index; //on what index of point we are stopped
    int stepSize;
    double health;
    int lvl;
    bool isAttached = false;
    virtual void attached(int damage);
};

class unit: public QObject, public QGraphicsPixmapItem, public unitBase {
    Q_OBJECT

public:
    unit();
    void attached(int damage);
    void delay(int msec);

public slots:
    void move_forward();
};

class Arthas: public unit {
   Q_OBJECT

public:
    Arthas(int lvlGlobal);

public slots:
    void move_forward();
};

class GryphonRyder: public unit {
   Q_OBJECT

public:
    GryphonRyder(int lvlGlobal);

public slots:
    void move_forward();
};

class Troll: public unit {
   Q_OBJECT

public:
    Troll(int lvlGlobal);

public slots:
    void move_forward();
};

class Wolf: public unit {
   Q_OBJECT

public:
    Wolf(int lvlGlobal);

public slots:
    void move_forward();
};

class Hydralisk: public unit {
   Q_OBJECT

public:
    Hydralisk(int lvlGlobal);

public slots:
    void move_forward();
};

class chaosBeast: public unit {
   Q_OBJECT

public:
    chaosBeast(int lvlGlobal);

public slots:
    void move_forward();
};

class Warlock: public unit {
   Q_OBJECT

public:
    Warlock(int lvlGlobal);

public slots:
    void move_forward();
};

class CrystalMaiden: public unit {
   Q_OBJECT

public:
    CrystalMaiden(int lvlGlobal);

public slots:
    void move_forward();
};

class Doom: public unit {
   Q_OBJECT

public:
    Doom(int lvlGlobal);

public slots:
    void move_forward();
};

class DragonKnight: public unit {
   Q_OBJECT

public:
    DragonKnight(int lvlGlobal);

public slots:
    void move_forward();
};

class Enchantress: public unit {
   Q_OBJECT

public:
    Enchantress(int lvlGlobal);

public slots:
    void move_forward();
};

class Rubick: public unit {
   Q_OBJECT

public:
    Rubick(int lvlGlobal);

public slots:
    void move_forward();
};

class Warlord: public unit {
   Q_OBJECT

public:
    Warlord(int lvlGlobal);

public slots:
    void move_forward();
};

class Furion: public unit {
   Q_OBJECT

public:
    Furion(int lvlGlobal);

public slots:
    void move_forward();
};

class Luna: public unit {
   Q_OBJECT

public:
    Luna(int lvlGlobal);

public slots:
    void move_forward();
};

class KotoBeast: public unit {
   Q_OBJECT

public:
    KotoBeast(int lvlGlobal);

public slots:
    void move_forward();
};

class WywernRyder: public unit {
   Q_OBJECT

public:
    WywernRyder(int lvlGlobal);

public slots:
    void move_forward();
};

class Sniper: public unit {
   Q_OBJECT

public:
    Sniper(int lvlGlobal);

public slots:
    void move_forward();
};

class Thrall: public unit {
   Q_OBJECT

public:
    Thrall(int lvlGlobal);

public slots:
    void move_forward();
};

class Infernal: public unit {
   Q_OBJECT

public:
    Infernal(int lvlGlobal);

public slots:
    void move_forward();
};

class TichondriusBoss: public unit {
   Q_OBJECT

public:
    TichondriusBoss(int lvlGlobal);

public slots:
    void move_forward();
};

#endif // UNIT_H
