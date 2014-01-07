#ifndef GRAPHNODEVIEW_H
#define GRAPHNODEVIEW_H

#include <QGraphicsRectItem>
#include <QList>
#include <QPen>
#include <QFont>
#include <QBrush>

class QGraphicsItem;
class QGraphicsScene;
class QMenu;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneContextMenuEvent;

namespace IStrategizer
{
    class GraphEdgeView;
    class PlanStepEx;

    const int DefaultNodeWidth = 48;
    const int DefaultNodeHeight = 32;
    const int CaseGoalNodeIndex = -1;

    class GraphNodeView : public QGraphicsRectItem
    {
    public:
        struct NodeStyle
        {
            QBrush BackgroundBrush;
            QPen BorderPen;
            QPen TxtPen;
            QFont TxtFont;
        };

        GraphNodeView(PlanStepEx* p_planStep, QMenu *p_contextMenu, QGraphicsItem *p_parent = 0);
        void RemoveEdge(GraphEdgeView* p_edge);
        QList<GraphEdgeView*> Disconnect();
        PlanStepEx* NodeModel() { return m_nodeModel; }
        const PlanStepEx* NodeModel() const { return m_nodeModel; }
        void AddEdge(GraphEdgeView* p_edge);
        int Index() const { return m_index; }
        void Index(int p_index) { m_index = p_index; }
        int NodeWidth() const { return m_nodeWidth; }
        int NodeHeight() const { return m_nodeHeight; }

    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant &value);
        void paint(QPainter *p_painter, const QStyleOptionGraphicsItem *p_option, QWidget *p_widget = 0);
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
        NodeStyle GetStyle();

    private:
        int m_nodeWidth;
        int m_nodeHeight;
        QMenu *m_contextMenu;
        int m_index;
        PlanStepEx* m_nodeModel;
        QString m_nodeTxt;
        QList<GraphEdgeView*> m_edges;
        NodeStyle   m_style;
    };
}

#endif // GRAPHNODEVIEW_H