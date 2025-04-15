#include "Connection.h"
#include "Node.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

Connection::Connection(Node* startNode, Node* endNode, QGraphicsItem* parent)
    : QGraphicsPathItem(parent), m_startNode(startNode), m_endNode(endNode) {

    setFlag(QGraphicsItem::ItemIsSelectable);
    setZValue(-1); 

    if (m_startNode) m_startNode->addConnection(this);
    if (m_endNode) m_endNode->addConnection(this);

    updatePath();
}

Connection::~Connection() {
    if (m_startNode) m_startNode->removeConnection(this);
    if (m_endNode) m_endNode->removeConnection(this);
}

void Connection::setStartNode(Node* node) {
    m_startNode = node;
    if (node) node->addConnection(this);
    updatePath();
}

void Connection::setEndNode(Node* node) {
    m_endNode = node;
    if (node) node->addConnection(this);
    updatePath();
}

void Connection::updatePath() {
    QPainterPath path;

    if (m_startNode && m_endNode) {
        // Get port positions
        QPointF startPos = m_startNode->outputPortPosition();
        QPointF endPos = m_endNode->inputPortPosition();

        // Create curved path
        QPointF ctr1(startPos.x() + 100, startPos.y());
        QPointF ctr2(endPos.x() - 100, endPos.y());

        path.moveTo(startPos);
        path.cubicTo(ctr1, ctr2, endPos);
    }

    setPath(path);
}

void Connection::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    Q_UNUSED(option)
        Q_UNUSED(widget)

        painter->setPen(QPen(m_color, m_lineWidth, Qt::SolidLine, Qt::RoundCap));
    painter->drawPath(path());
}

void Connection::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    setSelected(true);
    QGraphicsItem::mousePressEvent(event);
}

void Connection::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseMoveEvent(event);
}

void Connection::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseReleaseEvent(event);
}
