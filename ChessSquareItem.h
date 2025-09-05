#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class ChessSquareItem : public QGraphicsRectItem
{
public:
    ChessSquareItem(int row, int col, const QRectF &rect)
        : QGraphicsRectItem(rect), m_row(row), m_col(col) {}

    int row() const { return m_row; }
    int col() const { return m_col; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emitSquareClicked();
        }
        QGraphicsRectItem::mousePressEvent(event);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        Q_UNUSED(option)
        Q_UNUSED(widget)
        // Draw normal rectangle without selection highlight
        painter->setBrush(brush());
        painter->setPen(QPen(Qt::NoPen));
        painter->drawRect(rect());
        // If you want a border, you can do something like:
        painter->setPen(QPen(Qt::black, 1));
        painter->drawRect(rect());
    }

private:
    int m_row;
    int m_col;

    void emitSquareClicked() {
        // Forward the click to the parent GUI
        // Using Qt's signal-slot system with QGraphicsItem is tricky
        // Instead, we'll use a callback (std::function)
        if (onClicked) {
            onClicked(m_row, m_col);
        }
    }

public:
    std::function<void(int,int)> onClicked;
};
