#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H
#include <QApplication>
#include <QScrollArea>
#include <QScrollBar>
#include <QTemporaryDir>
#include <QWidget>
#include <labels.h>
#include <opencv2/opencv.hpp>
#include <unordered_map>
namespace Ui {
class ImageDisplay;
}
class ImageDisplay : public QWidget {
  Q_OBJECT
public:
  explicit ImageDisplay(QWidget *parent = nullptr);
  ~ImageDisplay();
public slots:
  void setImagePath(const QString &path);
  Labels *getImageLabel(void) { return imageLabel; }
  int getBitDepth(void) { return bitDepth; }
  void setColourMap(const QString &map);
  void toggleColourMap(bool enable);
  cv::Mat getOriginalImage();
  void clearPixmap();

private:
  cv::Mat displayImage;
  cv::Mat originalImage;
  QPixmap pixmap;
  Ui::ImageDisplay *ui;
  QString currentImagepath;
  void convert16(cv::Mat &source, double minval = -1, double maxval = -1);
  Labels *imageLabel;
  QScrollArea *scrollArea;
  bool fitToWindow = false;
  double imageScaleFactor = 1.0;
  bool applyColourmap = true;
  int colourMap = cv::COLORMAP_MAGMA;
  QImage::Format format = QImage::Format_Grayscale8;
  int bitDepth = 8;
  static std::unordered_map<std::string, int> colourHashmap;
private slots:
  void loadPixmap();
  void updateDisplay();
  void resetZoom();
  void scaleImage();
  void adjustScrollBar(QScrollBar *scrollBar, double factor);
  void zoomIn();
  void zoomOut();
signals:
  void image_loaded();
};
#endif // IMAGEDISPLAY_H
