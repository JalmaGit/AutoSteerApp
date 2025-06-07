#include "MyApp.hpp"

#include <iostream>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QObject>
#include <QPixmap>

#include "MapWidget.hpp"

MyApp::MyApp(/* args */)
{
}

MyApp::~MyApp()
{
}

int MyApp::run(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget* window = new QWidget;
    window->setWindowTitle("Auto Steer Delux");
    
    QLabel* label = new QLabel("Hello, World!");
    QPushButton* button1 = new QPushButton("Click Me!");
    QPushButton* button2 = new QPushButton("Click Me!");
    
    QLabel* imageLabel = new QLabel;
    QPixmap pixmap("bin/data/Saab93.jpg");
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);

    QObject::connect(button1, &QPushButton::clicked, [&](){
        label->setText("Button 1 Clicked");
    });

    QObject::connect(button2, &QPushButton::clicked, [&](){
        label->setText("Button 2 Clicked");
        //std::cout << "Button Clicked" << std::endl;

    });

    QWidget* mapView = new QWidget(window);
    mapView->setMinimumSize(600,400);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(button1, 3, 0);
    layout->addWidget(button2, 3, 1);
    layout->addWidget(mapView,2,0,1,2,Qt::AlignCenter);
    layout->addWidget(label, 1, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(imageLabel,0 ,0 , 1, 2);

    MapWidget* mapWidget = new MapWidget(mapView);
    //mapWidget->setPosition(0,0);
    //mapWidget->setZoom(0);

    window->setLayout(layout);
    window->resize(700,1000);
    window->show();

    return app.exec();
}