#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <map>
#include <vector>

#ifndef CROSSMAP_H
#include "CrossMap.h"
#endif

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
	class PlanStepEx;
	class GraphNodeView;
	class GoalEx;
	class ChoosePlanStepDialog;

	const int DefaultCellSize = 16;
	const int DefaultHorizontalNodeSpacing = 48;
	const int DefaultVerticalNodeSpacing = 48;

	class GraphScene : public QGraphicsScene
	{
		Q_OBJECT

	public:
		enum PointerMode { MODE_Move, MODE_Connect };

		GraphScene(CrossMap<unsigned, std::string>* p_idLookup, QObject *p_parent = 0);
		void View(GoalEx* p_caseGoal, PlanGraph* p_planGraph);
		void Mode(PointerMode p_mode) { m_mode = p_mode; }
		PointerMode Mode() const { return m_mode; }

		~GraphScene();

	protected:
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
		void mousePressEvent(QGraphicsSceneMouseEvent *p_mouseEvent);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *p_mouseEvent);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *p_mouseEvent);

	private:
		int m_cellSize;
		int m_nodeWidth;
		int m_nodeHeight;
		int m_horizontalNodeSpacing;
		int m_verticalNodeSpacing;
		PlanGraph *m_planGraph;
		GoalEx* m_caseGoal;
		QMenu* m_nodeMenu;
		QMenu* m_edgeMenu;
		QMenu* m_sceneMenu;
		QColor m_nodeColor;
		QColor m_lineColor;
		QGraphicsLineItem* m_connectionLine;
		ChoosePlanStepDialog* m_choosePlanStep;
		PointerMode m_mode;
		std::map<PlanStepEx*, GraphNodeView*> m_nodeModelViewMapping;
		std::map<int, GraphNodeView*> m_nodeIndexViewMapping;
		std::vector< std::vector<int> >	m_graphLevels;

		void CreateGrid();
		void ConstructGraph();
		void CreateEdgeMenu();
		void CreateNodeMenu();
		void CreateSceneMenu();
		void UpdateNodesIndices();
		void CreateCaseGoalNode( std::vector<int> &p_roots, std::map<int, GraphNodeView*> &p_nodeIndexViewMapping );
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