#include "NotationReporter.h"
#include <QDebug>

NotationReporter::NotationReporter() {}

void NotationReporter::Note(QPoint from, QPoint to, ChessPiece *piece, ChessPiece *toPiece)
{

    qDebug() << "move from " << from.x() << " " << from.y();
}
