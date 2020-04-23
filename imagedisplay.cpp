#include "imagedisplay.h"
#include "ui_imagedisplay.h"
std::unordered_map<std::string, int> ImageDisplay::colourHashmap{
    {"Cividis", cv::COLORMAP_CIVIDIS}, {"Inferno", cv::COLORMAP_INFERNO},
    {"Magma", cv::COLORMAP_MAGMA},     {"Hot", cv::COLORMAP_HOT},
    {"Bone", cv::COLORMAP_BONE},       {"Plasma", cv::COLORMAP_PLASMA},
    {"Jet", cv::COLORMAP_JET},         {"Rainbow", cv::COLORMAP_RAINBOW},
    {"Ocean", cv::COLORMAP_OCEAN},     {"Viridis", cv::COLORMAP_VIRIDIS}};
ImageDisplay::ImageDisplay(QWidget *parent)
    : QWidget(parent), ui(new Ui::ImageDisplay) {
  ui->setupUi(this);
  imageLabel = new Labels;
  scrollArea = new QScrollArea(this);
  ui->main->addWidget(scrollArea);
  scrollArea->setWidget(imageLabel);
  scrollArea->setAlignment(Qt::AlignCenter);
  scrollArea->setBackgroundRole(QPalette::Shadow);
  connect(ui->btnAutoFit, SIGNAL(clicked()), this, SLOT(updateDisplay()));
  connect(ui->spnZoom, SIGNAL(valueChanged(int)), this, SLOT(scaleImage()));
  updateDisplay();
}
ImageDisplay::~ImageDisplay() { delete ui; }
void ImageDisplay::setImagePath(const QString &path) {
  if (path != "") {
    currentImagepath = path;
    loadPixmap();
  }
}
void ImageDisplay::clearPixmap(void) {
  pixmap = QPixmap();
  imageLabel->setPixmap(pixmap);
}
void ImageDisplay::convert16(cv::Mat &source, double minval, double maxval) {
  if (minval < 0 || maxval < 0) {
    cv::minMaxIdx(source, &minval, &maxval);
  }
  double range = maxval - minval;
  double scaleFactor = 255.0 / range;
  source.convertTo(source, CV_32FC1);
  source -= minval;
  source *= scaleFactor;
  source.convertTo(source, CV_8UC1);
  return;
}
cv::Mat ImageDisplay::getOriginalImage(void) { return originalImage; }
void ImageDisplay::loadPixmap() {
  if (currentImagepath == "")
    return;
  originalImage = cv::imread(currentImagepath.toStdString(),
                             cv::IMREAD_UNCHANGED | cv::IMREAD_ANYDEPTH);
  if (originalImage.empty()) {
    qDebug() << "Failed to load image " << currentImagepath;
    return;
  }
  displayImage = originalImage.clone();
  // Default to single channel 8-bit image
  format = QImage::Format_Grayscale8;
  bitDepth = 8;
  if (originalImage.elemSize() == 2) {
    convert16(displayImage);
    bitDepth = 16;
  }
  if (displayImage.channels() == 3) {
    cv::cvtColor(displayImage, displayImage, cv::COLOR_BGR2RGB);
    format = QImage::Format_RGB888;
    bitDepth = 24;
  } else if (displayImage.channels() == 4) {
    cv::cvtColor(displayImage, displayImage, cv::COLOR_BGRA2RGBA);
    format = QImage::Format_RGBA8888;
    bitDepth = 32;
  } else if (displayImage.channels() == 1 && applyColourmap) {
    cv::applyColorMap(displayImage, displayImage, colourMap);
    cv::cvtColor(displayImage, displayImage, cv::COLOR_BGR2RGB);
    format = QImage::Format_RGB888;
  }
  pixmap =
      QPixmap::fromImage(QImage(displayImage.data, displayImage.cols,
                                displayImage.rows, displayImage.step, format));
  imageLabel->setImage(displayImage);
  updateDisplay();
  emit image_loaded();
}
void ImageDisplay::setColourMap(const QString &map) {
  auto map_str = map.toStdString();
  if (colourHashmap.count(map_str)) {
    colourMap = colourHashmap[map_str];
    loadPixmap();
  }
}
void ImageDisplay::toggleColourMap(bool enable) {
  applyColourmap = enable;
  loadPixmap();
}
void ImageDisplay::adjustScrollBar(QScrollBar *scrollBar, double factor) {
  scrollBar->setValue(int(factor * scrollBar->value() +
                          ((factor - 1) * scrollBar->pageStep() / 2)));
}
void ImageDisplay::scaleImage(void) {
  if (pixmap.isNull())
    return;
  imageScaleFactor = static_cast<double>(ui->spnZoom->value()) / 100.0;
  imageLabel->zoom(imageScaleFactor);
  adjustScrollBar(scrollArea->horizontalScrollBar(), imageScaleFactor);
  adjustScrollBar(scrollArea->verticalScrollBar(), imageScaleFactor);
}
void ImageDisplay::zoomIn() {
  if (fitToWindow)
    return;
  ui->spnZoom->setValue(ui->spnZoom->value() * 1.2);
}
void ImageDisplay::zoomOut() {
  if (fitToWindow)
    return;
  ui->spnZoom->setValue(ui->spnZoom->value() * 0.8);
}
void ImageDisplay::resetZoom() { ui->spnZoom->setValue(100); }
void ImageDisplay::updateDisplay() {
  if (pixmap.isNull())
    return;
  fitToWindow = ui->btnAutoFit->isChecked();
  scrollArea->setWidgetResizable(fitToWindow);
  imageLabel->setScaledContents(fitToWindow);
  imageLabel->setPixmap(pixmap);
}
