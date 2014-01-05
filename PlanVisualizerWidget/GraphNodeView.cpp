#include "stdafx.h"

#ifndef GRAPHNODEVIEW_H
#include "GraphNodeView.h"
#endif
#ifndef GRAPHEDGEVIEW_H
#include "stdafx.h"
#include "GraphEdgeView.h"
#endif
#ifndef PLANSTEPEX_H
#include "PlanStepEx.h"
#endif

#include <QBrush>
#include <QColor>
#include <QTextOption>
#include <QTextItem>
#include <QMenu>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>

using namespace IStrategizer;
using namespace std;

GraphNodeView::GraphNodeView(PlanStepEx* p_planStep, QMenu *p_contextMeun, QGraphicsItem *p_parent /* = 0 */) 
	: QGraphicsRectItem(p_parent)
{
	m_nodeModel		= p_planStep;
	m_nodeHeight	= DefaultNodeHeight;
	m_nodeWidth		= DefaultNodeWidth;
	m_contextMenu	= p_contextMeun;

    if(BELONG(GoalType, p_planStep->StepTypeId()))
	{
		QColor color(0, 0, 255, 192);
		QBrush brush(color, Qt::SolidPattern);
		setBrush(brush);
	}
	else
	{
		QColor color(0, 255, 0, 192);
		QBrush brush(color, Qt::SolidPattern);
		setBrush(brush);
	}

    string nodeName = m_nodeModel->ToString();
    size_t findLeftParanPos = nodeName.find("(");

    if (findLeftParanPos != string::npos)
    {
        nodeName = nodeName.substr(0, findLeftParanPos);
    }

    m_nodeTxt = QString::fromStdString(nodeName);

    m_nodeTxtFont.setBold(true);
    m_nodeTxtFont.setPixelSize(20);

    // Measure text width and set the node width accordingly with small padding
    QFontMetrics fontMetric(m_nodeTxtFont);
    m_nodeTxtWidth = fontMetric.width(m_nodeTxt) + 10;

	setToolTip(QString::fromLocal8Bit(p_planStep->TypeName().c_str()));
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemIsMovable, true);
}
//----------------------------------------------------------------------------------------------
void GraphNodeView::AddEdge(GraphEdgeView* p_edge)
{
	m_edges.append(p_edge);
}
//----------------------------------------------------------------------------------------------
void GraphNodeView::RemoveEdge(GraphEdgeView* p_edge)
{
	QList<GraphEdgeView*>::iterator where = find(m_edges.begin(), m_edges.end(), p_edge);

	if(where != m_edges.end())
		m_edges.erase(where);
}
//----------------------------------------------------------------------------------------------
QList<GraphEdgeView*> GraphNodeView::Disconnect()
{
	GraphNodeView *other = NULL;
	QList<GraphEdgeView*> edges(m_edges);

	foreach(GraphEdgeView* edge, edges)
	{
		if(edge->StartNode() != this)
			other = edge->StartNode();
		else
			other = edge->EndNode();

		other->RemoveEdge(edge);
		this->RemoveEdge(edge);
	}

	return edges;
}
//----------------------------------------------------------------------------------------------
QVariant GraphNodeView::itemChange(GraphicsItemChange change,
								 const QVariant &value)
{
	if (change == QGraphicsItem::ItemPositionChange) 
	{
		foreach (GraphEdgeView *edge, m_edges) 
		{
			edge->UpdatePosition();
		}
	}

	return value;
}
//----------------------------------------------------------------------------------------------
void GraphNodeView::paint(QPainter *p_painter, const QStyleOptionGraphicsItem *p_option, QWidget *p_widget)
{ 
	QGraphicsRectItem::paint(p_painter, p_option, p_widget);
	
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignCenter);

    setRect(0, 0, m_nodeTxtWidth, m_nodeHeight);

    p_painter->setFont(m_nodeTxtFont);

	p_painter->drawText(this->rect(), m_nodeTxt, textOption);
}
//----------------------------------------------------------------------------------------------
void GraphNodeView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	event->accept();
	scene()->clearSelection();
	setSelected(true);
	if(m_contextMenu != NULL)
		m_contextMenu->exec(event->screenPos());
}