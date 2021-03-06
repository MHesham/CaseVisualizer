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
#include "IStrategizerException.h"


using namespace IStrategizer;
using namespace Serialization;
using namespace std;

GraphScene::GraphScene(CrossMap<unsigned, string>* pIdLookup, QObject *pParent) : QGraphicsScene(pParent)
{
    m_horizontalNodeSpacing = DefaultHorizontalNodeSpacing;
    m_verticalNodeSpacing = DefaultVerticalNodeSpacing;
    m_pNodeMenu = nullptr;
    m_pChoosePlanStepDlg = new ChoosePlanStepDialog(pIdLookup, true, true);
    m_pointerMode = PTRMODE_Move;
    m_pConnectionLine = nullptr;
    m_pGraph = nullptr;
    m_cellSize = DefaultGridCellSize;
    m_lastCtxtMenuScreenPos = QPointF(0.0, 0.0);

    connect(this, SIGNAL(selectionChanged()), SLOT(NodeSelected()));

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
    QAction *pDuplicateAction = new QAction(tr("Duplicate"), this);
    pDuplicateAction->setStatusTip(tr("Duplicates graph node"));
    connect(pDuplicateAction, SIGNAL(triggered()), this, SLOT(DuplicateNode()));

    QAction *pDeleteAction = new QAction(tr("Delete"), this);
    pDuplicateAction->setStatusTip(tr("Deletes graph node"));
    connect(pDeleteAction, SIGNAL(triggered()), this, SLOT(DeleteNode()));

    QAction *pDisconnectAction = new QAction(tr("Disconnect"), this);
    pDisconnectAction->setStatusTip(tr("Disconnects the node from the graph"));
    connect(pDisconnectAction, SIGNAL(triggered()), this, SLOT(DisconnectNode()));

    m_pNodeMenu = new QMenu(tr("Node Menu"));
    m_pNodeMenu->setTearOffEnabled(true);
    m_pNodeMenu->addAction(pDeleteAction);
    m_pNodeMenu->addAction(pDuplicateAction);
    m_pNodeMenu->addAction(pDisconnectAction);
}
//----------------------------------------------------------------------------------------------
void GraphScene::CreateEdgeMenu()
{
    QAction *pDeleteAction = new QAction(tr("&Delete"), this);
    pDeleteAction->setStatusTip(tr("Deletes graph edge"));
    pDeleteAction->setShortcut(QString::fromLocal8Bit("D"));
    connect(pDeleteAction, SIGNAL(triggered()), this, SLOT(DeleteEdge()));

    m_pEdgeMenu = new QMenu(tr("Edge Menu"));
    m_pEdgeMenu->setTearOffEnabled(true);
    m_pEdgeMenu->addAction(pDeleteAction);
}
//----------------------------------------------------------------------------------------------
void GraphScene::CreateSceneMenu()
{
    QAction *pNewNodeAction = new QAction(tr("N&ew Node"), this);
    pNewNodeAction->setStatusTip(tr("Creates new plan graph node"));
    connect(pNewNodeAction, SIGNAL(triggered()), this, SLOT(NewNode()));

    QAction *pLayoutGraph = new QAction(tr("L&ayout Plan"), this);
    pLayoutGraph->setStatusTip(tr("Layout plan graph in the scene"));
    connect(pLayoutGraph, SIGNAL(triggered()), this, SLOT(ReconstructScene()));

    m_pSceneMenu = new QMenu(tr("Scene Menu"));
    m_pSceneMenu->setTearOffEnabled(true);
    m_pSceneMenu->addAction(pNewNodeAction);
    m_pSceneMenu->addAction(pLayoutGraph);
}
//----------------------------------------------------------------------------------------------
void GraphScene::View(IOlcbpPlan* pPlan)
{
    m_pGraph = pPlan;
}
//----------------------------------------------------------------------------------------------
void GraphScene::ReconstructScene()
{
    clear();

    CreateGrid();
    ConstructGraph();
    LayoutGraph();
}
//----------------------------------------------------------------------------------------------
void GraphScene::CreateGrid()
{
    int height = (int)this->height(), width = (int)this->width();

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
    NodeValue pNodeModel = nullptr;

    for (size_t level = 0 ; level < m_graphLevels.size(); ++level)
    {
        for each (NodeID nodeId in m_graphLevels[level])
        {
            pNodeModel = m_pGraph->GetNode(nodeId);
            pNodeView = new GraphNodeView(pNodeModel, nodeId, m_pNodeMenu, nullptr);

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
    NodeSet visitedNodes;

    typedef size_t NodeLevel;
    deque< pair<NodeID, NodeLevel> > Q;

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

    IOlcbpPlan::NodeSet nodes = m_pGraph->GetNodes();

    for each (NodeID srcNodeId in nodes)
    {
        NodeSet adjNodes = m_pGraph->GetAdjacentNodes(srcNodeId);

        for each (NodeID destNodeId in adjNodes)
        {
            GraphNodeView* pStart = m_nodeIdToNodeViewMap[srcNodeId];
            GraphNodeView* pEnd = m_nodeIdToNodeViewMap[destNodeId];

            ConnectNodeViews(pStart, pEnd);
        }
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::LayoutGraph()
{
    if(m_pGraph == nullptr)
        return;

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
        leveStartlX = (int)((width() - (qreal)levelWidth) / 2.0f);
        currNodeX = leveStartlX;

        // Place each node in the current level in its appropriate coordinate
        for (size_t currNodeIdx = 0 ; currNodeIdx < m_graphLevels[currLevel].size(); ++currNodeIdx)
        {
            NodeID currNodeId = m_graphLevels[currLevel][currNodeIdx];
            int nodeWidth = m_nodeIdToNodeViewMap[currNodeId]->NodeWidth();

            m_nodeIdToNodeViewMap[currNodeId]->setPos(QPointF(currNodeX, levelStartY));

            // Calculate current node drawing start x coordinate
            currNodeX += nodeWidth + m_horizontalNodeSpacing;
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
void GraphScene::OnGraphStructureChange()
{
    QApplication::postEvent(this, new QEvent((QEvent::Type)SCENEEVT_GraphStructureChange));
}
//----------------------------------------------------------------------------------------------
void GraphScene::OnGraphUpdate()
{
    QApplication::postEvent(this, new QEvent((QEvent::Type)SCENEEVT_GraphRedraw));
}
//----------------------------------------------------------------------------------------------
void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *p_mouseEvent)
{
    if (p_mouseEvent->button() != Qt::LeftButton)
        return;

    if(m_pointerMode == MODE_Connect)
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
    if (m_pointerMode == MODE_Connect && m_pConnectionLine != 0) 
    {
        QLineF newLine(m_pConnectionLine->line().p1(), p_mouseEvent->scenePos());
        m_pConnectionLine->setLine(newLine);
    } 
    else if (m_pointerMode == PTRMODE_Move) 
    {
        QGraphicsScene::mouseMoveEvent(p_mouseEvent);
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *p_mouseEvent)
{
    if (m_pConnectionLine != 0 && m_pointerMode == MODE_Connect) 
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
            GraphNodeView *pStartNode = qgraphicsitem_cast<GraphNodeView *>(startItems.first());
            GraphNodeView *pEndNode = qgraphicsitem_cast<GraphNodeView *>(endItems.first());

            if (pStartNode != nullptr &&
                pEndNode != nullptr)
            {
                m_pGraph->AddEdge(pStartNode->ModelId(), pEndNode->ModelId());
                ConnectNodeViews(pStartNode, pEndNode);
            }
        }
    }

    m_pConnectionLine = nullptr;
    QGraphicsScene::mouseReleaseEvent(p_mouseEvent);
}
//----------------------------------------------------------------------------------------------
void GraphScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvt)
{
    pEvt->setAccepted(false);

    QGraphicsScene::contextMenuEvent(pEvt);

    if(!pEvt->isAccepted())
    {
        pEvt->setAccepted(true);
        if(m_pSceneMenu != NULL)
        {
            m_lastCtxtMenuScreenPos = pEvt->scenePos();
            m_pSceneMenu->exec(pEvt->screenPos());
        }
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::NewNode()
{
    if(m_pChoosePlanStepDlg->exec() == QDialog::Accepted)
    {
        unsigned planStepId = m_pChoosePlanStepDlg->SelectedPlanStepId();
        NodeValue pNodeModel = NULL;

        if(BELONG(GoalType, planStepId))
            pNodeModel = g_GoalFactory.GetGoal((GoalType)planStepId, false);
        else if(BELONG(ActionType, planStepId))
            pNodeModel = g_ActionFactory.GetAction((ActionType)planStepId, false);
        else
            throw NotImplementedException(XcptHere);

        assert(planStepId != NULL);

        NodeID nodeId = m_pGraph->AddNode(pNodeModel);

        GraphNodeView *pNodeView = new GraphNodeView(pNodeModel, nodeId, m_pNodeMenu, nullptr);

        pNodeView->setPos(m_lastCtxtMenuScreenPos.x(), m_lastCtxtMenuScreenPos.y());

        m_nodeIdToNodeViewMap[nodeId] = pNodeView;

        addItem(pNodeView);
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

    GraphNodeView* pNodeView = NULL;

    foreach(QGraphicsItem *pItem, selectedItems())
    {
        pNodeView = dynamic_cast<GraphNodeView*>(pItem);

        if(pNodeView == NULL)
            continue;

        m_pGraph->RemoveNode(pNodeView->ModelId());

        QList<GraphEdgeView*> disconnectedEdges = pNodeView->Disconnect();

        foreach(GraphEdgeView* pEdge, disconnectedEdges)
            removeItem(pEdge);

        removeItem(pItem);
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

        NodeID startNode, endNode;
        startNode = edgeItem->StartNode()->ModelId();
        endNode = edgeItem->EndNode()->ModelId();

        m_pGraph->RemoveEdge(startNode, endNode);

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

        NodeValue sourceNode = (NodeValue)m_pGraph->GetNode(nodeItem->ModelId())->Clone();
        m_pGraph->AddNode(sourceNode);
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::ConnectNodeViews(GraphNodeView* pStart, GraphNodeView* pEnd)
{
    if(pStart != NULL && pEnd != NULL)
    {
        GraphEdgeView* pEdge = new GraphEdgeView(pStart, pEnd, m_pEdgeMenu, nullptr);
        pStart->AddEdge(pEdge);
        pEnd->AddEdge(pEdge);
        addItem(pEdge);
    }
}
//----------------------------------------------------------------------------------------------
void GraphScene::DisconnectNode()
{
    if(selectedItems().empty())
        return;

    GraphNodeView* pNodeView = NULL;

    foreach(QGraphicsItem *pItem, selectedItems())
    {
        pNodeView = dynamic_cast<GraphNodeView*>(pItem);

        if(pNodeView == NULL)
            continue;

        QList<GraphEdgeView*> disconnectedEdges = pNodeView->Disconnect();
        
        foreach(GraphEdgeView* pEdge, disconnectedEdges)
        {
            m_pGraph->RemoveEdge(pEdge->StartNode()->ModelId(), pEdge->EndNode()->ModelId());
            removeItem(pEdge);
        }
    }
}
//----------------------------------------------------------------------------------------------
bool GraphScene::event(QEvent * pEvt)
{
    assert(pEvt);
    SceneEvent evt = (SceneEvent)pEvt->type();

    if (evt == SCENEEVT_GraphStructureChange)
    {
        ReconstructScene();
        return true;
    }
    else if (evt == SCENEEVT_GraphRedraw)
    {
        update();
        return true;
    }
    else
    {
        return QGraphicsScene::event(pEvt);
    }
}
