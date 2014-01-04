/********************************************************************************
** Form generated from reading UI file 'PlanStepView.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANSTEPVIEW_H
#define UI_PLANSTEPVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlanStepViewClass
{
public:
    QToolBox *toolBox;
    QWidget *Parameters;
    QTableWidget *tblParameters;
    QWidget *Conditions;
    QLabel *lblPlanStep;

    void setupUi(QWidget *PlanStepViewClass)
    {
        if (PlanStepViewClass->objectName().isEmpty())
            PlanStepViewClass->setObjectName(QStringLiteral("PlanStepViewClass"));
        PlanStepViewClass->resize(260, 450);
        toolBox = new QToolBox(PlanStepViewClass);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(10, 30, 241, 411));
        toolBox->setLayoutDirection(Qt::LeftToRight);
        Parameters = new QWidget();
        Parameters->setObjectName(QStringLiteral("Parameters"));
        Parameters->setGeometry(QRect(0, 0, 241, 349));
        tblParameters = new QTableWidget(Parameters);
        tblParameters->setObjectName(QStringLiteral("tblParameters"));
        tblParameters->setGeometry(QRect(10, 10, 221, 331));
        QFont font;
        font.setFamily(QStringLiteral("Tahoma"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        tblParameters->setFont(font);
        tblParameters->setLayoutDirection(Qt::LeftToRight);
        tblParameters->setFrameShape(QFrame::StyledPanel);
        tblParameters->setFrameShadow(QFrame::Plain);
        tblParameters->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblParameters->setSelectionMode(QAbstractItemView::SingleSelection);
        tblParameters->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblParameters->setShowGrid(false);
        tblParameters->setGridStyle(Qt::NoPen);
        tblParameters->setCornerButtonEnabled(false);
        toolBox->addItem(Parameters, QStringLiteral("Parameters"));
        Conditions = new QWidget();
        Conditions->setObjectName(QStringLiteral("Conditions"));
        Conditions->setGeometry(QRect(0, 0, 98, 28));
        toolBox->addItem(Conditions, QStringLiteral("Conditions"));
        lblPlanStep = new QLabel(PlanStepViewClass);
        lblPlanStep->setObjectName(QStringLiteral("lblPlanStep"));
        lblPlanStep->setGeometry(QRect(10, 0, 241, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Tahoma"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        lblPlanStep->setFont(font1);
        lblPlanStep->setMargin(4);
        lblPlanStep->setIndent(0);

        retranslateUi(PlanStepViewClass);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PlanStepViewClass);
    } // setupUi

    void retranslateUi(QWidget *PlanStepViewClass)
    {
        PlanStepViewClass->setWindowTitle(QApplication::translate("PlanStepViewClass", "PlanStepView", 0));
        toolBox->setItemText(toolBox->indexOf(Parameters), QApplication::translate("PlanStepViewClass", "Parameters", 0));
        toolBox->setItemText(toolBox->indexOf(Conditions), QApplication::translate("PlanStepViewClass", "Conditions", 0));
        lblPlanStep->setText(QApplication::translate("PlanStepViewClass", "Plan Step Name", 0));
    } // retranslateUi

};

namespace Ui {
    class PlanStepViewClass: public Ui_PlanStepViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANSTEPVIEW_H
