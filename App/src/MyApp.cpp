#include "MyApp.hpp"

#include <iostream>

#include <QDebug>
#include <QGridLayout>
#include <QWidget>
#include <QObject>
#include <QPixmap>

#include "MapWidget.hpp"

MyApp::MyApp(/* args */)
{
    names_ = {"Zoom Out", "Zoom In", "Move Up", "Move Down", "Move Left", "Move Right"};
}

MyApp::~MyApp()
{
}

void MyApp::changeZoom(std::vector<QPushButton*>& buttons){
    int zoomLevel = 10;
    mapWidget_->setZoom(zoomLevel);

    QObject::connect(buttons[1], &QPushButton::clicked, [&](){
        label_->setText("Zoomed In");
        zoomLevel++;

        if (zoomLevel > 10){zoomLevel = 10;}
        mapWidget_->setZoom(zoomLevel);
    });

    QObject::connect(buttons[0], &QPushButton::clicked, [&](){
        label_->setText("Zoomed Out");
        zoomLevel--;

        if (zoomLevel < 0) {zoomLevel = 0;}
        mapWidget_->setZoom(zoomLevel);
    });

}

void MyApp::moveMap(std::vector<QPushButton*>& buttons){    
    int latMovement = 0;
    int lonMovement = 0;

    QObject::connect(buttons[2], &QPushButton::clicked, [&](){
        label_->setText("Moved Right");
        latMovement++;

        if (latMovement > 10){latMovement = 10;}
        mapWidget_->setZoom(latMovement);
    });

    QObject::connect(buttons[3], &QPushButton::clicked, [&](){
        label_->setText("Moved Left");
        latMovement--;

        if (latMovement < 0){latMovement = 0;}
        mapWidget_->setZoom(latMovement);
    });
}

void MyApp::addButtons(std::vector<QPushButton*>& buttons){

    for(int i = 0; i < names_.size(); i++){
        QPushButton* newButton = new QPushButton(names_[i]);
        buttons.push_back(newButton);
    }

    changeZoom(buttons);
   // moveMap(buttons);
}

int MyApp::run(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget* window = new QWidget;
    window->setWindowTitle("Auto Steer Delux");

    label_ = new QLabel("Hello, World!");
    
    QLabel* imageLabel = new QLabel;
    QPixmap pixmap("bin/data/Saab93.jpg");
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);

    QWidget* mapView = new QWidget(window);
    mapView->setMinimumSize(500,400);

    mapWidget_ = new MapWidget(mapView);

    std::vector<QPushButton*> buttons;
    addButtons(buttons);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(buttons[0], 3, 0);
    layout->addWidget(buttons[1], 3, 1);
   // layout->addWidget(buttons[2], 3, 0);
   // layout->addWidget(buttons[3], 3, 1);
    layout->addWidget(mapView,2,0,1,2,Qt::AlignCenter);
    layout->addWidget(label_, 1, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(imageLabel,0 ,0 , 1, 2);

    window->setLayout(layout);
    window->resize(700,1000);
    window->show();

    return app.exec();
}