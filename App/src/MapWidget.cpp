#include "MapWidget.hpp"

#include <QWidget>
#include <QNetworkReply>
#include <QMap>
#include <QPair>
#include <QPoint>
#include <QPainter>
#include <QEvent>
#include <cmath>
#include <memory>

MapWidget::MapWidget(QWidget *targetWidget) : widget(targetWidget),
                                              mapServerUrl("https://services.arcgisonline.com/arcgis/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}"),
                                              centerLat(0), centerLon(0), zoom(1)
{
    network = new QNetworkAccessManager(targetWidget);
    widget->setMinimumSize(100, 100);

    eventFilter = std::make_unique<MapEventFilter>(this);

    widget->installEventFilter(eventFilter.get());
}

void MapWidget::setMapServer(const QString &url)
{
    mapServerUrl = url;
    widget->update();
}

void MapWidget::setPosition(double lat, double lon)
{
    centerLat = lat;
    centerLon = lon;
    widget->update();
}

void MapWidget::setZoom(int z){
    zoom = z;
    widget->update();
}


void MapWidget::paint() {
        QPainter painter(widget);

        int widgetCenterX = widget->width() / 2;
        int widgetCenterY = widget->height() / 2;
        QPixmap tile = getMap(0, 0, 0);
        painter.drawPixmap(0,0,500,500,tile);

        painter.setBrush(Qt::red);
        painter.drawEllipse(QPoint(widgetCenterX, widgetCenterY), 7, 7);
    }

QString MapWidget::urlForMap(int x, int y, int z)
{
    return mapServerUrl.arg(z).arg(y).arg(x);
}

QPixmap MapWidget::getMap(int x, int y, int z)
{
    QString url = urlForMap(x, y ,z);

    if (mapCache.contains(url)){
        return mapCache.value(url);
    }
 
    QNetworkRequest* request = new QNetworkRequest(QUrl(url));
    QNetworkReply* reply = network->get(*request);

    QObject::connect(reply, &QNetworkReply::finished,[&, reply, url](){
        QPixmap pix;
        pix.loadFromData(reply->readAll());
        mapCache[url] = pix;
        reply->deleteLater();
        widget->update();
    });
    
    return QPixmap();
}