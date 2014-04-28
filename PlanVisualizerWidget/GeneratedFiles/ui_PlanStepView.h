/********************************************************************************
** Form generated from reading UI file 'PlanStepView.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANSTEPVIEW_H
#define UI_PLANSTEPVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlanStepViewClass
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_7;
    QLabel *lblPlanStep;
    QToolBox *toolBox;
    QWidget *Parameters;
    QGridLayout *gridLayout_3;
    QGridLayout *paramsGridLayout;
    QTableWidget *tblParameters;
    QWidget *Preformance;
    QGridLayout *gridLayout_6;
    QFormLayout *formLayout;
    QLabel *lblFailureProbability;
    QLineEdit *txtFailureProbability;
    QLabel *lblVulnerableCondition;
    QLineEdit *txtVulnerableCondition;
    QWidget *Conditions;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;

    void setupUi(QWidget *PlanStepViewClass)
    {
        if (PlanStepViewClass->objectName().isEmpty())
            PlanStepViewClass->setObjectName(QStringLiteral("PlanStepViewClass"));
        PlanStepViewClass->resize(365, 217);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PlanStepViewClass->sizePolicy().hasHeightForWidth());
        PlanStepViewClass->setSizePolicy(sizePolicy);
        PlanStepViewClass->setMinimumSize(QSize(365, 0));
        gridLayout = new QGridLayout(PlanStepViewClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setSizeConstraint(QLayout::SetDefaultConstraint);
        lblPlanStep = new QLabel(PlanStepViewClass);
        lblPlanStep->setObjectName(QStringLiteral("lblPlanStep"));
        QFont font;
        font.setFamily(QStringLiteral("Tahoma"));
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        lblPlanStep->setFont(font);
        lblPlanStep->setMargin(4);
        lblPlanStep->setIndent(0);

        gridLayout_7->addWidget(lblPlanStep, 0, 0, 1, 1);

        toolBox = new QToolBox(PlanStepViewClass);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolBox->sizePolicy().hasHeightForWidth());
        toolBox->setSizePolicy(sizePolicy1);
        toolBox->setLayoutDirection(Qt::LeftToRight);
        Parameters = new QWidget();
        Parameters->setObjectName(QStringLiteral("Parameters"));
        Parameters->setGeometry(QRect(0, 0, 320, 111));
        sizePolicy1.setHeightForWidth(Parameters->sizePolicy().hasHeightForWidth());
        Parameters->setSizePolicy(sizePolicy1);
        gridLayout_3 = new QGridLayout(Parameters);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        paramsGridLayout = new QGridLayout();
        paramsGridLayout->setSpacing(0);
        paramsGridLayout->setObjectName(QStringLiteral("paramsGridLayout"));
        paramsGridLayout->setContentsMargins(0, 0, 0, 0);
        tblParameters = new QTableWidget(Parameters);
        tblParameters->setObjectName(QStringLiteral("tblParameters"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tblParameters->sizePolicy().hasHeightForWidth());
        tblParameters->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamily(QStringLiteral("Tahoma"));
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        tblParameters->setFont(font1);
        tblParameters->setLayoutDirection(Qt::LeftToRight);
        tblParameters->setFrameShape(QFrame::StyledPanel);
        tblParameters->setFrameShadow(QFrame::Plain);
        tblParameters->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblParameters->setSelectionMode(QAbstractItemView::SingleSelection);
        tblParameters->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblParameters->setShowGrid(false);
        tblParameters->setGridStyle(Qt::NoPen);
        tblParameters->setCornerButtonEnabled(false);

        paramsGridLayout->addWidget(tblParameters, 0, 0, 1, 1);


        gridLayout_3->addLayout(paramsGridLayout, 0, 0, 1, 1);

        toolBox->addItem(Parameters, QStringLiteral("Parameters"));
        Preformance = new QWidget();
        Preformance->setObjectName(QStringLiteral("Preformance"));
        Preformance->setGeometry(QRect(0, 0, 341, 85));
        sizePolicy1.setHeightForWidth(Preformance->sizePolicy().hasHeightForWidth());
        Preformance->setSizePolicy(sizePolicy1);
        gridLayout_6 = new QGridLayout(Preformance);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        lblFailureProbability = new QLabel(Preformance);
        lblFailureProbability->setObjectName(QStringLiteral("lblFailureProbability"));
        sizePolicy.setHeightForWidth(lblFailureProbability->sizePolicy().hasHeightForWidth());
        lblFailureProbability->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::LabelRole, lblFailureProbability);

        txtFailureProbability = new QLineEdit(Preformance);
        txtFailureProbability->setObjectName(QStringLiteral("txtFailureProbability"));
        sizePolicy.setHeightForWidth(txtFailureProbability->sizePolicy().hasHeightForWidth());
        txtFailureProbability->setSizePolicy(sizePolicy);
        txtFailureProbability->setInputMask(QStringLiteral("9999999999"));
        txtFailureProbability->setText(QStringLiteral(""));
        txtFailureProbability->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, txtFailureProbability);

        lblVulnerableCondition = new QLabel(Preformance);
        lblVulnerableCondition->setObjectName(QStringLiteral("lblVulnerableCondition"));
        sizePolicy.setHeightForWidth(lblVulnerableCondition->sizePolicy().hasHeightForWidth());
        lblVulnerableCondition->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::LabelRole, lblVulnerableCondition);

        txtVulnerableCondition = new QLineEdit(Preformance);
        txtVulnerableCondition->setObjectName(QStringLiteral("txtVulnerableCondition"));
        sizePolicy.setHeightForWidth(txtVulnerableCondition->sizePolicy().hasHeightForWidth());
        txtVulnerableCondition->setSizePolicy(sizePolicy);
        txtVulnerableCondition->setInputMask(QStringLiteral(""));
        txtVulnerableCondition->setText(QStringLiteral(""));
        txtVulnerableCondition->setReadOnly(false);

        formLayout->setWidget(1, QFormLayout::FieldRole, txtVulnerableCondition);


        gridLayout_6->addLayout(formLayout, 0, 0, 1, 1);

        toolBox->addItem(Preformance, QStringLiteral("Performance"));
        Conditions = new QWidget();
        Conditions->setObjectName(QStringLiteral("Conditions"));
        Conditions->setGeometry(QRect(0, 0, 98, 28));
        sizePolicy1.setHeightForWidth(Conditions->sizePolicy().hasHeightForWidth());
        Conditions->setSizePolicy(sizePolicy1);
        gridLayout_5 = new QGridLayout(Conditions);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));

        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        toolBox->addItem(Conditions, QStringLiteral("Conditions"));

        gridLayout_7->addWidget(toolBox, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_7, 0, 0, 1, 1);


        retranslateUi(PlanStepViewClass);

        toolBox->setCurrentIndex(0);
        toolBox->layout()->setSpacing(0);


        QMetaObject::connectSlotsByName(PlanStepViewClass);
    } // setupUi

    void retranslateUi(QWidget *PlanStepViewClass)
    {
        PlanStepViewClass->setWindowTitle(QApplication::translate("PlanStepViewClass", "PlanStepView", 0));
        lblPlanStep->setText(QApplication::translate("PlanStepViewClass", "Plan Step Name", 0));
        toolBox->setItemText(toolBox->indexOf(Parameters), QApplication::translate("PlanStepViewClass", "Parameters", 0));
        lblFailureProbability->setText(QApplication::translate("PlanStepViewClass", "Failure Probability", 0));
        lblVulnerableCondition->setText(QApplication::translate("PlanStepViewClass", "Vulnerable Condition", 0));
        toolBox->setItemText(toolBox->indexOf(Preformance), QApplication::translate("PlanStepViewClass", "Performance", 0));
        toolBox->setItemText(toolBox->indexOf(Conditions), QApplication::translate("PlanStepViewClass", "Conditions", 0));
    } // retranslateUi

};

namespace Ui {
    class PlanStepViewClass: public Ui_PlanStepViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANSTEPVIEW_H
