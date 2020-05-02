#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "linkedlist.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QProgressDialog>
#include <QScreen>
#include <QScrollArea>
#include <QSettings>
#include <QTemporaryDir>
#include <QThread>
#include <QtConcurrent>
#include <algorithm>
#include <fileio.h>
#include <imagedisplay.h>
#include <labels.h>
#include <opencv2/opencv.hpp>
#include <structs.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  struct ImagesPanelItem {
    QString name;
    QString imageDir;
  };

private:
  Ui::MainWindow *ui;
  Files *project;
  Labels *currentImage;
  QScrollArea *imageScrollArea;
  ImageDisplay *display;
  void initDisplay();
  std::vector<image> images;
  LinkedList classes;
  std::vector<BoundingBox> bboxes;
  QString currentImagepath;
  QString curClass;
  void updateClassList();
  void updateLabels();
  bool loadClasses();
  QSettings *settings;
private slots:
  void saveLabels();
  void saveClasses();
  void openLabels();
  void openClasses();
  void openImagesFolder();
  void setShapeRect();
  void setShapeTri();
  void setShapePent();
  void setShapeOcta();
  void setShapeEllip();
  void updateDisplay(void);
  void addClass(void);
  void setCurrentClass(const QString &);
  void addLabel(const BoundingBox &bbox);
  void removeLabel(const BoundingBox &bbox);
  void updateLabel(const BoundingBox &oldBbox, const BoundingBox &newBbox);
  void removeImageLabels(void);
  void setDrawMode(void);
  void setSelectMode(void);
  void onListWidgetItemClicked(QListWidgetItem *);
signals:
  void selectedClass(QString);
};
#endif // MAINWINDOW_H
