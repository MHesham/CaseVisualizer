#ifndef PLANGRAPHVIEW_H
#define PLANGRAPHVIEW_H

#include <QWidget>
#include <hash_map>
#include <string>
using namespace std;
using namespace stdext;
#include "ui_PlanGraphView.h"
#ifndef CROSSMAP_H
#include "CrossMap.h"
#endif

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
        ~PlanGraphView();

        void View(GoalEx* p_caseGoal, PlanGraph* p_planGraph);
        void SetMode(int p_mode);

    private:
        Ui::PlanGraphViewClass ui;
        QGraphicsView* m_graphicsView; 
        GraphScene* m_scene;
        PlanStepView* m_planStepView;

        private slots:
            void HandleNodeSelected(GraphNodeView* p_node);
    };
}

#endif // PLANGRAPHVIEW_H
