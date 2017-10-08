#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    this->setFixedSize(1280, 720); //window size 720p
    ui->stackedWidget->setCurrentIndex(0); //make start index = 0
    QMessageBox::information(this, "Login", "Now you play as the guest! If you want to save the progress - LogIn"); //make messagebox
    ui->userLabel->setText("Guest"); // default username

    try {
        if(!QFile::exists(qApp->applicationDirPath() + "/accounts.db")) {
            throw 1;
        }
        db.setDatabaseName(qApp->applicationDirPath() + "/accounts.db");
    }
    catch(int e) {
        QMessageBox::critical(this, "No database", "You have no database.");
        exit(0);
    }
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::delay(int msec) {  //function for small pause
    QTime dieTime = QTime::currentTime().addMSecs(msec); //make time, what we need in int
    while(QTime::currentTime() < dieTime) // while it's not that time
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // wait
}

void MainMenu::on_exitButton_clicked() // exit
{
    close();
}

void MainMenu::on_loginButton_clicked() //login
{
    ReadDB(); // read database
    ui->stackedWidget->setCurrentIndex(1); //go next page of login
}

void MainMenu::on_chooseButton_clicked() //choose user
{
    if(ui->listAccount->currentItem()) { //if current item is available
        QListWidgetItem *itm = ui->listAccount->currentItem();
        user = itm->text(); //set username
        for(int i = 0; i < users.size(); i++) { //find real data of user
            if(user == users[i].username) {
                level = users[i].level;
                record = users[i].record;
            }
        }
        ui->userLabel->setText(user); //set username in label

        ui->stackedWidget->setCurrentIndex(0); // back to main page
    }
    else { //if empty choose
        QMessageBox::critical(this, "Error", "Choose the username!");
    }
}

void MainMenu::on_newButton_clicked() //create new user
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainMenu::on_oknewButton_clicked() //add user
{
    if(!ui->userEdit->text().isEmpty()) { //if username is not empty
        bool original = true; // make username original
        for(int i = 0; i < users.size(); i++) { // check for original
            if(users[i].username == ui->userEdit->text()) //if found simple name
                original = false;//not original
        }
        if(!original || ui->userEdit->text() == "Guest" || ui->userEdit->text() == "guest") { // and name not guest
            QMessageBox::critical(this, tr("Error"), tr("Username is incorrect!"));
        }
        else {
            db.open();

            QSqlQuery query(db); //create query
            query.exec("INSERT INTO accounts (username, level, record)"
                       "VALUES ('" + ui->userEdit->text() + "', 1, 0)");//make query
            db.close();// close database
            ui->stackedWidget->setCurrentIndex(1); //back to prev page
            }
    }
    else {
        QMessageBox::critical(this, "Error", "Enter the username!");
    }
    ReadDB(); //read database for showing
}

void MainMenu::ReadDB() { //read database
    info buf;
    users.clear(); //clear vector
    ui->listAccount->clear();

    db.open();//open it

        QSqlQuery query(db); //create query
        query.exec("Select username, level, record from accounts"); //read all

        while(query.next()) { //write info to vector
            buf.username = query.value(0).toString();
            buf.level = query.value(1).toInt();
            buf.record = query.value(2).toInt();
            users.push_back(buf);
            ui->listAccount->addItem(buf.username);
        }

    db.close();
}

void MainMenu::WriteDB() {
    QString del = ("UPDATE accounts SET level=" + QString::number(level) + ", record=" + QString::number(record) + " WHERE username='" + user + "'");

    db.open();

    QSqlQuery query(db); //create query
    query.exec(del);
    db.close();
}

void MainMenu::on_cancelButton_clicked() //go to prev page
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainMenu::on_recordButton_clicked() //page of records
{
    ReadDB(); // read database
    ui->stackedWidget->setCurrentIndex(3);

    QString str; //string with all records
    str.clear();
    for(int i = 0; i < users.size(); i++) { //write all records
        str += users[i].username + ": " + QString::number(users[i].record) +'\n';
        ui->recordBrowser->setText(str); //set text to browser
    }
}

