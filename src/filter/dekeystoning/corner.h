#ifndef CORNER_H
#define CORNER_H

#include <QGraphicsEllipseItem>
#include <QWheelEvent>

class Line;

class Corner : public QGraphicsEllipseItem
{
public:
    Corner(qreal x, qreal y);
    void addLine(Line *line);
    void removeLine(Line *line);
    bool getCornerMoved();
    void resetCornerMoved();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    QSet<Line *> myLines;
    qreal x, y;
    bool cornerMoved;
};

#endif // CORNER_H
