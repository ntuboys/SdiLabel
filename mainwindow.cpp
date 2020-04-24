#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  display = new ImageDisplay;
  project = new Files;
  settings = new QSettings("label", "label");
  ui->main->addWidget(display);
  currentImage = display->getImageLabel();
  QVariantMap options;
  options.insert("scale-factor", 1);
  resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
  connect(ui->actionOpen_Class_File, SIGNAL(triggered(bool)), this,
          SLOT(openClasses()));
  connect(ui->actionOpen_Annotations, SIGNAL(triggered(bool)), this,
          SLOT(openLabels()));
  connect(ui->actionSave_Class_File, SIGNAL(triggered(bool)), this,
          SLOT(saveClasses()));
  connect(ui->actionSave_Annotations, SIGNAL(triggered(bool)), this,
          SLOT(saveLabels()));
  connect(ui->actionOpen_Images_Folder, SIGNAL(triggered(bool)), this,
          SLOT(openImagesFolder()));
  connect(ui->classesComboBox, SIGNAL(currentIndexChanged(QString)), this,
          SLOT(setCurrentClass(QString)));
  connect(ui->addClass, SIGNAL(clicked(bool)), this, SLOT(addClass()));
  connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(onListWidgetItemClicked(QListWidgetItem *)));
  connect(ui->select, SIGNAL(clicked(bool)), this, SLOT(setSelectMode()));
  connect(ui->draw, SIGNAL(clicked(bool)), this, SLOT(setDrawMode()));
  connect(ui->rect, SIGNAL(clicked(bool)), this, SLOT(setShapeRect()));
  connect(ui->ellip, SIGNAL(clicked(bool)), this, SLOT(setShapeEllip()));
  connect(ui->tri, SIGNAL(clicked(bool)), this, SLOT(setShapeTri()));
  connect(ui->octa, SIGNAL(clicked(bool)), this, SLOT(setShapeOcta()));
  connect(ui->pent, SIGNAL(clicked(bool)), this, SLOT(setShapePent()));
  connect(currentImage, SIGNAL(newLabel(BoundingBox)), this,
          SLOT(addLabel(BoundingBox)));
  connect(currentImage, SIGNAL(removeLabel(BoundingBox)), this,
          SLOT(removeLabel(BoundingBox)));
  connect(currentImage, SIGNAL(updateLabel(BoundingBox, BoundingBox)), this,
          SLOT(updateLabel(BoundingBox, BoundingBox)));
  connect(currentImage, SIGNAL(setCurrentClass(QString)), this,
          SLOT(setCurrentClass(QString)));
  connect(display, SIGNAL(image_loaded()), this, SLOT(updateImageInfo()));
  connect(this, SIGNAL(selectedClass(QString)), currentImage,
          SLOT(setClassname(QString)));
}
void MainWindow::openImagesFolder() {
  QFileDialog fd(this);
  QString imageFolderDir = fd.getExistingDirectory(this, ("Open Folder"));
  std::vector<ImagesPanelItem> images;
  QDirIterator dirIt(imageFolderDir);
  while (dirIt.hasNext()) {
    ImagesPanelItem newItem;
    dirIt.next();
    if ((QFileInfo(dirIt.filePath()).suffix() == "png") || (QFileInfo(dirIt.filePath()).suffix() == "jpg")) {
      newItem.name = dirIt.fileName();
      newItem.imageDir = dirIt.filePath();
      images.push_back(newItem);
    }
  }
  ui->listWidget->clear();
  for (ImagesPanelItem item : images) {
    QListWidgetItem *img = new QListWidgetItem(QIcon(item.imageDir), item.name);
    ui->listWidget->addItem(img);
  }
  settings->setValue("imagesFolder", imageFolderDir);
}
void MainWindow::openClasses() {
  QFileDialog fd(this);
  fd.setFileMode(QFileDialog::AnyFile);
  // fd.setDefaultSuffix(".classes");
  QString classFileDir = fd.getSaveFileName(
      this, tr("Open Classes File") /*, "", tr("Classes (.classes)")*/);
  QFile fs(classFileDir);
  if (fs.exists()) {
    if (fs.open(QIODevice::ReadOnly)) {
      if (!classes.empty()) {
        classes.clear();
      }
      QTextStream in(&fs);
      while (!in.atEnd()) {
        classes.add(in.readLine().toStdString());
      }
      fs.close();
    }
  } else {
    fs.open(QIODevice::ReadWrite);
    fs.close();
  }
  updateClassList();
  settings->setValue("classFile", classFileDir);
}
void MainWindow::saveClasses() {
  std::ofstream fs(settings->value("classFile").toString().toStdString(),
                   std::ofstream::trunc | std::ofstream::out);
  if (fs.is_open()) {
    for (std::string c : *classes.getAll()) {
      fs << c << '\n';
    }
  }
}
void MainWindow::openLabels() {
  QFileDialog fd(this);
  // fd.setDefaultSuffix(".annotations");
  fd.setFileMode(QFileDialog::AnyFile);
  QString labelsFileDir = fd.getSaveFileName(
      this,
      tr("Open Annotations File") /*, "", tr("Annotations (.annotations)")*/);
  QFile fs(labelsFileDir);
  if (fs.exists(labelsFileDir)) {
    if (!project->loadLabels(labelsFileDir.toStdString(), bboxes)) {
      QMessageBox::warning(this, tr("Error opening labels"),
                           tr("labels file could not be opeend"));
      return;
    }
  } else {
    fs.open(QIODevice::ReadWrite);
    fs.close();
  }
  settings->setValue("labelsFile", labelsFileDir);
  updateLabels();
}
void MainWindow::saveLabels() {
  std::string file =
      settings->value("labelsFile", QDir::homePath()).toString().toStdString();
  if (project->saveLabels(file, bboxes)) {

  } else {

  }
}
// ui->rect->setEnabled(false);
// ui->ellip->setEnabled(false);
// ui->poly->setEnabled(false);
// ui->tri->setEnabled(false);
// ui->octa->setEnabled(false);
// ui->pent->setEnabled(false);
void MainWindow::setShapeTri() {
  myShape shape = TRIANGLE;
  currentImage->setShape(shape);
  ui->rect->setEnabled(true);
  ui->ellip->setEnabled(true);
  ui->tri->setEnabled(false);
  ui->octa->setEnabled(true);
  ui->pent->setEnabled(true);
}
void MainWindow::setShapePent() {
  myShape shape = PENTAGON;
  currentImage->setShape(shape);
  ui->rect->setEnabled(true);
  ui->ellip->setEnabled(true);
  ui->tri->setEnabled(true);
  ui->octa->setEnabled(true);
  ui->pent->setEnabled(false);
}
void MainWindow::setShapeOcta() {
  myShape shape = OCTAGON;
  currentImage->setShape(shape);
  ui->rect->setEnabled(true);
  ui->ellip->setEnabled(true);
  ui->tri->setEnabled(true);
  ui->octa->setEnabled(false);
  ui->pent->setEnabled(true);
}
void MainWindow::setShapeRect() {
  myShape shape = RECTANGLE;
  currentImage->setShape(shape);
  ui->rect->setEnabled(false);
  ui->ellip->setEnabled(true);
  ui->tri->setEnabled(true);
  ui->octa->setEnabled(true);
  ui->pent->setEnabled(true);
}
void MainWindow::setShapeEllip() {
  myShape shape = ELLIPSE;
  currentImage->setShape(shape);
  ui->rect->setEnabled(true);
  ui->ellip->setEnabled(false);
  ui->tri->setEnabled(true);
  ui->octa->setEnabled(true);
  ui->pent->setEnabled(true);
}
void MainWindow::onListWidgetItemClicked(QListWidgetItem *i) {
    QString path = settings->value("imagesFolder", "").toString() + '\\' + i->data(0).toString();
  currentImagepath = path;
  currentImage->setDir(currentImagepath.toStdString());
  updateDisplay();
}
void MainWindow::setCurrentClass(const QString &name) {
  if (ui->classesComboBox->currentText() != name) {
    ui->classesComboBox->setCurrentText(name);
  }
  current_class = name;
  emit selectedClass(current_class);
}
void MainWindow::setDrawMode() {
  ui->draw->setEnabled(false);
  ui->select->setEnabled(true);
  currentImage->setDrawMode();
}
void MainWindow::setSelectMode() {
  ui->draw->setEnabled(true);
  ui->select->setEnabled(false);
  currentImage->setSelectMode();
}
bool MainWindow::loadClasses() {
  QFile cFile(settings->value("project_folder").toString() + "/.classes");
  if (cFile.open(QIODevice::ReadOnly)) {
    if (!classes.empty()) {
      classes.clear();
    }
    QTextStream in(&cFile);
    while (!in.atEnd()) {
      classes.add(in.readLine().toStdString());
    }
    cFile.close();
    return true;
  } else {
    QMessageBox::warning(this, tr("Error loading classes file"),
                         tr("class filed could not be loaded"));
    return false;
  }
}
void MainWindow::updateLabels() {
  // project->getLabels(currentImagepath, bboxes);
  std::vector<BoundingBox> temp;
  for (BoundingBox bb : bboxes) {
    if (bb.imgPath == currentImagepath.toStdString()) {
      temp.push_back(bb);
    }
  }
  currentImage->setBoundingBoxes(temp);
}
void MainWindow::updateClassList() {
  // loadClasses();
  ui->classesComboBox->clear();
  std::string classname;
  foreach (classname, *classes.getAll()) {
    if (classname != "")
      ui->classesComboBox->addItem(QString::fromUtf8(classname.c_str()));
  }
  if (!classes.empty()) {
    ui->classesComboBox->setEnabled(true);
    ui->removeClass->setEnabled(true);
    ui->classesComboBox->setCurrentIndex(0);
  } else {
    ui->classesComboBox->setDisabled(true);
    ui->removeClass->setDisabled(true);
  }
}
void MainWindow::addClass() {
  QString new_class = ui->newClassText->text();
  if (new_class.simplified() != "" && (classes.find(new_class.toStdString()) == -1)) {
    classes.add(new_class.simplified().toStdString());
    ui->newClassText->clear();
    updateClassList();
    setCurrentClass(new_class.simplified());
  }
}
void MainWindow::addLabel(const BoundingBox &bbox) {
  // project->addLabel(currentImagepath, bbox);
  if (bbox.classname != "")
    bboxes.push_back(bbox);
  updateLabels();
}
void MainWindow::removeLabel(const BoundingBox &bbox) {
  // project->removeLabel(currentImagepath, bbox);
  if (!bboxes.empty())
    for (int i = 0; i < bboxes.size(); i++) {
      BoundingBox box = bboxes[i];
      if (bbox.rect == box.rect && bbox.classname == box.classname) {
        bboxes.erase(bboxes.begin() + i);
        break;
      }
    }
  updateLabels();
}
void MainWindow::removeImageLabels() {
  if (QMessageBox::Yes ==
      QMessageBox::question(this, tr("rem all labels"), QString("you sure?"))) {
    ;
    // project->removeLabels(currentImagepath);
    bboxes.clear();
    updateLabels();
    updateDisplay();
  }
}
void MainWindow::updateLabel(const BoundingBox &old_bbox,
                             const BoundingBox &new_bbox) {
  // project->removeLabel(currentImagepath, old_bbox);
  // project->addLabel(currentImagepath, new_bbox);
  removeLabel(old_bbox);
  addLabel(new_bbox);
  updateLabels();
}
void MainWindow::initDisplay() {
  display->clearPixmap();
  // update image list
  updateClassList();
  current_index = 0;
  updateDisplay();
}
void MainWindow::updateCurrentIndex(int index) {
  current_index = index;
  updateDisplay();
}
void MainWindow::updateDisplay() {
  display->setImagePath(currentImagepath);
  updateLabels();
}
MainWindow::~MainWindow() {
  delete project;
  delete ui;
}