void MainMenu::on_okrecordButton_clicked()//go to prev page
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainMenu::Sort() { // buble sort of records by number
    for(int i = 0; i < users.size(); i++) {
        for(int j = i; j < users.size() - 1; j++) {
            if(users[j].record < users[j + 1].record)
                std::swap(users[j], users[j+1]);
        }
    }
}

void MainMenu::on_storyButton_clicked() //go to menu with levels
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->secondlevel->setEnabled(true);
    ui->thirdlevel->setEnabled(true);
    ui->fourthlevel->setEnabled(true);
    ui->fifthlevel->setEnabled(true);
    ui->sixlevel->setEnabled(true);
    ui->sevenlevel->setEnabled(true);
    ui->eightlevel->setEnabled(true);
    ui->ninelevel->setEnabled(true);
    ui->tenlevel->setEnabled(true);

    //block all levels, which are unreached
    if(level < 2)
        ui->secondlevel->setEnabled(false);

    if (level < 3)
        ui->thirdlevel->setEnabled(false);

    if(level < 4)
        ui->fourthlevel->setEnabled(false);

    if(level < 5)
        ui->fifthlevel->setEnabled(false);

    if(level < 6)
        ui->sixlevel->setEnabled(false);

    if(level < 7)
        ui->sevenlevel->setEnabled(false);

    if(level < 8)
        ui->eightlevel->setEnabled(false);

    if(level < 9)
        ui->ninelevel->setEnabled(false);

    if(level < 10)
        ui->tenlevel->setEnabled(false);
}

void MainMenu::on_backButton_clicked() //go to prev page
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainMenu::BackToMenu() {
    if(isLose == false) {
        scene->deleteLater();
        view->deleteLater();
        ui->stackedWidget->setCurrentIndex(0);
        QMessageBox::critical(this, "Lost", "You lose. Try again later");
        isLose = true;
    }
}

void MainMenu::checkForWin(int lvl) {
    if(countOfUnits == 0 && isOver == true) {
        level = lvl + 1;

        if(coins > record) {
            record = coins;
        }

        scene->deleteLater();
        view->deleteLater();
        ui->stackedWidget->setCurrentIndex(0);
        WriteDB();
        QMessageBox::about(this, "Won", "You won! Next level is openned");
        isLose = true;
    }
}

void MainMenu::on_helpButton_clicked() {
    ui->stackedWidget->setCurrentIndex(6);
    QString aboutTextFromFile = readFile("resources/about.txt");
    ui->aboutText->setText(aboutTextFromFile);
    ui->aboutText->setWordWrap(true);
    ui->aboutText->setFont(QFont("Times", 20));
}

void MainMenu::on_aboutBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

QString MainMenu::readFile(QString filename){
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       return NULL;

    QByteArray total;
    QByteArray line;
    while (!file.atEnd()) {
        line = file.read(1024);
        total.append(line);
    }
    return QString(total);
}

void MainMenu::on_xmlWriteButton_clicked() {
    QFile file("backup.xml");
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    for(int i = 0; i < users.size(); i++) {
        xmlWriter.writeStartElement("User " + QString::number(i + 1));

        xmlWriter.writeStartElement("Username");
        xmlWriter.writeCharacters(users[i].username);
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("Level");
        xmlWriter.writeCharacters(QString::number(users[i].level));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("Record");
        xmlWriter.writeCharacters(QString::number(users[i].record));
        xmlWriter.writeEndElement();

        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndDocument();
    file.close();
    QMessageBox::about(this, "Succes", "File is done!");
}

void MainMenu::on_firstlevel_clicked() //open first level
{
    ui->stackedWidget->setCurrentIndex(5);
    firstlevel();
}

void MainMenu::on_secondlevel_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
    secondlevel();
}

