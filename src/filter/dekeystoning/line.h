#ifndef LINE_H
#define LINE_H

#include <QGraphicsLineItem>

class Corner;

class Line : public QGraphicsLineItem
{
public:
    Line(Corner *fromCorner, Corner *toCorner);
    void trackCorners();
private:
    Corner *fromCorner, *toCorner;
};

#endif // LINE_H
