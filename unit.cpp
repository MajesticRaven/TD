#include "unit.h"

extern MainMenu* game;

unit::unit() {
    countOfUnits++;
    stepSize = 1;

    point_index = 0;
    destination = points[0];
}

void unit::delay(int msec) {  //function for small pause
    QTime dieTime = QTime::currentTime().addMSecs(msec); //make time, what we need in int
    while(QTime::currentTime() < dieTime) // while it's not that time
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // wait
}

void unit::attached(int damage) {
    health -= damage;
    isAttached = false;
    if(health <= 0) {
        this->deleteLater();
        coins += 5;
        textItem->setPlainText(QString::number(coins));
        countOfUnits--;
        game->checkForWin(lvl);
    }
}

void unit::move_forward() {
    QLineF ln(pos(), destination);
    if(ln.length() < 5) {
        point_index++;

        if(point_index>=points.size()) {
            return;
        }

        destination = points[point_index];
    }

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

    if(pos() == QPointF(Castle.x() - 5, Castle.y()) && isAttached == true) {
        while(isAttached == true) {
            delay(10);
        }
    }

    if(pos() == Castle) {

        countOfUnits--;
        game->checkForWin(lvl);
        this->deleteLater();
        hpCastle--;
        texthp->setPlainText(QString::number(hpCastle) + "/10");
        switch(hpCastle) {
        case 9: {
                pixmaphp->setPixmap(QPixmap("resources/images/HP bar/HP9.png"));
                break;
            }
        case 8: {
            pixmaphp->setPixmap(QPixmap("resources/images/HP bar/HP8.png"));
            break;
        }
        case 7: {
            pixmaphp->setPixmap(QPixmap("resources/images/HP bar/HP7.png"));
            break;
        }
        case 6: {
            pixmaphp->setPixmap(QPixmap("resources/images/HP bar/HP6.png"));
            break;
        }
        case 5: {
            pixmaphp->setPixmap(QPixmap("resources/images/HP bar/HP5.png"));
            break;
        }
        case 4: {
            pixmaphp->setPixmap(QPixmap("resources/images/HP bar/HP4.png"));
            break;
        }
        case 3: {
            pixmaphp->setPixmap(QPixmap("resources/images/HP bar/HP3.png"));
            break;
        }
        case 2: {
            pixmaphp->setPixmap(QPixmap("resources/images/HP bar/HP2.png"));
            break;
        }
        case 1: {
            pixmaphp->setPixmap(QPixmap("resources/images/HP bar/HP1.png"));
            break;
        }
        }

        if(hpCastle == 0) {
            game->BackToMenu();
        }
    }    
}

Arthas::Arthas(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/Arthas.png"));

    health = 50;
    stepSize = 1;

    point_index = 0;
    destination = points[0];

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(20);
}

void Arthas::move_forward() {
    unit::move_forward();
}

GryphonRyder::GryphonRyder(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/GryphonRyder.png"));

    health = 70;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(15);
}

void GryphonRyder::move_forward() {
    unit::move_forward();
}

Troll::Troll(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/Troll.png"));

    health = 120;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(24);
}

void Troll::move_forward() {
    unit::move_forward();
}

Wolf::Wolf(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/Wolf.png"));

    health = 100;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(13);
}

void Wolf::move_forward() {
    unit::move_forward();
}

Hydralisk::Hydralisk(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/Hydralisk.png"));

    health = 170;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(28);
}

void Hydralisk::move_forward() {
    unit::move_forward();
}

chaosBeast::chaosBeast(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/chaosBeast.png"));

    health = 300;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(32);
}

void chaosBeast::move_forward() {
    unit::move_forward();
}

Warlock::Warlock(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/warlock.png"));

    health = 250;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(19);
}

void Warlock::move_forward() {
    unit::move_forward();
}

CrystalMaiden::CrystalMaiden(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/crystalMaiden.png"));

    health = 200;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(12);
}

void CrystalMaiden::move_forward() {
    unit::move_forward();
}

Doom::Doom(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/doom.png"));

    health = 400;
    stepSize = 1;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(42);
}

void Doom::move_forward() {
    unit::move_forward();
}

DragonKnight::DragonKnight(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/dragonKnight.png"));

    health = 600;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(45);
}

void DragonKnight::move_forward() {
    unit::move_forward();
}

Enchantress::Enchantress(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/enchantress.png"));

    health = 280;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(20);
}

void Enchantress::move_forward() {
    unit::move_forward();
}

Rubick::Rubick(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/rubick.png"));

    health = 320;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(20);
}

void Rubick::move_forward() {
    unit::move_forward();
}

Warlord::Warlord(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/warlord.png"));

    health = 700;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(53);
}

void Warlord::move_forward() {
    unit::move_forward();
}

Furion::Furion(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/furion.png"));

    health = 330;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(30);
}

void Furion::move_forward() {
    unit::move_forward();
}

Luna::Luna(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/Luna.png"));

    health = 350;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(27);
}

void Luna::move_forward() {
    unit::move_forward();
}

KotoBeast::KotoBeast(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/KotoBeast.png"));

    health = 750;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(43);
}

void KotoBeast::move_forward() {
    unit::move_forward();
}

WywernRyder::WywernRyder(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/wywernRyder.png"));

    health = 600;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(17);
}

void WywernRyder::move_forward() {
    unit::move_forward();
}

Sniper::Sniper(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/sniper.png"));

    health = 650;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(14);
}

void Sniper::move_forward() {
    unit::move_forward();
}

Thrall::Thrall(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/Thrall.png"));

    health = 1500;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(31);
}

void Thrall::move_forward() {
    unit::move_forward();
}

Infernal::Infernal(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/infernal.png"));

    health = 3000;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(50);
}

void Infernal::move_forward() {
    unit::move_forward();
}

TichondriusBoss::TichondriusBoss(int lvlGlobal) {
    lvl = lvlGlobal;
    setPixmap(QPixmap("resources/images/units/TichondriusBoss.png"));

    health = 9000;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(70);
}

void TichondriusBoss::move_forward() {
    unit::move_forward();
}