void MainMenu::on_thirdlevel_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
    thirdlevel();
}

void MainMenu::on_fourthlevel_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
    fourthlevel();
}

void MainMenu::on_fifthlevel_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
    fifthlevel();
}

void MainMenu::on_sixlevel_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
    sixlevel();
}

void MainMenu::on_sevenlevel_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
    sevenlevel();
}

void MainMenu::on_eightlevel_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
    eightlevel();
}

void MainMenu::on_ninelevel_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
    ninelevel();
}

void MainMenu::on_tenlevel_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
    tenlevel();
}

void MainMenu::firstlevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    coins = 50;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_1.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1020, 40);

    points.clear();
    points.push_back(QPointF(230, 150));
    points.push_back(QPointF(230, 400));
    points.push_back(QPointF(600, 400));
    points.push_back(QPointF(600, 40));
    points.push_back(QPointF(1050, 40));

    pit* pit1 = new pit();
    pit1->setPos(25, 250);
    scene->addItem(pit1);

    pit* pit2 = new pit();
    pit2->setPos(750, 200);
    scene->addItem(pit2);

    pit* pit3 = new pit();
    pit3->setPos(370, 200);
    scene->addItem(pit3);

    for(int i = 0; i < 0; i++ ) {
        delay(2000);
        Arthas* unit1 = new Arthas(1);
        unit1->setPos(0, 150);
        scene->addItem(unit1);
    }

    delay(10000);

    for(int i = 0; i < 5; i++) {
        delay(2000);
        Arthas* unit1 = new Arthas(1);
        unit1->setPos(0, 150);
        scene->addItem(unit1);

        delay(2000);

        GryphonRyder* unit2 = new GryphonRyder(1);
        unit2->setPos(0, 150);
        scene->addItem(unit2);
    }
    isOver = true;
}

void MainMenu::secondlevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);


    coins = 50;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_2.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1050, 420);

    points.clear();
    points.push_back(QPointF(320, 420));
    points.push_back(QPointF(320, 50));
    points.push_back(QPointF(120, 50));
    points.push_back(QPointF(120, 220));
    points.push_back(QPointF(600, 220));
    points.push_back(QPointF(600, 420));
    points.push_back(QPointF(1300, 420));

    pit* pit1 = new pit();
    pit1->setPos(140, 280);
    scene->addItem(pit1);

    pit* pit2 = new pit();
    pit2->setPos(700, 280);
    scene->addItem(pit2);

    pit* pit3 = new pit();
    pit3->setPos(420, 90);
    scene->addItem(pit3);

    for(int i = 0; i < 5; i++ ) {
        delay(2000);
        GryphonRyder* unit1 = new GryphonRyder(2);
        unit1->setPos(0, 420);
        scene->addItem(unit1);
    }

    delay(10001);

    for(int i = 0; i < 4; i++) {
        delay(2222);
        Troll* unit1 = new Troll(2);
        unit1->setPos(0, 420);
        scene->addItem(unit1);
    }

    delay(8999);

    for(int i = 0; i < 6; i++) {
        delay(1800);
        Troll* unit1 = new Troll(2);
        unit1->setPos(0, 420);
        scene->addItem(unit1);

        delay(2000);
        GryphonRyder* unit2 = new GryphonRyder(2);
        unit2->setPos(0, 420);
        scene->addItem(unit2);

        delay(1500);
        Arthas* unit3 = new Arthas(1);
        unit3->setPos(0, 420);
        scene->addItem(unit3);
    }

    isOver = true;
}

