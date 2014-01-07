#include "stdafx.h"
#ifndef GRAPHSCENE_H
#include "GraphScene.h"
#endif
#ifndef PLANGRAPH_H
#include "PlanGraph.h"
#endif
#ifndef PLANSTEPEX_H
#include "PlanStepEx.h"
#endif
#ifndef GRAPHNODEVIEW_H
#include "GraphNodeView.h"
#endif
#ifndef GRAPHEDGEVIEW_H
#include "GraphEdgeView.h"
#endif
#ifndef GOALEX_H
#include "GoalEx.h"
#endif
#ifndef ACTION_H
#include "Action.h"
#endif
#ifndef CHOOSEPLANSTEPDIALOG_H
#include "ChoosePlanStepDialog.h"
#endif
#ifndef GOALFACTORY_H
#include "GoalFactory.h"
#endif
#ifndef ACTIONFACTORY_H
#include "ActionFactory.h"
#endif

#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QAction>
#include <QTimer>

using namespace IStrategizer;
using namespace Serialization;
using namespace std;

GraphScene::GraphScene(CrossMap<unsigned, string>* p_idLookup, QObject *p_parent) : QGraphicsScene(p_parent)
{
    m_horizontalNodeSpacing = DefaultHorizontalNodeSpacing;
    m_verticalNodeSpacing    = DefaultVerticalNodeSpacing;
    m_pNodeMenu                = nullptr;
    m_pPlanGraph            = nullptr;
    m_pChoosePlanStepDlg    = new ChoosePlanStepDialog(p_idLookup, true, true);
    m_mode                    = MODE_Move;
    m_pConnectionLine        = nullptr;
    m_pGraph                = nullptr;
    m_cellSize              = DefaultGridCellSize;

    connect(this, SIGNAL(selectionChanged()), SLOT(NodeSelected()));
    updateTimerId = startTimer(GraphRedrawIntervalMs);

    CreateMenus();
    CreateGrid();
}
//----------------------------------------------------------------------------------------------
void GraphScene::CreateMenus()
{
    CreateNodeMenu();
    CreateEdgeMenu();
    CreateSceneMenu();
}
//----------------------------------------------------------------------------------------------
void GraphScene::CreateNodeMenu()
{
    QAction *duplicateAction = new QAction(tr("Duplicate"), this);
    duplicateAction->setStatusTip(tr("Duplicates graph node"));
    connect(duplicateAction, SIGNAL(triggered()), this, SLOT(DuplicateNode()));

    QAction *deleteAction = new QAction(tr("Delete"), this);
    duplicateAction->setStatusTip(tr("Deletes graph node"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(DeleteNode()));

    QAction *disconnectAction = new QAction(tr("Disconnect"), this);
    disconnectAction->setStatusTip(tr("Disconnects the node from the graph"));
    connect(disconnectAction, SIGNAL(triggered()), this, SLOT(DisconnectNode()));

    m_pNodeMenu = new QMenu(tr("Node Menu"));
    m_pNodeMenu->setTearOffEnabled(true);
    m_pNodeMenu->addAction(deleteAction);
    m_pNodeMenu->addAction(duplicateAction);
    m_pNodeMenu->addAction(disconnectAction);
}
//----------------------------------------------------------------------------------------------
void GraphScene::CreateEdgeMenu()
{
    QAction *deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setStatusTip(tr("Deletes graph edge"));
    deleteAction->setShortcut(QString::fromLocal8Bit("D"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(DeleteEdge()));

    m_edgeMenu = new QMenu(tr("Edge Menu"));
    m_edgeMenu->setTearOffEnabled(true);
    m_edgeMenu->addAction(deleteAction);
}
//----------------------------------------------------------------------------------------------
void GraphScene::CreateSceneMenu()
{
    QAction *newNodeAction = new QAction(tr("N&ew Node"), this);
    newNodeAction->setStatusTip(tr("Creates new plan graph node"));
    connect(newNodeAction, SIGNAL(triggered()), this, SLOT(NewNode()));

    QAction *layoutGraph = new QAction(tr("L&ayout Plan"), this);
    layoutGraph->setStatusTip(tr("Layout plan graph in the scene"));
    connect(layoutGraph, SIGNAL(triggered()), this, SLOT(RedrawScene()));

    m_sceneMenu = new QMenu(tr("Scene Menu"));
    m_sceneMenu->setTearOffEnabled(true);
    m_sceneMenu->addAction(newNodeAction);
    m_sceneMenu->addAction(layoutGraph);
}
//----------------------------------------------------------------------------------------------
void GraphScene::View(IPlanDigraph* pPlan)
{
    m_pGraph = pPlan;
}
//----------------------------------------------------------------------------------------------
void GraphScene::RedrawScene()
{
    clear();    

    CreateGrid();
    ConstructGraph();
    LayoutGraph();
}
//----------------------------------------------------------------------------------------------
void GraphScene::CreateGrid()
{
    int height = this->height(), width = this->width();

    QPen p(Qt::DotLine);

    if (height > 0 && width > 0)
    {
        for(int y = 0; y < height - 1; y += m_cellSize)
        {
            addLine(0, y, width, y, p);
        }

        for(int x = 0; x < width - 1; x += m_cellSize)
        {    
            addLine(x, 0, x, height, p);
        }
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::ConstructGraph()
{
    if(m_pGraph == NULL)
        return;

    ComputeGraphLevels();

    GraphNodeView* pNodeView = nullptr;
    PlanStepEx*    pNodeModel = nullptr;

    for (size_t level = 0 ; level < m_graphLevels.size(); ++level)
    {
        for each (NodeID nodeId in m_graphLevels[level])
        {
            pNodeModel = m_pGraph->GetNode(nodeId);
            pNodeView = new GraphNodeView(pNodeModel, m_pNodeMenu, nullptr);

            m_nodeIdToNodeViewMap[nodeId] = pNodeView;

            addItem(pNodeView);
        }
    }

    ConnectGraphNodes();
}
//----------------------------------------------------------------------------------------------
void IStrategizer::GraphScene::ComputeGraphLevels()
{
    NodeSet roots = m_pGraph->GetOrphanNodes();
    NodeSet    visitedNodes;

    typedef int NodeLevel;
    deque< pair<NodeID, NodeLevel> >    Q;

    for each (NodeID nodeId in roots)
    {
        Q.push_back(make_pair(nodeId, 0));
        visitedNodes.insert(nodeId);
    }

    for(size_t i = 0; i < m_graphLevels.size(); ++i)
        m_graphLevels[i].clear();
    m_graphLevels.clear();

    while(!Q.empty())
    {
        NodeID nodeId = Q.front().first;
        NodeLevel nodeLevel = Q.front().second;

        Q.pop_front();

        if(nodeLevel >= m_graphLevels.size())
            m_graphLevels.resize(nodeLevel + 1);

        m_graphLevels[nodeLevel].push_back(nodeId);

        NodeSet children = m_pGraph->GetAdjacentNodes(nodeId);

        for each(NodeID nodeId in children)
        {
            if(visitedNodes.count(nodeId) == 0)
            {
                visitedNodes.insert(nodeId);
                Q.push_back(make_pair(nodeId, nodeLevel + 1));
            }
        }
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::ConnectGraphNodes()
{
    if(m_pGraph == nullptr)
        return;

    for each (NodeID srcNodeId in m_pGraph->GetNodes())
    {
        NodeSet adjNodes = m_pGraph->GetAdjacentNodes(srcNodeId);

        for each (NodeID destNodeId in adjNodes)
        {
            GraphNodeView* start = m_nodeIdToNodeViewMap[srcNodeId];
            GraphNodeView* end = m_nodeIdToNodeViewMap[destNodeId];

            GraphEdgeView* edge = new GraphEdgeView(start, end, m_edgeMenu, nullptr);
            start->AddEdge(edge);
            end->AddEdge(edge);
            addItem(edge);
        }
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::LayoutGraph()
{
    if(m_pGraph == nullptr)
        return;

    GraphNodeView* pNodeView    = nullptr;
    PlanStepEx* pNodeModel    = nullptr;
    int currNodeX;
    int levelWidth, levelHeight;
    int leveStartlX, levelStartY;

    for (size_t currLevel = 0 ; currLevel < m_graphLevels.size(); ++currLevel)
    {
        levelWidth = ComputeLevelWidth(currLevel);
        levelHeight = ComputeLevelHeight(currLevel);

        // Calculate the level drawing start y coordinate
        levelStartY = m_verticalNodeSpacing + (currLevel * (levelHeight + m_verticalNodeSpacing));

        // Calculate the level drawing start x coordinate
        leveStartlX = (width() - levelWidth) / 2.0;

        // Place each node in the current level in its appropriate coordinate
        for (size_t currNodeIdx = 0 ; currNodeIdx < m_graphLevels[currLevel].size(); ++currNodeIdx)
        {
            NodeID currNodeId = m_graphLevels[currLevel][currNodeIdx];
            int nodeWidth = m_nodeIdToNodeViewMap[currNodeId]->NodeWidth();

            // Calculate current node drawing start x coordinate
            currNodeX = leveStartlX + (currNodeIdx  * (nodeWidth + m_horizontalNodeSpacing));

            m_nodeIdToNodeViewMap[currNodeId]->setPos(QPointF(currNodeX, levelStartY));
        }
    }
}
//----------------------------------------------------------------------------------------------
int IStrategizer::GraphScene::ComputeLevelWidth(int levelIdx)
{
    int levelWidth = 0;

    // Sum the width of all level nodes
    for each (NodeID nodeID in m_graphLevels[levelIdx])
    {
        levelWidth += m_nodeIdToNodeViewMap[nodeID]->NodeWidth();
    }

    // Take into account the inter node horizontal spacing
    levelWidth += ((m_graphLevels[levelIdx].size() - 1) * m_horizontalNodeSpacing);

    return levelWidth;
}
//----------------------------------------------------------------------------------------------
int IStrategizer::GraphScene::ComputeLevelHeight(int levelIdx)
{
    int levelHeight = 0;

    // Level height is the height of the node with the largest height
    for each (NodeID nodeID in m_graphLevels[levelIdx])
    {
        levelHeight = max(levelHeight, m_nodeIdToNodeViewMap[nodeID]->NodeHeight());
    }

    return levelHeight;
}
//----------------------------------------------------------------------------------------------
void IStrategizer::GraphScene::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == updateTimerId)
        OnGraphRedraw();
}
//----------------------------------------------------------------------------------------------
void GraphScene::OnGraphStructureChange()
{
    QApplication::postEvent(this, new QEvent((QEvent::Type)SCENEEVT_GraphStructureChange));
}
//----------------------------------------------------------------------------------------------
void GraphScene::OnGraphRedraw()
{
    QApplication::postEvent(this, new QEvent((QEvent::Type)SCENEEVT_GraphRedraw));
}
//----------------------------------------------------------------------------------------------
void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *p_mouseEvent)
{
    if (p_mouseEvent->button() != Qt::LeftButton)
        return;

    if(m_mode == MODE_Connect)
    {
        m_pConnectionLine = new QGraphicsLineItem(QLineF(p_mouseEvent->scenePos(), p_mouseEvent->scenePos()));
        m_pConnectionLine->setPen(QPen(QColor("black"), 2));
        addItem(m_pConnectionLine);
    }

    QGraphicsScene::mousePressEvent(p_mouseEvent);
}
//----------------------------------------------------------------------------------------------
void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *p_mouseEvent)
{
    if (m_mode == MODE_Connect && m_pConnectionLine != 0) 
    {
        QLineF newLine(m_pConnectionLine->line().p1(), p_mouseEvent->scenePos());
        m_pConnectionLine->setLine(newLine);
    } 
    else if (m_mode == MODE_Move) 
    {
        QGraphicsScene::mouseMoveEvent(p_mouseEvent);
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *p_mouseEvent)
{
    if (m_pConnectionLine != 0 && m_mode == MODE_Connect) 
    {
        QList<QGraphicsItem *> startItems = items(m_pConnectionLine->line().p1());
        if (startItems.count() && startItems.first() == m_pConnectionLine)
            startItems.removeFirst();

        QList<QGraphicsItem *> endItems = items(m_pConnectionLine->line().p2());
        if (endItems.count() && endItems.first() == m_pConnectionLine)
            endItems.removeFirst();

        removeItem(m_pConnectionLine);
        delete m_pConnectionLine;

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first() != endItems.first()) 
        {
            GraphNodeView *startNode = qgraphicsitem_cast<GraphNodeView *>(startItems.first());
            GraphNodeView *endNode = qgraphicsitem_cast<GraphNodeView *>(endItems.first());
            ConnectNodes(startNode, endNode);
            RedrawScene();
        }
    }

    m_pConnectionLine = nullptr;
    QGraphicsScene::mouseReleaseEvent(p_mouseEvent);
}
//----------------------------------------------------------------------------------------------
void GraphScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    event->setAccepted(false);

    QGraphicsScene::contextMenuEvent(event);

    if(!event->isAccepted())
    {
        event->setAccepted(true);
        if(m_sceneMenu != NULL)
            m_sceneMenu->exec(event->screenPos());
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::UpdateNodesIndices()
{
    for(int i = 0; i < m_pPlanGraph->Size(); ++i)
    {
        GraphNode<PlanStepEx*, EdgeAnnotation>* node = m_pPlanGraph->operator [](i);
        m_nodeModelViewMapping[node->Value()]->Index(i);
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::NewNode()
{
    if(m_pChoosePlanStepDlg->exec() == QDialog::Accepted)
    {
        unsigned planStepId = m_pChoosePlanStepDlg->SelectedPlanStepId();
        PlanStepEx* planStep = NULL;

        if(BELONG(GoalType, planStepId))
            planStep = g_GoalFactory.GetGoal((GoalType)planStepId, false);
        else if(BELONG(ActionType, planStepId))
            planStep = g_ActionFactory.GetAction((ActionType)planStepId, false);

        assert(planStepId != NULL);
        m_pPlanGraph->AddNode(planStep, m_pPlanGraph->Size());
        RedrawScene();
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::NodeSelected()
{
    GraphNodeView* pNodeView =  NULL;

    if(!selectedItems().empty())
        pNodeView = dynamic_cast<GraphNodeView*>(selectedItems().first());

    emit NodeSelected(pNodeView);
}
//----------------------------------------------------------------------------------------------
void GraphScene::DeleteNode()
{
    if(selectedItems().empty())
        return;

    GraphNodeView* nodeItem = NULL;
    foreach(QGraphicsItem *item, selectedItems())
    {
        nodeItem = dynamic_cast<GraphNodeView*>(item);

        if(nodeItem == NULL)
            continue;

        if(nodeItem->Index() == CaseGoalNodeIndex)
            continue;

        GraphNode<PlanStepEx*, EdgeAnnotation>* node = m_pPlanGraph->operator [](nodeItem->Index());
        m_nodeModelViewMapping.erase(node->Value());
        m_pPlanGraph->RemoveNode(nodeItem->Index());
        UpdateNodesIndices();

        QList<GraphEdgeView*> disconnectedEdges = nodeItem->Disconnect();

        foreach(GraphEdgeView* edge, disconnectedEdges)
            removeItem(edge);

        removeItem(item);
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::DeleteEdge()
{
    if(selectedItems().empty())
        return;

    GraphEdgeView* edgeItem = NULL;
    foreach(QGraphicsItem *item, selectedItems())
    {
        edgeItem = dynamic_cast<GraphEdgeView*>(item);

        if(edgeItem == NULL)
            continue;

        int start, end;
        start    = edgeItem->StartNode()->Index();
        end        = edgeItem->EndNode()->Index();

        if(start != CaseGoalNodeIndex && end != CaseGoalNodeIndex)
            m_pPlanGraph->Disconnect(start, end);

        removeItem(item);
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::DuplicateNode()
{
    if(selectedItems().empty())
        return;

    GraphNodeView* nodeItem = NULL;
    foreach(QGraphicsItem *item, selectedItems())
    {
        nodeItem = dynamic_cast<GraphNodeView*>(item);

        if(nodeItem == NULL)
            continue;

        PlanStepEx* sourceNode = m_pPlanGraph->operator [](nodeItem->Index())->Value();
        m_pPlanGraph->AddNode((PlanStepEx*)sourceNode->Clone(), m_pPlanGraph->Size());
        //m_planGraph->AddNode(newNode->Clone(), m_planGraph->Size());
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::ConnectNodes(GraphNodeView* p_start, GraphNodeView* p_end)
{
    if(p_start != NULL && p_end != NULL && p_start->Index() != CaseGoalNodeIndex && p_end->Index() != CaseGoalNodeIndex)
        m_pPlanGraph->Connect(p_start->Index(), p_end->Index(), SVector<Expression*>());
}
//----------------------------------------------------------------------------------------------
void GraphScene::DisconnectNode()
{
    if(selectedItems().empty())
        return;

    GraphNodeView* nodeItem = NULL;
    foreach(QGraphicsItem *item, selectedItems())
    {
        nodeItem = dynamic_cast<GraphNodeView*>(item);

        if(nodeItem == NULL)
            continue;

        if(nodeItem->Index() == CaseGoalNodeIndex)
            continue;

        GraphNode<PlanStepEx*, EdgeAnnotation>* node = m_pPlanGraph->operator [](nodeItem->Index());
        QList<GraphEdgeView*> disconnectedEdges = nodeItem->Disconnect();
        
        foreach(GraphEdgeView* edge, disconnectedEdges)
        {
            if (edge->StartNode()->Index() == CaseGoalNodeIndex ||
                edge->EndNode()->Index() == CaseGoalNodeIndex)
                continue;

            m_pPlanGraph->Disconnect(edge->StartNode()->Index(), edge->EndNode()->Index());
            removeItem(edge);
        }
    }
}
//----------------------------------------------------------------------------------------------
bool GraphScene::event( QEvent * e )
{
    assert(e);
    SceneEvent evt = (SceneEvent)e->type();

    if (evt == SCENEEVT_GraphStructureChange)
    {
        RedrawScene();
        return true;
    }
    else if (evt == SCENEEVT_GraphRedraw)
    {
        update();
        return true;
    }
    else
    {
        return QGraphicsScene::event(e);
    }
}
