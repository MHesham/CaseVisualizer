#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <map>
#include <vector>

#ifndef CROSSMAP_H
#include "CrossMap.h"
#endif

#include "OlcbpPlanGraphAdapter.h"

class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QGraphicsLineItem;

namespace IStrategizer
{
	class PlanGraph;
	class GraphNodeView;
	class GoalEx;
	class ChoosePlanStepDialog;

	const int DefaultCellSize = 16;
	const int DefaultHorizontalNodeSpacing = 48;
	const int DefaultVerticalNodeSpacing = 48;

    typedef IDigraph<PlanStepEx*> IPlanDigraph;

	class GraphScene : public QGraphicsScene
	{
		Q_OBJECT

	public:
        typedef IPlanDigraph::NodeID NodeID;
        typedef IPlanDigraph::NodeSet NodeSet;

		enum PointerMode { MODE_Move, MODE_Connect };

		GraphScene(CrossMap<unsigned, std::string>* p_idLookup, QObject *p_parent = 0);
        void View(IPlanDigraph* pGraph);
		void Mode(PointerMode p_mode) { m_mode = p_mode; }
		PointerMode Mode() const { return m_mode; }

	protected:
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
		void mousePressEvent(QGraphicsSceneMouseEvent *p_mouseEvent);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *p_mouseEvent);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *p_mouseEvent);
        bool event ( QEvent * e );

	private:
		int m_cellSize;
		int m_nodeWidth;
		int m_nodeHeight;
		int m_horizontalNodeSpacing;
		int m_verticalNodeSpacing;
	    PlanGraph *m_pPlanGraph;
		GoalEx* m_caseGoal;
		QMenu* m_pNodeMenu;
		QMenu* m_edgeMenu;
		QMenu* m_sceneMenu;
		QColor m_nodeColor;
		QColor m_lineColor;
		QGraphicsLineItem* m_pConnectionLine;
		ChoosePlanStepDialog* m_pChoosePlanStepDlg;
		PointerMode m_mode;
		std::map<PlanStepEx*, GraphNodeView*> m_nodeModelViewMapping;
		std::map<int, GraphNodeView*> m_nodeIndexViewMapping;
        IPlanDigraph *m_pGraph;
        std::vector< std::vector<NodeID> >	m_graphLevels;
        std::map<NodeID, GraphNodeView*> m_nodeIdToNodeViewMap;

		void CreateGrid();
		void ConstructGraph();

        //************************************
        // IStrategizer::GraphScene::ComputeGraphLevels
        // Description:	Do a BFS traversal on the graph to decide node levels to be used
        // in graph layout and drawing
        // Returns:   	void
        //************************************
        void ComputeGraphLevels();

        void CreateEdgeMenu();
		void CreateNodeMenu();
		void CreateSceneMenu();
		void UpdateNodesIndices();
		void ConnectNodes(GraphNodeView* p_start, GraphNodeView* p_end);
		void CreateMenus();
		void ConnectGraphNodes();
		void LayoutGraph();

		private slots:
			void UpdateView();
			void NodeSelected();
			void NewNode();
			void DeleteNode();
			void DeleteEdge();
			void DisconnectNode();

			void DuplicateNode();

signals:
			void NodeSelected(GraphNodeView* p_node);
	};
}

#endif // GRAPHSCENE_H