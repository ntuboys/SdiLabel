#include "fileio.h"
using json = nlohmann::json;
bool Files::loadLabels(const std::string fileName,
                       std::vector<BoundingBox> &bboxes) {
  std::ifstream fs(fileName);
  if (!fs.is_open()) {
    std::cout << "error opening file to load" << std::endl;
    fs.close();
    return false;
  }
  if (!readLabels(fs, bboxes)) {
    std::cout << "error reading file to load" << std::endl;
    fs.close();
    return false;
  }
  fs.close();
  return true;
}
bool Files::saveLabels(const std::string fileName,
                       std::vector<BoundingBox> bboxes) {
  std::cout << "saving to " << fileName << std::endl;
  std::ofstream fs(fileName, std::ofstream::out | std::ofstream::trunc);
  if (!fs.is_open()) {
    std::cout << "error opening file to save" << std::endl;
    fs.close();
    return false;
  }
  if (!writeLabels(fs, bboxes)) {
    std::cout << "error write file to save" << std::endl;
    fs.close();
    return false;
  }
  fs.close();
  return true;
}
bool Files::readLabels(std::ifstream &fs, std::vector<BoundingBox> &labels) {
  try {
    json j;
    fs >> j;
    std::cout << j << std::endl;
    for (json ele : j["bboxes"]) {
      std::cout << ele << std::endl;
      json points = ele["points"];
      std::vector<QPointF> pointVec;
      for (json point : points) {
        pointVec.push_back(
            QPointF(point["x"].get<float>(), point["y"].get<float>()));
      }
      labels.push_back(BoundingBox{
          QRect(QPoint(ele["rect"]["x"].get<float>(),
                       ele["rect"]["y"].get<float>()),
                QPoint(ele["rect"]["x"].get<float>() +
                           ele["rect"]["width"].get<float>(),
                       ele["rect"]["y"].get<float>() +
                           ele["rect"]["height"].get<float>())),
          pointVec,
          ele["className"],
          ele["imgPath"],
          ele["occluded"],
          ele["shape"],
      });
    }
  } catch (std::exception &err) {
    std::cout << err.what() << std::endl;
    return false;
  }
  return true;
}
bool Files::writeLabels(std::ofstream &fs, std::vector<BoundingBox> bboxes) {
  try {
    json j;
    for (BoundingBox bb : bboxes) {
      json box;
      box["rect"]["x"] = bb.rect.x();
      box["rect"]["y"] = bb.rect.x();
      box["rect"]["width"] = bb.rect.width();
      box["rect"]["height"] = bb.rect.height();
      box["shape"] = bb.shape;
      for (QPointF point : bb.points) {
        json jp;
        jp["x"] = point.x();
        jp["y"] = point.y();
        box["points"].push_back(jp);
      }
      box["imgPath"] = bb.imgPath;
      box["occluded"] = bb.occluded;
      box["className"] = bb.classname;
      j["bboxes"].push_back(box);
    }
    fs << j;
  } catch (std::exception err) {
    return false;
  }
  return true;
}
