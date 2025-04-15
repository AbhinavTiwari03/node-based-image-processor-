#include "Node.h"
#include "Connection.h"

Node::~Node() {
    for (Connection* conn : m_connections) {
        delete conn;
    }
}
QPointF Node::inputPortPosition() const {
    return QPointF(boundingRect().left(), boundingRect().center().y());
}


QPointF Node::outputPortPosition() const {
    return QPointF(boundingRect().right(), boundingRect().center().y());
}

void Node::addConnection(Connection* connection) {
    m_connections.append(connection);
}


void Node::removeConnection(Connection* connection) {
    m_connections.removeAll(connection);
}


QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value) {
    if (change == ItemPositionChange) {
        for (Connection* conn : m_connections) {
            conn->updatePath();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
Node::Node(QGraphicsItem* parent) : QGraphicsItem(parent) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF Node::boundingRect() const {
    return QRectF(0, 0, 150, 100); // Node size
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Draw node body
    painter->setBrush(Qt::lightGray);
    painter->drawRoundedRect(boundingRect(), 5, 5);

    // Draw ports (input/output circles) dynamically
    QRectF rect = boundingRect();
    constexpr qreal portSize = 20.0;
    qreal y = rect.center().y() - portSize / 2;

    // Input port
    painter->setBrush(Qt::blue);
    painter->drawEllipse(QPointF(rect.left() + 10 + portSize / 2, y + portSize / 2), portSize / 2, portSize / 2);

    // Output port
    painter->drawEllipse(QPointF(rect.right() - 10 - portSize / 2, y + portSize / 2), portSize / 2, portSize / 2);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value) {
    if (change == ItemPositionChange && scene()) {
        emit positionChanged(value.toPointF());
    }
    return QGraphicsItem::itemChange(change, value);
}
