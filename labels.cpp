#include "labels.h"
Labels::Labels(QWidget *parent) : QLabel(parent) {
  setMinimumSize(1, 1);
  setAlignment(Qt::AlignCenter);
  setMouseTracking(true);
  setScaledContents(true);
  setBackgroundRole(QPalette::Shadow);
  setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  setFocusPolicy(Qt::StrongFocus);
  rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
  setDrawMode();
}
void Labels::setPixmap(QPixmap &p) {
  basePixmap = p;
  drawLabel();
  resize(pixmap()->size());
}
int Labels::heightForWidth(int width) const {
  return basePixmap.isNull()
             ? height()
             : static_cast<int>(
                   (static_cast<qreal>(basePixmap.height()) * width) /
                   basePixmap.width());
}
QSize Labels::sizeHint() const {
  int w = width();
  return QSize(w, heightForWidth(w));
}
void Labels::resizeEvent(QResizeEvent *e) {
  if (!basePixmap.isNull()) {
    drawLabel();
  } else {
    e->ignore();
  }
}
void Labels::zoom(double factor) {
  zoomFactor = factor;
  scalePixmap();
  if (zoomFactor == 1.0) {
    resize(basePixmap.size());
  } else {
    resize(scaledPixmap.size());
  }
}
QPixmap Labels::scalePixmap(void) {
  if (basePixmap.isNull())
    return QPixmap();
  if (shouldScaleContents) {
    scaledPixmap = basePixmap.scaled(size(), Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
  } else if (zoomFactor != 1.0) {
    scaledPixmap =
        basePixmap.scaled(zoomFactor * basePixmap.size(), Qt::KeepAspectRatio,
                          Qt::SmoothTransformation);
  } else {
    scaledPixmap = basePixmap;
  }
  scaledWidth = scaledPixmap.width();
  scaledHeight = scaledPixmap.height();
  scaleFactor = static_cast<float>(scaledHeight) / basePixmap.height();
  return scaledPixmap;
}
void Labels::setDrawMode() {
  curMode = DRAW;
  setCursor(Qt::CrossCursor);
  rubberBand->setGeometry(QRect(bbOrigin, QSize()));
  rubberBand->show();
}
void Labels::setDrawDragMode() {
  curMode = DRAW_DRAG;
  rubberBand->setGeometry(QRect(bbOrigin, QSize()));
  rubberBand->show();
}
void Labels::setSelectMode() {
  curMode = SELECTION;
  setCursor(Qt::ArrowCursor);
  rubberBand->hide();
}
QPoint Labels::getScaledImageLocation(QPoint loc) {
  QPoint scaledLoc = loc;
  if (scaleFactor != 1.0) {
    scaledLoc.setX(scaledLoc.x() - (width() - scaledWidth) / 2);
    scaledLoc.setY(scaledLoc.y() - (height() - scaledHeight) / 2);
    scaledLoc.setX(static_cast<int>(scaledLoc.x() / scaleFactor));
    scaledLoc.setY(static_cast<int>(scaledLoc.y() / scaleFactor));
  }
  return scaledLoc;
}
void Labels::mousePressEvent(QMouseEvent *ev) {
  if (basePixmap.isNull())
    return;
  QPoint imgLoc = ev->pos();
  if (curMode == SELECTION && ev->button() == Qt::LeftButton) {
    moving = true;
    lastPos = ev->pos();
    drawLabel(getScaledImageLocation(imgLoc));
  } else if (curMode == DRAW && ev->button() == Qt::LeftButton) {
    if (bbState == WAITING) {
      bbOrigin = imgLoc;
      rubberBand->setGeometry(QRect(bbOrigin, QSize()));
      rubberBand->show();
      bbState = DRAWING;
    } else if (bbState == DRAWING) {
      bbFinal = imgLoc;
      QRect bbox(bbOrigin, bbFinal);
      bbox = clip(bbox.normalized());
      bbOrigin = bbox.topLeft();
      bbFinal = bbox.bottomRight();
      rubberBand->setGeometry(bbox);
      bbState = WAITING;
    }
  }
}
QRect Labels::clip(QRect bbox) {
  auto xpad = (width() - scaledWidth) / 2;
  bbox.setLeft(std::max(xpad, bbox.left()));
  bbox.setRight(std::min(width() - xpad, bbox.right()));
  auto ypad = (height() - scaledHeight) / 2;
  bbox.setTop(std::max(ypad, bbox.top()));
  bbox.setBottom(std::min(height() - ypad, bbox.bottom()));
  return bbox;
}
void Labels::mouseReleaseEvent(QMouseEvent *ev) {
  ev->ignore();
  moving = false;
}
void Labels::mouseMoveEvent(QMouseEvent *ev) {
  if (basePixmap.isNull())
    return;
  if (bbState == DRAWING && curMode == DRAW) {
    QRect bbox = QRect(bbOrigin, ev->pos()).normalized();
    rubberBand->setGeometry(bbox);
  }

  if (curMode == SELECTION && moving && selectedBb.classname != "") {
    // move
    int xDiff = (ev->pos() - lastPos).x();
    int yDiff = (ev->pos() - lastPos).y();
    QPoint diff = QPoint(xDiff, yDiff);
    selectedBb.rect.setTopLeft(QPoint(selectedBb.rect.topLeft() + diff));
    selectedBb.rect.setBottomRight(
        QPoint(selectedBb.rect.bottomRight() + diff));
    for (QPointF point : selectedBb.points) {
      point.setX(point.x() + xDiff);
      point.setY(point.y() + yDiff);
    }
    std::cout << "moving!" << std::endl;
    lastPos = ev->pos();
    drawLabel(QPoint(), true);
  }
}
void Labels::drawBoundingBox(const BoundingBox &bbox) {
  auto colour_list = QColor::colorNames();
  QColor colour = QColor(100, 100, 100);
  drawBoundingBox(bbox, colour);
}
void Labels::drawBoundingBox(const BoundingBox &bbox, const QColor &colour) {
  if (scaledPixmap.isNull())
    return;
  QPainter painter;
  painter.begin(&scaledPixmap);
  QPen pen(colour, 2);
  painter.setPen(pen);
  auto scaled_bbox = bbox.rect;
  scaled_bbox.setRight(static_cast<int>(scaled_bbox.right() * scaleFactor));
  scaled_bbox.setLeft(static_cast<int>(scaled_bbox.left() * scaleFactor));
  scaled_bbox.setTop(static_cast<int>(scaled_bbox.top() * scaleFactor));
  scaled_bbox.setBottom(static_cast<int>(scaled_bbox.bottom() * scaleFactor));
  if (bbox.classname != "") {
    painter.setFont(QFont("Helvetica", 10));
    painter.drawText(scaled_bbox.bottomLeft(),
                     QString::fromStdString(bbox.classname));
  }
  switch (bbox.shape) {
  case ELLIPSE:
    painter.drawEllipse(scaled_bbox);
    break;
  default:
    QPointF arr[bbox.points.size()];
    for (int i = 0; i < bbox.points.size(); i++) {
      arr[i] = bbox.points[i] * scaleFactor;
    }
    painter.drawPolygon(arr, bbox.points.size());
    break;
  }
  painter.end();
}
void Labels::setPolyPoints(int points) { polyPoints = points; }
void Labels::setShape(myShape shape) { curShape = shape; }
void Labels::setBoundingBoxes(std::vector<BoundingBox> input_bboxes) {
  bboxes.clear();
  bboxes = input_bboxes;
  drawLabel();
}
void Labels::setClassname(const QString &classname) {
  curClass = classname;
  if (selectedBb.classname == "")
    return;
  if (selectedBb.classname != classname.toStdString()) {
    auto new_bbox = selectedBb;
    new_bbox.classname = classname.toStdString();
    emit updateLabel(selectedBb, new_bbox);
  }
}
void Labels::setScaledContents(bool should_scale) {
  shouldScaleContents = should_scale;
  if (!shouldScaleContents) {
    scaleFactor = 1.0;
  }
}
bool Labels::scaleContents(void) { return shouldScaleContents; }
void Labels::drawLabel(QPoint location, bool moving) {
  scalePixmap();
  if (scaleFactor == 1.0) {
    scaledPixmap = basePixmap;
  }
  if (moving) {
    drawBoundingBox(selectedBb, Qt::green);
  } else {
    BoundingBox bbox;
    selectedBb = BoundingBox();
    foreach (bbox, bboxes) {
      if (bbox.rect.contains(location)) {
        drawBoundingBox(bbox, Qt::green);
        selectedBb = bbox;
        emit setCurrentClass(QString::fromStdString(selectedBb.classname));
      } else {
        drawBoundingBox(bbox);
      }
    }
  }
  QLabel::setPixmap(scaledPixmap);
}
void Labels::addLabel(QRect rect, QString classname) {
  BoundingBox new_bbox;
  new_bbox.classname = classname.toStdString();
  new_bbox.imgPath = currentDir;
  new_bbox.shape = curShape;
  new_bbox.rect = rect;
  // HERE
  float x = new_bbox.rect.x();
  float xs = new_bbox.rect.x() + new_bbox.rect.width();
  float y = new_bbox.rect.y();
  float ys = new_bbox.rect.y() + new_bbox.rect.height();
  switch (new_bbox.shape) {
  case RECTANGLE: {
    new_bbox.points = std::vector<QPointF>{QPointF(x, y), QPointF(x, ys),
                                           QPointF(xs, ys), QPointF(xs, y)};
    break;
  }
  case TRIANGLE: {
    new_bbox.points = std::vector<QPointF>{
        QPointF((x + xs) / 2, y),
        QPointF(xs, ys),
        QPointF(x, ys),
    };
    break;
  }
  case PENTAGON: {
    new_bbox.points = std::vector<QPointF>{
        QPointF((x + xs) / 2, y),
        QPointF(xs, (y + ys) / 2),
        QPointF(x + (((xs - x) / 3) * 2), ys),
        QPointF(x + ((xs - x) / 3), ys),
        QPointF(x, (y + ys) / 2),
    };
    break;
  }
  case OCTAGON: {
    new_bbox.points = std::vector<QPointF>{
        QPointF(x + ((xs - x) / 3), y),
        QPointF(x + (((xs - x) / 3) * 2), y),
        QPointF(xs, y + ((ys - y) / 3)),
        QPointF(xs, y + (((ys - y) / 3) * 2)),
        QPointF(x + (((xs - x) / 3) * 2), ys),
        QPointF(x + ((xs - x) / 3), ys),
        QPointF(x, y + (((ys - y) / 3) * 2)),
        QPointF(x, y + ((ys - y) / 3)),
    };
    break;
  }
  default:
    new_bbox.points = std::vector<QPointF>{QPointF(x, y), QPointF(x, ys),
                                           QPointF(xs, ys), QPointF(xs, y)};
    break;
  }
  bboxes.push_back(new_bbox);
  emit newLabel(new_bbox);
  drawLabel();
}
void Labels::setDir(std::string newDir) { currentDir = newDir; }
void Labels::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
    emit removeLabel(selectedBb);
  } else if (event->key() == Qt::Key_Escape) {
    rubberBand->setGeometry(QRect(bbOrigin, QSize()));
    bbState = WAITING;
  } else if (event->key() == Qt::Key_Space && bbState == WAITING) {
    if (rubberBand->width() > 0 && rubberBand->height() > 0) {
      if (curClass == "") {
        // make this into a pop up error
      } else {
        QRect bbox_rect;
        bbox_rect = QRect(bbOrigin, bbFinal);
        bbox_rect.setTopLeft(getScaledImageLocation(bbox_rect.topLeft()));
        bbox_rect.setBottomRight(
            getScaledImageLocation(bbox_rect.bottomRight()));
        addLabel(bbox_rect, curClass);
        rubberBand->setGeometry(QRect(bbOrigin, QSize()));
      }
    } else if (event->key() == 'o') {
      emit setOccluded(selectedBb);
      drawLabel();
    }
  } else {
    event->ignore();
  }
}
