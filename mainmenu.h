#ifndef MAINMENU_H
#define MAINMENU_H

#include "libs.h"

struct info;

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);

    void BackToMenu();

    void checkForWin(int lvl);

    ~MainMenu();

private slots:
    void delay(int msec);

    void on_exitButton_clicked();

    void on_loginButton_clicked();

    void on_chooseButton_clicked();

    void on_newButton_clicked();

    void on_oknewButton_clicked();

    void ReadDB();

    void WriteDB();

    void on_cancelButton_clicked();

    void on_recordButton_clicked();

    void on_okrecordButton_clicked();

    void Sort();

    void on_storyButton_clicked();

    void on_backButton_clicked();

    void on_helpButton_clicked();

    void on_aboutBack_clicked();

    QString readFile(QString filename);

    void firstlevel();

    void secondlevel();

    void thirdlevel();

    void fourthlevel();

    void fifthlevel();

    void sixlevel();

    void sevenlevel();

    void eightlevel();

    void ninelevel();

    void tenlevel();

    void on_firstlevel_clicked();

    void on_secondlevel_clicked();

    void on_thirdlevel_clicked();

    void on_fourthlevel_clicked();

    void on_fifthlevel_clicked();

    void on_sixlevel_clicked();

    void on_sevenlevel_clicked();

    void on_eightlevel_clicked();

    void on_ninelevel_clicked();

    void on_tenlevel_clicked();

    void on_xmlWriteButton_clicked();

public:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
