/********************************************************************************
** Form generated from reading UI file 'ParameterEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETEREDIT_H
#define UI_PARAMETEREDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ParameterEditClass
{
public:
    QLabel *lblActualParamName;
    QLabel *lblParamValue;
    QLabel *lblParamName;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QLineEdit *lineEditParamValue;

    void setupUi(QDialog *ParameterEditClass)
    {
        if (ParameterEditClass->objectName().isEmpty())
            ParameterEditClass->setObjectName(QStringLiteral("ParameterEditClass"));
        ParameterEditClass->resize(170, 130);
        lblActualParamName = new QLabel(ParameterEditClass);
        lblActualParamName->setObjectName(QStringLiteral("lblActualParamName"));
        lblActualParamName->setGeometry(QRect(5, 27, 160, 16));
        lblActualParamName->setFrameShape(QFrame::StyledPanel);
        lblParamValue = new QLabel(ParameterEditClass);
        lblParamValue->setObjectName(QStringLiteral("lblParamValue"));
        lblParamValue->setGeometry(QRect(5, 49, 160, 16));
        QFont font;
        font.setFamily(QStringLiteral("Tahoma"));
        font.setPointSize(8);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        lblParamValue->setFont(font);
        lblParamName = new QLabel(ParameterEditClass);
        lblParamName->setObjectName(QStringLiteral("lblParamName"));
        lblParamName->setGeometry(QRect(5, 5, 160, 16));
        lblParamName->setFont(font);
        btnOK = new QPushButton(ParameterEditClass);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(10, 100, 71, 25));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        btnOK->setFont(font1);
        btnCancel = new QPushButton(ParameterEditClass);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(90, 100, 71, 25));
        btnCancel->setFont(font1);
        lineEditParamValue = new QLineEdit(ParameterEditClass);
        lineEditParamValue->setObjectName(QStringLiteral("lineEditParamValue"));
        lineEditParamValue->setGeometry(QRect(10, 70, 151, 22));

        retranslateUi(ParameterEditClass);

        QMetaObject::connectSlotsByName(ParameterEditClass);
    } // setupUi

    void retranslateUi(QDialog *ParameterEditClass)
    {
        ParameterEditClass->setWindowTitle(QApplication::translate("ParameterEditClass", "ParameterEdit", 0));
        lblActualParamName->setText(QApplication::translate("ParameterEditClass", "Param Name", 0));
        lblParamValue->setText(QApplication::translate("ParameterEditClass", "Param Value", 0));
        lblParamName->setText(QApplication::translate("ParameterEditClass", "Param Name", 0));
        btnOK->setText(QApplication::translate("ParameterEditClass", "OK", 0));
        btnCancel->setText(QApplication::translate("ParameterEditClass", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class ParameterEditClass: public Ui_ParameterEditClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETEREDIT_H
