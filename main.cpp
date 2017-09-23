#include "libs.h"

MainMenu *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss("resources/style.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    a.topLevelWindows();


    game = new MainMenu;
    game->setWindowTitle("Tower Defence");
    game->show();


    return a.exec();
}
