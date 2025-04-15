#pragma once
#include <QGraphicsPathItem>

class Node;
class QGraphicsSceneMouseEvent;

class Connection : public QGraphicsPathItem {
public:
    Connection(Node* startNode = nullptr, Node* endNode = nullptr,
        QGraphicsItem* parent = nullptr);
    ~Connection();
    void setStartNode(Node* node);
    void setEndNode(Node* node);
    void updatePath();

    // Getters
    Node* startNode() const { return m_startNode; }
    Node* endNode() const { return m_endNode; }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget = nullptr) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    Node* m_startNode;
    Node* m_endNode;
    QPointF m_startPos;
    QPointF m_endPos;
    QColor m_color = Qt::darkGray;
    qreal m_lineWidth = 2.0;
};
