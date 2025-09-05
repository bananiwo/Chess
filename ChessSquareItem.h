#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class ChessSquareItem : public QGraphicsRectItem
{
public:
    enum HighlightState{
        None, Selected, AvailableMove
    };

    ChessSquareItem(int row, int col, const QRectF &rect)
        : QGraphicsRectItem(rect), m_row(row), m_col(col)
    {
        setAcceptHoverEvents(true);
    }

    void setHighlight(HighlightState state) {
        m_highlight = state;
        update(); // trigger repaint
    }
    HighlightState highlight() const { return m_highlight; }
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
        QColor baseColor = ((m_row + m_col) % 2 == 0) ? QColor("#E57A44") : QColor("#E3D985");
        painter->setBrush(baseColor);
        painter->setPen(QPen(Qt::black, 1));
        painter->drawRect(rect());
        // Overlay highlight if needed
        if (m_highlight == Selected) {
            QColor selColor(188, 216, 193, 150); // semi-transparent yellow
            painter->fillRect(rect(), selColor);
        } else if (m_highlight == AvailableMove) {
            QColor moveColor(191, 189, 193, 100); // semi-transparent blue
            painter->fillRect(rect(), moveColor);
        }
    }

private:
    int m_row;
    int m_col;
    HighlightState m_highlight = HighlightState::None;

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
