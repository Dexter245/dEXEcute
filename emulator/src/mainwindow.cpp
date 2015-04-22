#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    createSettingsArea();
    createControlArea();
    createInfoArea();
    createRegisterArea();
    createRamArea();
    createRomArea();
    createLogArea();

//    QVBoxLayout *scrollLayout = new QVBoxLayout();

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(settingsBox);
    mainLayout->addWidget(controlBox);
    mainLayout->addWidget(infoBox);
    mainLayout->addWidget(registerBox);
    mainLayout->addWidget(ramBox);
    mainLayout->addWidget(romBox);
    mainLayout->addWidget(logBox);

    //mainScrollArea = new QScrollArea();
    //mainScrollArea->setLayout(mainLayout);
    //mainScrollArea->setWidget(this);

    //scrollLayout->addWidget(mainScrollArea);
    //mainScrollArea.setWidget(mainLayout);

    //setLayout(scrollLayout);
    setLayout(mainLayout);

    //ram rom und log nach rechts seitlich

    //mainScrollArea = new QScrollArea();
    //mainScrollArea->setWidget(registerBox);
    //mainScrollArea->show();

    //setLayout(mainScrollArea);
    //addWidget(mainScrollArea);

}

void MainWindow::createSettingsArea(){
    //init widgets
    settingsBox = new QGroupBox("Settings");
    settings_continExec = new QCheckBox();
    settings_maxSpeed = new QCheckBox();
    settings_execSpeed = new QSpinBox();
    settings_dexeFilename = new QLineEdit();

    //settings
    settings_execSpeed->setMaximum(1000);

    //add widgets
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(new QLabel("Continuous Execution: "));
    layout->addWidget(settings_continExec);
    layout->addWidget(new QLabel("Maximum emulation speed: "));
    layout->addWidget(settings_maxSpeed);
    layout->addWidget(new QLabel("Execution Speed(Hz): "));
    layout->addWidget(settings_execSpeed);
    layout->addWidget(new QLabel("dexe filename: "));
    layout->addWidget(settings_dexeFilename);

    settingsBox->setLayout(layout);
}

void MainWindow::createControlArea(){
    //init widgets
    controlBox = new QGroupBox("Control");
    control_start = new QPushButton("Start");
    control_pause = new QPushButton("Pause");
    control_reset = new QPushButton("Reset");
    control_step = new QPushButton("Step");

    //add widgets
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(control_start);
    layout->addWidget(control_pause);
    layout->addWidget(control_reset);
    layout->addWidget(control_step);

    controlBox->setLayout(layout);
}

void MainWindow::createInfoArea(){
    //init widgets
    infoBox = new QGroupBox("Info");
    info_instrExecuted = new QLabel("0");
    info_running = new QLabel("no");
    info_paused = new QLabel("no");
    info_reset = new QLabel("yes");

    //add widgets
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(new QLabel("Instructions Executed: "));
    layout->addWidget(info_instrExecuted);
    layout->addWidget(new QLabel("Running: "));
    layout->addWidget(info_running);
    layout->addWidget(new QLabel("Paused: "));
    layout->addWidget(info_paused);
    layout->addWidget(new QLabel("Reset: "));
    layout->addWidget(info_reset);

    infoBox->setLayout(layout);
}

void MainWindow::createRegisterArea(){
    //create widgets
    registerBox = new QGroupBox("Registers");
    QGridLayout *gridLayout = new QGridLayout();
    //QVBoxLayout *vLayout = new QVBoxLayout();
    //QHBoxLayout *hLayout0 = new QHBoxLayout();
    //QHBoxLayout *hLayout1 = new QHBoxLayout();


    for(int i = 0; i < NUM_REGISTERS; i++){

        //auto newVec = std::vector<QLabel*>();
        std::vector<QLabel*> newVec;
        QLabel *qLab = new QLabel(QString::fromStdString(reg_names[i]));
        newVec.push_back(qLab);
        newVec.push_back(new QLabel("65535"));
        newVec.push_back(new QLabel("FF"));
        newVec.push_back(new QLabel("255 255"));
        reg_labels.push_back(newVec);

    }

    //add widgets
    int counter = 0;
    for(auto it = reg_labels.begin(); it != reg_labels.end(); ++it){
        //auto *vlay = new QVBoxLayout();
        int counter2 = 0;
        for(auto it2 = it->begin(); it2 != it->end(); ++it2){

            if(counter < 8)
                gridLayout->addWidget(*it2, counter2, counter);
            else
                gridLayout->addWidget(*it2, counter2+6, counter-8);
            if(counter2 == 3 && counter < 8){
                gridLayout->addWidget(new QLabel("------"), ++counter2,
                        counter);
            }
            counter2++;
        }
        counter++;
        //if(counter < 8)
            //hLayout0->addLayout(vlay);
        //else
            //hLayout1->addLayout(vlay);
    }

    //vLayout->addLayout(hLayout0);
    //vLayout->addLayout(hLayout1);
    //registerBox->setLayout(vLayout);

    registerBox->setLayout(gridLayout);

}

void MainWindow::createRamArea(){
    ramBox = new QGroupBox("RAM");

    QGridLayout *gridLayout = new QGridLayout();

    //create widgets
    ram_showingAddr = new QLabel("Showing Address: 123");
    QLabel *ram_gotoAddrLabel = new QLabel("Goto Address: ");
    ram_gotoAddr = new QLineEdit();
    ram_gotoAddrButton = new QPushButton("Go");
    ram_ramDisplay = new QTextEdit("asdf");

    //add widgets
    gridLayout->addWidget(ram_showingAddr, 0, 0);
    gridLayout->addWidget(ram_gotoAddrLabel, 0, 1);
    gridLayout->addWidget(ram_gotoAddr, 0, 2);
    gridLayout->addWidget(ram_gotoAddrButton, 0, 3);
    gridLayout->addWidget(ram_ramDisplay, 1, 0, 1, 4);

    ramBox->setLayout(gridLayout);

}

void MainWindow::createRomArea(){

    romBox = new QGroupBox("ROM");

    QGridLayout *gridLayout = new QGridLayout();

    //create widgets
    rom_showingAddr = new QLabel("Showing Address: 123");
    QLabel *rom_gotoAddrLabel = new QLabel("Goto Address: ");
    rom_gotoAddr = new QLineEdit();
    rom_gotoAddrButton = new QPushButton("Go");
    rom_romDisplay = new QTextEdit("asdf");

    //add widgets
    gridLayout->addWidget(rom_showingAddr, 0, 0);
    gridLayout->addWidget(rom_gotoAddrLabel, 0, 1);
    gridLayout->addWidget(rom_gotoAddr, 0, 2);
    gridLayout->addWidget(rom_gotoAddrButton, 0, 3);
    gridLayout->addWidget(rom_romDisplay, 1, 0, 1, 4);

    romBox->setLayout(gridLayout);

}

void MainWindow::createLogArea(){

    logBox = new QGroupBox("Log");

    QGridLayout *gridLayout = new QGridLayout();

    //create widgets
    log_logDisplay = new QTextEdit("log comes here");

    //add widgets
    gridLayout->addWidget(log_logDisplay);

    logBox->setLayout(gridLayout);

}

MainWindow::~MainWindow()
{

}