void MainMenu::thirdlevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);


    coins = 70;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_3.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1050, 200);

    points.clear();
    points.push_back(QPointF(400, 50));
    points.push_back(QPointF(400, 450));
    points.push_back(QPointF(800, 450));
    points.push_back(QPointF(800, 10));
    points.push_back(QPointF(580, 10));
    points.push_back(QPointF(580, 200));
    points.push_back(QPointF(1100, 200));

    pit* pit1 = new pit();
    pit1->setPos(290, 150);
    scene->addItem(pit1);

    pit* pit2 = new pit();
    pit2->setPos(900, 280);
    scene->addItem(pit2);

    pit* pit3 = new pit();
    pit3->setPos(650, 80);
    scene->addItem(pit3);

    for(int i = 0; i < 5; i++ ) {
        delay(2000);
        Troll* unit1 = new Troll(3);
        unit1->setPos(0, 50);
        scene->addItem(unit1);
    }

    delay(11111);

    for(int i = 0; i < 6; i++) {
        delay(2000);
        Troll* unit1 = new Troll(3);
        unit1->setPos(0, 50);
        scene->addItem(unit1);

        delay(2000);
        Wolf *unit2 = new Wolf(3);
        unit2->setPos(0, 50);
        scene->addItem(unit2);
    }

    delay(8888);

    for(int i = 0; i < 5; i++) {
        Hydralisk* unit1 = new Hydralisk(3);
        unit1->setPos(0, 50);
        scene->addItem(unit1);

        delay(2000);
        Wolf *unit2 = new Wolf(3);
        unit2->setPos(0, 50);
        scene->addItem(unit2);
    }

    isOver = true;
}

void MainMenu::fourthlevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);


    coins = 70;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_4.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1000, 50);

    points.clear();
    points.push_back(QPointF(200, 150));
    points.push_back(QPointF(200, 400));
    points.push_back(QPointF(500, 400));
    points.push_back(QPointF(500, 150));
    points.push_back(QPointF(670, 150));
    points.push_back(QPointF(670, 480));
    points.push_back(QPointF(945, 480));
    points.push_back(QPointF(945, 50));
    points.push_back(QPointF(1100, 50));

    pitWinter* pit1 = new pitWinter();
    pit1->setPos(330, 290);
    scene->addItem(pit1);

    pitWinter* pit2 = new pitWinter();
    pit2->setPos(810, 300);
    scene->addItem(pit2);

    pitWinter* pit3 = new pitWinter();
    pit3->setPos(30, 250);
    scene->addItem(pit3);

    for(int i = 0; i < 10; i++ ) {
        delay(2000);
        Hydralisk* unit1 = new Hydralisk(4);
        unit1->setPos(0, 150);
        scene->addItem(unit1);

        delay(3000);
        Wolf *unit2 = new Wolf(4);
        unit2->setPos(0, 150);
        scene->addItem(unit2);
    }

    delay(5777);

    for(int i = 0; i < 5; i++) {
        delay(2000);
        Hydralisk* unit1 = new Hydralisk(4);
        unit1->setPos(0, 150);
        scene->addItem(unit1);

        delay(3000);
        chaosBeast* unit2 = new chaosBeast(4);
        unit2->setPos(0,150);
        scene->addItem(unit2);
    }

    delay(9111);

    for(int i = 0; i < 5; i++) {
        delay(2000);
        Warlock* unit1 = new Warlock(4);
        unit1->setPos(0,150);
        scene->addItem(unit1);
    }

    isOver = true;
}

