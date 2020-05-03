#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <QRect>
#include <QString>
#include <vector>

enum myShape { ELLIPSE, RECTANGLE, PENTAGON, OCTAGON, TRIANGLE, POLYGON };

typedef struct BoundingBox {
  QRect rect = QRect(0, 0, 0, 0);
  std::vector<QPointF> points;
  std::string classname = "";
  std::string imgPath = "";
  int occluded = 0;
  myShape shape = RECTANGLE;
} BoundingBox;

#endif // BOUNDINGBOX_H
