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

        int tileX = long2map(centerLon, zoom);
        int tileY = lat2map(centerLat, zoom);

        int widgetCenterX = widget->width() / 2;
        int widgetCenterY = widget->height() / 2;
        int tileSize = 256;

        for (int dx = -2; dx <= 2; ++dx) {
            for (int dy = -2; dy <= 2; ++dy) {
                int x = tileX + dx;
                int y = tileY + dy;
                int px = widgetCenterX + dx * tileSize;
                int py = widgetCenterY + dy * tileSize;

                QPixmap tile = getMap(x, y, zoom);
                painter.drawPixmap(px, py, tileSize, tileSize, tile);
            }
        }
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

int MapWidget::long2map(double lon, int z){ 
    return static_cast<int>(std::floor((lon + 180.0) / 360.0 * (1 << z)));
}

int MapWidget::lat2map(double lat, int z){
    double latRad = lat * M_PI / 180.0;
    return static_cast<int>(std::floor((1.0 - std::log(std::tan(latRad) + 1.0 / std::cos(latRad)) / M_PI) / 2.0 * (1 << z)));
}