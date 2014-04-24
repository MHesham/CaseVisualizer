#include "stdafx.h"
#ifndef PLANGRAPHVIEW_H
#include "PlanGraphView.h"
#endif
#ifndef TOOLBOX_H
#include "Toolbox.h"
#endif
#ifndef GRAPHSCENE_H
#include "GraphScene.h"
#endif
#ifndef PLANSTEPVIEW_H
#include "PlanStepView.h"
#endif
#ifndef GRAPHNODEVIEW_H
#include "GraphNodeView.h"
#endif
#ifndef CROSSMAP_H
#include "CrossMap.h"
#endif


using namespace IStrategizer;
using namespace std;

PlanGraphView::PlanGraphView(GraphScene* p_scene, CrossMap<unsigned, string>* p_idLookup, QWidget *p_parent)
: QWidget(p_parent)
{
    m_ui.setupUi(this);
    
    QHBoxLayout* layout = new QHBoxLayout;
    m_pPlanStepView = new PlanStepView(p_idLookup);
    m_pGraphicsView = new QGraphicsView();
    m_pGraphicsView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_pScene = p_scene;
    m_pScene->setSceneRect(0, 0, 1000, 1000);

    m_pGraphicsView->setScene(m_pScene);
    m_pGraphicsView->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
    m_pGraphicsView->fitInView(m_pScene->sceneRect(), Qt::KeepAspectRatio);
    
    m_pGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    layout->setMargin(0);
    layout->addWidget(m_pGraphicsView);
    layout->addWidget(m_pPlanStepView);
    
    QRectF r1 = m_pPlanStepView->geometry();
    QRectF r2 = m_pGraphicsView->geometry();

    setLayout(layout);

    connect(m_pScene, SIGNAL(NodeSelected(GraphNodeView*)), SLOT(HandleNodeSelected(GraphNodeView*)));

    m_updateTimerId = startTimer(GraphUpdateIntervalMs);
}
//----------------------------------------------------------------------------------------------
void PlanGraphView::SetMode(GraphScene::PointerMode mode) 
{
    m_pScene->Mode((GraphScene::PointerMode)mode); 
}
//----------------------------------------------------------------------------------------------
void PlanGraphView::View(IOlcbpPlan* pPlanGraph)
{
    m_pScene->View(pPlanGraph);
}
//----------------------------------------------------------------------------------------------
void PlanGraphView::HandleNodeSelected(GraphNodeView* p_node)
{
    if(p_node == NULL)
        m_pPlanStepView->View(NULL);
    else
        m_pPlanStepView->View(p_node->NodeModel());
}
//----------------------------------------------------------------------------------------------
void PlanGraphView::OnPlanStructureChange()
{
    m_pScene->OnGraphStructureChange();
}
//----------------------------------------------------------------------------------------------
void PlanGraphView::timerEvent(QTimerEvent *pEvt)
{
    if (pEvt->timerId() == m_updateTimerId)
        m_pScene->OnGraphUpdate();
}
