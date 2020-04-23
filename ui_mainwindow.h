/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
QT_BEGIN_NAMESPACE
class Ui_MainWindow {
public:
  QAction *actionSave_Annotations;
  QAction *actionSave_Class_File;
  QAction *actionOpen_Annotations;
  QAction *actionOpen_Class_File;
  QAction *actionOpen_Images_Folder;
  QWidget *centralwidget;
  QHBoxLayout *horizontalLayout_6;
  QVBoxLayout *tools;
  QVBoxLayout *modes;
  QPushButton *select;
  QPushButton *draw;
  QGridLayout *shapes;
  QPushButton *ellip;
  QPushButton *tri;
  QPushButton *pent;
  QPushButton *octa;
  QPushButton *rect;
  QVBoxLayout *main;
  QVBoxLayout *browser;
  QGridLayout *images;
  QListWidget *listWidget;
  QGridLayout *classes;
  QPushButton *addClass;
  QComboBox *classesComboBox;
  QLineEdit *newClassText;
  QPushButton *removeClass;
  QMenuBar *menubar;
  QMenu *menuFile;
  QStatusBar *statusbar;
  void setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName(QStringLiteral("MainWindow"));
    MainWindow->resize(828, 621);
    actionSave_Annotations = new QAction(MainWindow);
    actionSave_Annotations->setObjectName(
        QStringLiteral("actionSave_Annotations"));
    actionSave_Class_File = new QAction(MainWindow);
    actionSave_Class_File->setObjectName(
        QStringLiteral("actionSave_Class_File"));
    actionOpen_Annotations = new QAction(MainWindow);
    actionOpen_Annotations->setObjectName(
        QStringLiteral("actionOpen_Annotations"));
    actionOpen_Class_File = new QAction(MainWindow);
    actionOpen_Class_File->setObjectName(
        QStringLiteral("actionOpen_Class_File"));
    actionOpen_Images_Folder = new QAction(MainWindow);
    actionOpen_Images_Folder->setObjectName(
        QStringLiteral("actionOpen_Images_Folder"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QStringLiteral("centralwidget"));
    horizontalLayout_6 = new QHBoxLayout(centralwidget);
    horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
    tools = new QVBoxLayout();
    tools->setObjectName(QStringLiteral("tools"));
    modes = new QVBoxLayout();
    modes->setObjectName(QStringLiteral("modes"));
    select = new QPushButton(centralwidget);
    select->setObjectName(QStringLiteral("select"));
    modes->addWidget(select);
    draw = new QPushButton(centralwidget);
    draw->setObjectName(QStringLiteral("draw"));
    modes->addWidget(draw);

    tools->addLayout(modes);
    shapes = new QGridLayout();
    shapes->setObjectName(QStringLiteral("shapes"));
    ellip = new QPushButton(centralwidget);
    ellip->setObjectName(QStringLiteral("ellip"));
    shapes->addWidget(ellip, 1, 0, 1, 1);
    tri = new QPushButton(centralwidget);
    tri->setObjectName(QStringLiteral("tri"));
    shapes->addWidget(tri, 2, 0, 1, 1);
    pent = new QPushButton(centralwidget);
    pent->setObjectName(QStringLiteral("pent"));
    shapes->addWidget(pent, 3, 0, 1, 1);
    octa = new QPushButton(centralwidget);
    octa->setObjectName(QStringLiteral("octa"));
    shapes->addWidget(octa, 4, 0, 1, 1);
    rect = new QPushButton(centralwidget);
    rect->setObjectName(QStringLiteral("rect"));
    shapes->addWidget(rect, 0, 0, 1, 1);

    tools->addLayout(shapes);

    horizontalLayout_6->addLayout(tools);
    main = new QVBoxLayout();
    main->setObjectName(QStringLiteral("main"));
    horizontalLayout_6->addLayout(main);
    browser = new QVBoxLayout();
    browser->setObjectName(QStringLiteral("browser"));
    images = new QGridLayout();
    images->setObjectName(QStringLiteral("images"));
    listWidget = new QListWidget(centralwidget);
    listWidget->setObjectName(QStringLiteral("listWidget"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
    listWidget->setSizePolicy(sizePolicy);
    listWidget->setViewMode(QListView::IconMode);
    images->addWidget(listWidget, 0, 0, 1, 1);

    browser->addLayout(images);
    classes = new QGridLayout();
    classes->setObjectName(QStringLiteral("classes"));
    addClass = new QPushButton(centralwidget);
    addClass->setObjectName(QStringLiteral("addClass"));
    classes->addWidget(addClass, 3, 0, 1, 1);
    classesComboBox = new QComboBox(centralwidget);
    classesComboBox->setObjectName(QStringLiteral("classesComboBox"));
    classes->addWidget(classesComboBox, 0, 0, 1, 1);
    newClassText = new QLineEdit(centralwidget);
    newClassText->setObjectName(QStringLiteral("newClassText"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(
        newClassText->sizePolicy().hasHeightForWidth());
    newClassText->setSizePolicy(sizePolicy1);
    classes->addWidget(newClassText, 2, 0, 1, 1);
    removeClass = new QPushButton(centralwidget);
    removeClass->setObjectName(QStringLiteral("removeClass"));
    classes->addWidget(removeClass, 1, 0, 1, 1);

    browser->addLayout(classes);

    horizontalLayout_6->addLayout(browser);
    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QStringLiteral("menubar"));
    menubar->setGeometry(QRect(0, 0, 828, 30));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QStringLiteral("menuFile"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QStringLiteral("statusbar"));
    MainWindow->setStatusBar(statusbar);
    menubar->addAction(menuFile->menuAction());
    menuFile->addAction(actionOpen_Images_Folder);
    menuFile->addAction(actionOpen_Annotations);
    menuFile->addAction(actionOpen_Class_File);
    menuFile->addAction(actionSave_Annotations);
    menuFile->addAction(actionSave_Class_File);
    retranslateUi(MainWindow);
    QMetaObject::connectSlotsByName(MainWindow);
  } // setupUi
  void retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(
        QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
    actionSave_Annotations->setText(
        QApplication::translate("MainWindow", "Save Annotations", Q_NULLPTR));
    actionSave_Class_File->setText(
        QApplication::translate("MainWindow", "Save Class File", Q_NULLPTR));
    actionOpen_Annotations->setText(
        QApplication::translate("MainWindow", "Open Annotations", Q_NULLPTR));
    actionOpen_Class_File->setText(
        QApplication::translate("MainWindow", "Open Class File", Q_NULLPTR));
    actionOpen_Images_Folder->setText(
        QApplication::translate("MainWindow", "Open Images Folder", Q_NULLPTR));
    select->setText(QApplication::translate("MainWindow", "Select", Q_NULLPTR));
    draw->setText(QApplication::translate("MainWindow", "Draw", Q_NULLPTR));
    ellip->setText(
        QApplication::translate("MainWindow", "Ellipsis", Q_NULLPTR));
    tri->setText(QApplication::translate("MainWindow", "Triangle", Q_NULLPTR));
    pent->setText(QApplication::translate("MainWindow", "Pentagon", Q_NULLPTR));
    octa->setText(QApplication::translate("MainWindow", "Octagon", Q_NULLPTR));
    rect->setText(QApplication::translate("MainWindow", "Rect", Q_NULLPTR));
    addClass->setText(
        QApplication::translate("MainWindow", "Add Class", Q_NULLPTR));
    newClassText->setText(
        QApplication::translate("MainWindow", "test", Q_NULLPTR));
    removeClass->setText(
        QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
    menuFile->setTitle(
        QApplication::translate("MainWindow", "File", Q_NULLPTR));
  } // retranslateUi
};
namespace Ui {
class MainWindow : public Ui_MainWindow {};
} // namespace Ui
QT_END_NAMESPACE
#endif // UI_MAINWINDOW_H
