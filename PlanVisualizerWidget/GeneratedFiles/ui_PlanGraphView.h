/********************************************************************************
** Form generated from reading UI file 'PlanGraphView.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANGRAPHVIEW_H
#define UI_PLANGRAPHVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlanGraphViewClass
{
public:
    QHBoxLayout *planGraphViewMainLayout;
    QHBoxLayout *planGraphViewInnerLayout;

    void setupUi(QWidget *PlanGraphViewClass)
    {
        if (PlanGraphViewClass->objectName().isEmpty())
            PlanGraphViewClass->setObjectName(QStringLiteral("PlanGraphViewClass"));
        PlanGraphViewClass->resize(805, 551);
        PlanGraphViewClass->setFocusPolicy(Qt::NoFocus);
        planGraphViewMainLayout = new QHBoxLayout(PlanGraphViewClass);
        planGraphViewMainLayout->setSpacing(6);
        planGraphViewMainLayout->setContentsMargins(11, 11, 11, 11);
        planGraphViewMainLayout->setObjectName(QStringLiteral("planGraphViewMainLayout"));
        planGraphViewInnerLayout = new QHBoxLayout();
        planGraphViewInnerLayout->setSpacing(6);
        planGraphViewInnerLayout->setObjectName(QStringLiteral("planGraphViewInnerLayout"));
        planGraphViewInnerLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

        planGraphViewMainLayout->addLayout(planGraphViewInnerLayout);


        retranslateUi(PlanGraphViewClass);

        QMetaObject::connectSlotsByName(PlanGraphViewClass);
    } // setupUi

    void retranslateUi(QWidget *PlanGraphViewClass)
    {
        PlanGraphViewClass->setWindowTitle(QApplication::translate("PlanGraphViewClass", "PlanGraphView", 0));
    } // retranslateUi

};

namespace Ui {
    class PlanGraphViewClass: public Ui_PlanGraphViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANGRAPHVIEW_H
