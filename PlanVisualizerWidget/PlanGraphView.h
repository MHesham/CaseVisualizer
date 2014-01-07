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

    class PlanGraphView : public QWidget
    {
        Q_OBJECT

    public:
        PlanGraphView(GraphScene* p_scene, CrossMap<unsigned, std::string>* p_idLookup, QWidget *p_parent = 0);
        
        void View(IPlanDigraph* pPlanGraph);
        void SetMode(int p_mode);
        void OnPlanStructureChange();

    private:
        Ui::PlanGraphViewClass    ui;
        QGraphicsView*            m_graphicsView;        
        GraphScene*                m_scene;
        PlanStepView*            m_planStepView;

        private slots:
            void HandleNodeSelected(GraphNodeView* p_node);
    };
}

#endif // PLANGRAPHVIEW_H
