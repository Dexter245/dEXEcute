#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>
#include <QGroupBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

//class QGroupBox;
//class QCheckBox;
//class QSpinBox;
//class QLineEdit;

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


    //TODO use dconst once merged!
    const int NUM_REGISTERS = 16;
    const std::string reg_names[16] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
        "l0", "l1", "sr", "ip", "ir", "rp0", "rp1", "-"};

};

#endif // MAINWINDOW_H
