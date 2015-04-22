#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>
#include <QBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createSettingsArea();
    void createControlArea();
    void createInfoArea();
    void createRegisterArea();
    void createRamArea();
    void createRomArea();
    void createLogArea();

    QHBoxLayout *mainLayout;
    QVBoxLayout *mainLeftLayout;
    QVBoxLayout *mainRightLayout;


    //settings widgets
    QGroupBox *settingsBox;
    QCheckBox *settings_continExec;
    QCheckBox *settings_maxSpeed;
    QSpinBox *settings_execSpeed;
    QLineEdit *settings_dexeFilename;

    //control widgets
    QGroupBox *controlBox;
    QPushButton *control_start;
    QPushButton *control_pause;
    QPushButton *control_reset;
    QPushButton *control_step;

    //info widgets
    QGroupBox *infoBox;
    QLabel *info_instrExecuted;
    QLabel *info_running;
    QLabel *info_paused;
    QLabel *info_reset;

    //register widgets
    QGroupBox *registerBox;
    std::vector<std::vector<QLabel*> > reg_labels;

    //ram widgets
    QGroupBox *ramBox;
    QLabel *ram_showingAddr;
    QLineEdit *ram_gotoAddr;
    QPushButton *ram_gotoAddrButton;
    QTextEdit *ram_ramDisplay;

    //rom widgets
    QGroupBox *romBox;
    QLabel *rom_showingAddr;
    QLineEdit *rom_gotoAddr;
    QPushButton *rom_gotoAddrButton;
    QTextEdit *rom_romDisplay;

    //log widgets
    QGroupBox *logBox;
    QTextEdit *log_logDisplay;




};

#endif // MAINWINDOW_H
