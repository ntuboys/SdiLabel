/********************************************************************************
** Form generated from reading UI file 'imagedisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#ifndef UI_IMAGEDISPLAY_H
#define UI_IMAGEDISPLAY_H
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
QT_BEGIN_NAMESPACE
class Ui_ImageDisplay {
public:
  QVBoxLayout *verticalLayout_2;
  QVBoxLayout *main;
  QHBoxLayout *horizontalLayout;
  QCheckBox *btnAutoFit;
  QSpinBox *spnZoom;
  void setupUi(QWidget *ImageDisplay) {
    if (ImageDisplay->objectName().isEmpty())
      ImageDisplay->setObjectName(QStringLiteral("ImageDisplay"));
    ImageDisplay->resize(400, 300);
    verticalLayout_2 = new QVBoxLayout(ImageDisplay);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
    main = new QVBoxLayout();
    main->setObjectName(QStringLiteral("main"));
    verticalLayout_2->addLayout(main);
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    btnAutoFit = new QCheckBox(ImageDisplay);
    btnAutoFit->setObjectName(QStringLiteral("btnAutoFit"));
    horizontalLayout->addWidget(btnAutoFit);
    spnZoom = new QSpinBox(ImageDisplay);
    spnZoom->setObjectName(QStringLiteral("spnZoom"));
    spnZoom->setMinimum(25);
    spnZoom->setMaximum(300);
    spnZoom->setSingleStep(25);
    spnZoom->setValue(100);
    horizontalLayout->addWidget(spnZoom);

    verticalLayout_2->addLayout(horizontalLayout);

    retranslateUi(ImageDisplay);
    QMetaObject::connectSlotsByName(ImageDisplay);
  } // setupUi
  void retranslateUi(QWidget *ImageDisplay) {
    ImageDisplay->setWindowTitle(
        QApplication::translate("ImageDisplay", "Form", Q_NULLPTR));
    btnAutoFit->setText(
        QApplication::translate("ImageDisplay", "Auto fit", Q_NULLPTR));
    spnZoom->setSuffix(QApplication::translate("ImageDisplay", "%", Q_NULLPTR));
  } // retranslateUi
};
namespace Ui {
class ImageDisplay : public Ui_ImageDisplay {};
} // namespace Ui
QT_END_NAMESPACE
#endif // UI_IMAGEDISPLAY_H
