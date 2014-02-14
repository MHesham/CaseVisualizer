#ifndef CASEVIEW_H
#define CASEVIEW_H

#include <QWidget>
#include "ui_CaseView.h"

#ifndef ENGINEDATA_H
#include "EngineData.h"
#endif
#ifndef CROSSMAP_H
#include "CrossMap.h"
#endif

#include <string>
#include <hash_map>
#include "GraphScene.h"

#define GameIdsLookupFilename "IdLookup.txt"

namespace IStrategizer
{
	class CaseEx;
	class GoalEx; 
	class GameStateEx;
	class GraphScene;
	class PlanGraphView;

	class CaseView : public QWidget
	{
		Q_OBJECT

	public:
		CaseView(CrossMap<unsigned, std::string>* p_idLookup, QWidget *parent = 0);
		~CaseView();
		void View(CaseEx* p_case);
		void SetMode(GraphScene::PointerMode p_mode);

	private:
		CrossMap<unsigned, std::string>* m_idLookup;
		PlanGraphView*				m_graphView;
		Ui::CaseViewClass			ui;
		CaseEx*						m_currentCase;

		void ViewGoal(GoalEx* p_goal);
		void ViewGoalParameters(PlanStepParameters* p_params);
		void ViewGameState(GameStateEx* p_gameState);
		void ViewPlanGraph(GoalEx* p_caseGoal, IOlcbpPlanDigraph* p_planGraph);
		void InitializeIdLookup();
		void CreatePlanView();
		void ViewPerformance(CaseEx *p_pCase);

		private slots:
			void on_txtTrialCount_textChanged(const QString &p_newText);
			void on_txtSuccessCount_textChanged(const QString &p_newText);
			void OnCellChanged(int p_row, int p_column);
	};
}

#endif // CASEVIEW_H
