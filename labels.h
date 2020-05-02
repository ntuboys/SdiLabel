#ifndef IMAGELABEL_H
#define IMAGELABEL_H
#include <BoundingBox.h>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>
#include <QRubberBand>
#include <opencv2/opencv.hpp>
enum drawState {
  WAITING,
  DRAWING,
};
enum interactionState {
  DRAW,
  DRAW_DRAG,
  SELECTION,
};
class Labels : public QLabel {
  Q_OBJECT
public:
  explicit Labels(QWidget *parent = nullptr);
  virtual int heightForWidth(int width) const;
  virtual QSize sizeHint() const;
  void setScaledContents(bool scale_factor);
  std::vector<BoundingBox> getBoundingBoxes() { return bboxes; }
  cv::Mat getImage(void) { return image; }
  bool scaleContents(void);
  void setDir(std::string);
  void setPolyPoints(int);
  void setShape(myShape);
signals:
  void newLabel(BoundingBox);
  void removeLabel(BoundingBox);
  void updateLabel(BoundingBox, BoundingBox);
  void setOccluded(BoundingBox);
  void setCurrentClass(QString);
public slots:
  void setPixmap(QPixmap &);
  void setImage(cv::Mat &image) { this->image = image; }
  void setBoundingBoxes(std::vector<BoundingBox> input_bboxes);
  void setClassname(const QString &classname);
  void addLabel(QRect rect, QString classname);
  void zoom(double factor);
  void setDrawMode();
  void setDrawDragMode();
  void setSelectMode();
  void resizeEvent(QResizeEvent *);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void keyPressEvent(QKeyEvent *event);

private:
  std::string currentDir = "";
  cv::Mat image;
  QPixmap pix;
  QPixmap basePixmap;
  QPixmap scaledPixmap;
  QString curClass;
  bool shouldScaleContents = false;
  std::vector<BoundingBox> bboxes;
  BoundingBox selectedBb;
  void drawBoundingBox(const BoundingBox &bbox);
  void drawBoundingBox(const BoundingBox &bbox, const QColor &colour);
  void drawLabel(QPoint location = QPoint());
  QPoint getScaledImageLocation(QPoint loc);
  QPixmap scalePixmap(void);
  QRect clip(QRect bbox);
  QPainter *painter;
  drawState bbState = WAITING;
  interactionState curMode = DRAW;
  QPoint bbOrigin, bbFinal;
  QRubberBand *rubberBand;
  int bbWidth = 0;
  int bbHeight = 0;
  double scaleFactor = 1.0;
  double zoomFactor = 1.0;
  int scaledWidth;
  int scaledHeight;
  myShape curShape = RECTANGLE;
  int polyPoints = -1;
  void drawBoundingBoxes(QPoint location);
};
#endif // IMAGELABEL_H
