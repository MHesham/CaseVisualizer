/********************************************************************************
** Form generated from reading UI file 'ChoosePlanStepDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEPLANSTEPDIALOG_H
#define UI_CHOOSEPLANSTEPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChoosePlanStepDialogClass
{
public:
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QComboBox *comboBox;
    QLabel *lblPlanStepType;

    void setupUi(QDialog *ChoosePlanStepDialogClass)
    {
        if (ChoosePlanStepDialogClass->objectName().isEmpty())
            ChoosePlanStepDialogClass->setObjectName(QStringLiteral("ChoosePlanStepDialogClass"));
        ChoosePlanStepDialogClass->resize(201, 73);
        btnOK = new QPushButton(ChoosePlanStepDialogClass);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(10, 40, 91, 25));
        btnCancel = new QPushButton(ChoosePlanStepDialogClass);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(110, 40, 81, 25));
        comboBox = new QComboBox(ChoosePlanStepDialogClass);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(10, 10, 141, 20));
        comboBox->setFocusPolicy(Qt::WheelFocus);
        lblPlanStepType = new QLabel(ChoosePlanStepDialogClass);
        lblPlanStepType->setObjectName(QStringLiteral("lblPlanStepType"));
        lblPlanStepType->setGeometry(QRect(160, 10, 31, 20));

        retranslateUi(ChoosePlanStepDialogClass);

        QMetaObject::connectSlotsByName(ChoosePlanStepDialogClass);
    } // setupUi

    void retranslateUi(QDialog *ChoosePlanStepDialogClass)
    {
        ChoosePlanStepDialogClass->setWindowTitle(QApplication::translate("ChoosePlanStepDialogClass", "ChoosePlanStepDialog", 0));
        btnOK->setText(QApplication::translate("ChoosePlanStepDialogClass", "OK", 0));
        btnCancel->setText(QApplication::translate("ChoosePlanStepDialogClass", "Cancel", 0));
        lblPlanStepType->setText(QApplication::translate("ChoosePlanStepDialogClass", "Type", 0));
    } // retranslateUi

};

namespace Ui {
    class ChoosePlanStepDialogClass: public Ui_ChoosePlanStepDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEPLANSTEPDIALOG_H
