#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QVariant>
#include <opencv2/opencv.hpp>

class Node : public QGraphicsItem {
public:
    QPointF inputPortPosition() const;
    QPointF outputPortPosition() const;
    void addConnection(Connection* connection);
    void removeConnection(Connection* connection);
    explicit Node(QGraphicsItem* parent = nullptr);



    explicit Node(QGraphicsItem* parent = nullptr);
    ~Node() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    virtual void process() = 0;
    cv::Mat inputImage;
    cv::Mat outputImage;
    enum { Type = UserType + 1 };
    int type() const override { return Type; }


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
signals:
    void positionChanged(const QPointF& newPos);
private:
    QList<Connection*> m_connections;
};

