#ifndef MAPWIDGET_HPP
#define MAPWIDGET_HPP

#include <QWidget>
#include <QString>
#include <QNetworkAccessManager>
#include <QPainter>
#include <QPoint>
#include <QPixmap>
#include <QEvent>

class MapWidget
{

public:
    MapWidget(QWidget *targetWidget);

    void setMapServer(const QString& url);
    void setPosition(double lat, double lon);
    void setZoom(int z);

private:
    QWidget *widget;
    QString mapServerUrl;
    double centerLat, centerLon;
    int zoom;

    struct MapEventFilter : public QObject {
        MapWidget* parent;
        MapEventFilter(MapWidget* p) : QObject(p->widget), parent(p) {}
        bool eventFilter(QObject* obj, QEvent* event) override {
            if (obj == parent->widget && event->type() == QEvent::Paint) {
                parent->paint();
                return true;
            }
            return false;
        }
    };

    std::unique_ptr<MapEventFilter> eventFilter;
    
    QNetworkAccessManager* network;
    QMap<QString, QPixmap> mapCache;

    void paint();
    QString urlForMap(int x, int y, int z);
    QPixmap getMap(int x, int y, int z);

    int long2map(double lon, int z);
    int lat2map(double lat, int z);
};

#endif