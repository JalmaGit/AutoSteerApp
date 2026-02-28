#ifndef MYAPP_HPP
#define MYAPP_HPP

#include <string>
#include <vector>

#include <QApplication>
#include <QPushButton>
#include <QLabel>

#include "MapWidget.hpp"

class MyApp
{
private:
    QLabel* label_;
    MapWidget* mapWidget_;
    std::vector<QString> names_;

public:
    MyApp();
    ~MyApp();
    void changeZoom(std::vector<QPushButton*>& buttons);
    void moveMap(std::vector<QPushButton*>& buttons);
    void addButtons(std::vector<QPushButton*>& buttons);

    int run(int argc, char *argv[]);
};

#endif