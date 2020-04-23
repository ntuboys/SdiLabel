#ifndef LABELPROJECT_H
#define LABELPROJECT_H
#include <BoundingBox.h>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QMessageBox>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QProgressDialog>
#include <QThread>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
class Files : public QObject {
  Q_OBJECT
public:
  bool loadLabels(std::string fileName, std::vector<BoundingBox> &);
  bool saveLabels(std::string fileName, std::vector<BoundingBox>);

private:
  bool readLabels(std::ifstream &fs, std::vector<BoundingBox> &);
  bool writeLabels(std::ofstream &fs, std::vector<BoundingBox>);
};
#endif // LABELPROJECT_H