void MainMenu::fifthlevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    coins = 90;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_5.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1080, 480);

    points.clear();
    points.push_back(QPointF(430, 240));
    points.push_back(QPointF(430, 500));
    points.push_back(QPointF(190, 500));
    points.push_back(QPointF(190, 50));
    points.push_back(QPointF(740, 50));
    points.push_back(QPointF(740, 480));
    points.push_back(QPointF(1150, 480));

    pitWinter* pit1 = new pitWinter();
    pit1->setPos(270, 330);
    scene->addItem(pit1);

    pitWinter* pit2 = new pitWinter();
    pit2->setPos(850, 300);
    scene->addItem(pit2);

    pitWinter* pit3 = new pitWinter();
    pit3->setPos(560, 150);
    scene->addItem(pit3);

    for(int i = 0; i < 11; i++ ) {
        delay(2000);
        Hydralisk* unit1 = new Hydralisk(5);
        unit1->setPos(0, 240);
        scene->addItem(unit1);
    }

    for(int i = 0; i < 4; i++) {
        delay(3000);
        Doom* unit1 = new Doom(5);
        unit1->setPos(0, 240);
        scene->addItem(unit1);
    }

    delay(8888);

    for(int i = 0; i < 10; i++) {
        delay(3000);
        Doom* unit1 = new Doom(5);
        unit1->setPos(0, 240);
        scene->addItem(unit1);

        delay(1700);
        CrystalMaiden* unit2 = new CrystalMaiden(5);
        unit2->setPos(0, 240);
        scene->addItem(unit2);
    }

    isOver = true;
}

void MainMenu::sixlevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    coins = 90;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_6.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1110, 420);

    points.clear();
    points.push_back(QPointF(670, 420));
    points.push_back(QPointF(670, 250));
    points.push_back(QPointF(900, 250));
    points.push_back(QPointF(900, 120));
    points.push_back(QPointF(400, 120));
    points.push_back(QPointF(400, 420));
    points.push_back(QPointF(1200, 420));

    pitWinter* pit1 = new pitWinter();
    pit1->setPos(200, 300);
    scene->addItem(pit1);

    pitWinter* pit2 = new pitWinter();
    pit2->setPos(770, 300);
    scene->addItem(pit2);

    pitWinter* pit3 = new pitWinter();
    pit3->setPos(540, 230);
    scene->addItem(pit3);

    for(int i = 0; i < 11; i++ ) {
        delay(2000);
        Doom* unit1 = new Doom(6);
        unit1->setPos(0, 420);
        scene->addItem(unit1);
    }

    delay(11111);

    for(int i = 0; i < 9; i++) {
        delay(2500);
        DragonKnight* unit1 = new DragonKnight(6);
        unit1->setPos(0, 420);
        scene->addItem(unit1);
    }

    delay(9999);

    for(int i = 0; i < 9; i++) {
        delay(2500);
        DragonKnight* unit1 = new DragonKnight(6);
        unit1->setPos(0, 420);
        scene->addItem(unit1);

        delay(1600);
        Enchantress* unit2 = new Enchantress(6);
        unit2->setPos(0, 420);
        scene->addItem(unit2);
    }

    isOver = true;
}

void MainMenu::sevenlevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    coins = 90;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_7.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1100, 450);

    points.clear();
    points.push_back(QPointF(420, 450));
    points.push_back(QPointF(420, 150));
    points.push_back(QPointF(650, 150));
    points.push_back(QPointF(650, 300));
    points.push_back(QPointF(270, 300));
    points.push_back(QPointF(270, 70));
    points.push_back(QPointF(820, 70));
    points.push_back(QPointF(820, 450));
    points.push_back(QPointF(1150, 450));

    pitWinter* pit1 = new pitWinter();
    pit1->setPos(100, 330);
    scene->addItem(pit1);

    pitWinter* pit2 = new pitWinter();
    pit2->setPos(900, 330);
    scene->addItem(pit2);

    pitWinter* pit3 = new pitWinter();
    pit3->setPos(530, 180);
    scene->addItem(pit3);

    for(int i = 0; i < 11; i++ ) {
        delay(2000);
        DragonKnight* unit1 = new DragonKnight(7);
        unit1->setPos(0, 450);
        scene->addItem(unit1);
    }

    delay(11111);

    for(int i = 0; i < 7; i++) {
        delay(1700);
        Rubick* unit1 = new Rubick(7);
        unit1->setPos(0, 450);
        scene->addItem(unit1);
    }

    delay(11111);

    for(int i = 0; i < 12; i++) {
        delay(1700);
        Rubick* unit1 = new Rubick(7);
        unit1->setPos(0, 450);
        scene->addItem(unit1);

        delay(2500);
        Warlord* unit2 = new Warlord(7);
        unit2->setPos(0, 450);
        scene->addItem(unit2);
    }

    isOver = true;
}

