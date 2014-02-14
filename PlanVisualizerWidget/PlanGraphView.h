#ifndef PLANGRAPHVIEW_H
#define PLANGRAPHVIEW_H

#include <QWidget>
#include <hash_map>
#include <string>
#include "ui_PlanGraphView.h"
#include "CrossMap.h"
#include "GraphScene.h"
#include "MessagePump.h"

class QGraphicsView;

namespace IStrategizer
{
    class PlanGraph;
    class GraphScene;
    class PlanStepView;
    class GraphNodeView;
    class GoalEx;

    const int GraphUpdateIntervalMs = 500;

    class PlanGraphView : public QWidget
    {
        Q_OBJECT

    public:
        PlanGraphView(GraphScene* pScene, CrossMap<unsigned, std::string>* pIdLookup, QWidget *pParent = 0);
        
        void View(IOlcbpPlanDigraph* pPlanGraph);
        void SetMode(GraphScene::PointerMode mode);
        void OnPlanStructureChange();

    protected:
        void timerEvent(QTimerEvent *pEvt);

    private:
        Ui::PlanGraphViewClass m_ui;
        QGraphicsView* m_pGraphicsView;        
        GraphScene* m_pScene;
        PlanStepView* m_pPlanStepView;
        int m_updateTimerId;

        private slots:
            void HandleNodeSelected(GraphNodeView* pNode);
    };
}

#endif // PLANGRAPHVIEW_H