void MainMenu::eightlevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    coins = 90;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_8.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1050, 460);

    points.clear();
    points.push_back(QPointF(170, 400));
    points.push_back(QPointF(170, 100));
    points.push_back(QPointF(400, 100));
    points.push_back(QPointF(400, 480));
    points.push_back(QPointF(620, 480));
    points.push_back(QPointF(620, 100));
    points.push_back(QPointF(840, 100));
    points.push_back(QPointF(840, 480));
    points.push_back(QPointF(1200, 480));

    pitWinter* pit1 = new pitWinter();
    pit1->setPos(50, 280);
    scene->addItem(pit1);

    pitWinter* pit2 = new pitWinter();
    pit2->setPos(700, 200);
    scene->addItem(pit2);

    pitWinter* pit3 = new pitWinter();
    pit3->setPos(470, 320);
    scene->addItem(pit3);

    for(int i = 0; i < 8; i++ ) {
        delay(4000);
        Warlord* unit1 = new Warlord(8);
        unit1->setPos(0, 400);
        scene->addItem(unit1);
    }

    delay(13000);

    for(int i = 0; i < 7; i++) {
        delay(3500);
        Luna* unit1 = new Luna(8);
        unit1->setPos(0, 400);
        scene->addItem(unit1);

        delay(2500);
        Furion* unit2 = new Furion(8);
        unit2->setPos(0, 400);
        scene->addItem(unit2);
    }

    delay(14999);

    for(int i = 0; i < 8; i++) {
        delay(3000);
        KotoBeast* unit1 = new KotoBeast(8);
        unit1->setPos(0, 400);
        scene->addItem(unit1);

        delay(2000);
        Luna* unit2 = new Luna(8);
        unit2->setPos(0, 400);
        scene->addItem(unit2);
    }

    isOver = true;
}

void MainMenu::ninelevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    coins =  80;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_9.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1020, 430);

    points.clear();
    points.push_back(QPointF(860, 260));
    points.push_back(QPointF(860, 110));
    points.push_back(QPointF(100, 110));
    points.push_back(QPointF(100, 430));
    points.push_back(QPointF(1200, 430));

    pitWinter* pit1 = new pitWinter();
    pit1->setPos(150, 300);
    scene->addItem(pit1);

    pitWinter* pit2 = new pitWinter();
    pit2->setPos(650, 300);
    scene->addItem(pit2);

    pitWinter* pit3 = new pitWinter();
    pit3->setPos(440, 130);
    scene->addItem(pit3);

    for(int i = 0; i < 7; i++ ) {
        delay(2500);
        KotoBeast* unit1 = new KotoBeast(9);
        unit1->setPos(0, 260);
        scene->addItem(unit1);

        delay(2500);
        WywernRyder* unit2 = new WywernRyder(9);
        unit2->setPos(0, 260);
        scene->addItem(unit2);
    }

    delay(13000);

    for(int i = 0; i < 9; i++) {
        delay(1500);
        Sniper* unit1 = new Sniper(9);
        unit1->setPos(0, 260);
        scene->addItem(unit1);

        delay(1500);
        WywernRyder* unit2 = new WywernRyder(9);
        unit2->setPos(0, 260);
        scene->addItem(unit2);
    }

    delay(15000);

    for(int i = 0; i < 8; i++) {
        delay(3000);
        Sniper* unit1 = new Sniper(9);
        unit1->setPos(0, 260);
        scene->addItem(unit1);

        delay(1500);
        Thrall* unit2 = new Thrall(9);
        unit2->setPos(0, 260);
        scene->addItem(unit2);
    }

    isOver = true;
}

void MainMenu::tenlevel() {
    isLose = false;
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    coins =  80;
    countOfUnits = 0;
    isOver = false;
    hpCastle = 10;

    //set the size of this scene
    scene->setSceneRect(0.0, 0.0, 1200.0, 660.0);
    ui->levellay->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet("border-image: url(resources/images/backgrounds/background_10.png)");

    pixmapItem = scene->addPixmap(QPixmap("resources/images/coinsbar.png"));
    pixmapItem->setPos(0, 0);

    textItem = scene->addText(QString::number(coins));
    textItem->setPos(50, 5);
    textItem->setFont(QFont("Times", 20));
    textItem->setDefaultTextColor(Qt::white);

    pixmaphp = scene->addPixmap(QPixmap("resources/images/HP bar/HP10.png"));
    pixmaphp->setPos(350, 0);

    texthp = scene->addText(QString::number(hpCastle) + "/10");
    texthp->setPos(550, 5);
    texthp->setFont(QFont("Times", 20));
    texthp->setDefaultTextColor(Qt::white);

    Castle = QPointF(1100, 490);

    points.clear();
    points.push_back(QPointF(280, 300));
    points.push_back(QPointF(280, 550));
    points.push_back(QPointF(470, 550));
    points.push_back(QPointF(470, 150));
    points.push_back(QPointF(720, 150));
    points.push_back(QPointF(720, 300));
    points.push_back(QPointF(470, 300));
    points.push_back(QPointF(470, 150));
    points.push_back(QPointF(300, 150));
    points.push_back(QPointF(300, 50));
    points.push_back(QPointF(920, 50));
    points.push_back(QPointF(920, 490));
    points.push_back(QPointF(1200, 490));

    pitWinter* pit1 = new pitWinter();
    pit1->setPos(150, 400);
    scene->addItem(pit1);

    pitWinter* pit2 = new pitWinter();
    pit2->setPos(800, 400);
    scene->addItem(pit2);

    pit* pit3 = new pit();
    pit3->setPos(600, 200);
    scene->addItem(pit3);

    pit* pit4 = new pit();
    pit4->setPos(350, 400);
    scene->addItem(pit4);

    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Arthas* unit1 = new Arthas(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 8;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        GryphonRyder* unit1 = new GryphonRyder(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 6;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Troll* unit1 = new Troll(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 5;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Wolf* unit1 = new Wolf(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 4;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Hydralisk* unit1 = new Hydralisk(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 4;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        chaosBeast* unit1 = new chaosBeast(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Warlock* unit1 = new Warlock(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        CrystalMaiden* unit1 = new CrystalMaiden(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Doom* unit1 = new Doom(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        DragonKnight* unit1 = new DragonKnight(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Enchantress* unit1 = new Enchantress(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Rubick* unit1 = new Rubick(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Warlord* unit1 = new Warlord(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Furion* unit1 = new Furion(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Luna* unit1 = new Luna(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        KotoBeast* unit1 = new KotoBeast(10);
        unit1->setPos(0, 300);
        dynamic_cast<unit*>(unit1)->health *= 2;
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        WywernRyder* unit1 = new WywernRyder(10);
        unit1->setPos(0, 300);
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Sniper* unit1 = new Sniper(10);
        unit1->setPos(0, 300);
        scene->addItem(unit1);
    }

    delay(11111);
    for(int i = 0; i < 7; i++ ) {
        delay(2000);
        Thrall* unit1 = new Thrall(10);
        unit1->setPos(0, 300);
        scene->addItem(unit1);
    }

    delay(12777);
    for(int i = 0; i < 4; i++ ) {
        delay(5000);
        Infernal* unit1 = new Infernal(10);
        unit1->setPos(0, 300);
        scene->addItem(unit1);
    }

    delay(15000);
    TichondriusBoss* unit1 = new TichondriusBoss(10);
    unit1->setPos(0, 300);
    scene->addItem(unit1);

    isOver = true;
}

