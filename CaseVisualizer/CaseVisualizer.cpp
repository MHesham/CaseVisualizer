#include "CaseVisualizer.h"

#include <QFileDialog>
#include <QString>
#include <sstream>
#include <cassert>
#include <QDockWidget>
#include <QToolBar>
#include <QButtonGroup>
#include <QToolButton>
#include <QMessageBox>
#include <QApplication>
#include <QStatusBar>

using namespace std;

#ifndef CASEBASEEX_H
#include "CaseBaseEx.h"
#endif
#ifndef OBJECTSERIALIZER_H
#include "ObjectSerializer.h"
#endif
#ifndef SERIALIZATIONESSENTIALS_H
#include "SerializationEssentials.h"
#endif
#ifndef GOALFACTORY_H
#include "GoalFactory.h"
#endif
#ifndef GAMESTATEEX_H
#include "GameStateEx.h"
#endif
#ifndef TOOLBOX_H
#include "Toolbox.h"
#endif
#ifndef CASEVIEW_H
#include "CaseView.h"
#endif
#ifndef WINGAMEGOAL_H
#include "WinGameGoal.h"
#endif
#ifndef CHOOSEPLANSTEPDIALOG_H
#include "ChoosePlanStepDialog.h"
#endif
#ifndef IDLOOKUPREADER_H
#include "IdLookupReader.h"
#endif
#ifndef GRAPHSCENE_H
#include "GraphScene.h"
#endif

using namespace IStrategizer;

CaseVisualizer::CaseVisualizer(QWidget *parent, Qt::WindowFlags flags)
: QMainWindow(parent, flags), m_caseBase(new CaseBaseEx)
{

    ui.setupUi(this);
    CreateToolBox();

    IStrategizer::Init();

    if (InitIdLookup())
    {
        m_caseView = new CaseView(&m_idLookup, ui.caseViewFrame);
        m_goalDialog = new ChoosePlanStepDialog(&m_idLookup, true, false, this);
        this->setCentralWidget(ui.caseViewFrame);

        NewCaseBase();
        NewCase(GOALEX_WinGame);
    }
}
//----------------------------------------------------------------------------------------------
bool CaseVisualizer::InitIdLookup()
{
    IdLookupReader reader;

    // Read game specific IDs
    if (!reader.ReadEx(GameIdsLookupFilename, m_idLookup))
    {
        QMessageBox::warning(this, tr("Initialization Error"), tr("'%1' file is not found.").arg(GameIdsLookupFilename));
        return false;
    }

    for (unsigned currID = 0; currID < ENUMS_SIZE; ++currID)
    {
        // Read engine specific IDs form Enums to the IdLookup
        if (!BELONG(EntityClassType, currID) &&
            !BELONG(ResearchType, currID))
        {
            if (Enums[currID] != nullptr)
            {
                m_idLookup.SetByFirst(currID, string(Enums[currID]));
            }
        }
        // Read game specific IDs from Idlookup to Enums if such IDs are valid game type ids
        else if (Enums[currID] == nullptr && m_idLookup.ContainsFirst(currID))
        {
            Enums[currID] = _strdup(m_idLookup.GetByFirst(currID).c_str());
        }
    }

    return true;
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::CreateToolBox()
{
    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setText(QString("Select"));

    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setText(QString("Connect"));

    m_pointerTypeGroup = new QButtonGroup;
    m_pointerTypeGroup->addButton(pointerButton, (int)GraphScene::PTRMODE_Move);
    m_pointerTypeGroup->addButton(linePointerButton, (int)GraphScene::MODE_Connect);
    connect(m_pointerTypeGroup, SIGNAL(buttonClicked(int)), this, SLOT(PointerGroupClicked(int)));

    m_pointerToolbar = addToolBar(tr("Pointer type"));
    m_pointerToolbar->addWidget(pointerButton);
    m_pointerToolbar->addWidget(linePointerButton);
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::PointerGroupClicked(int)
{
    m_caseView->SetMode((GraphScene::PointerMode)m_pointerTypeGroup->checkedId());
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::on_actionOpen_triggered()
{
    OpenCaseBase();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::on_actionSave_triggered()
{
    SaveCaseBase();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::on_actionSaveAs_triggered()
{
    SaveCaseBaseAs();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::on_actionNew_triggered()
{
    NewCaseBase();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::on_actionShow_triggered()
{
    ui.caseBaseViewDockWidget->show();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::on_lstCases_itemDoubleClicked(QListWidgetItem*)
{
    EditCase();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::on_btnNewCase_clicked()
{
    NewCase();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::on_btnDeleteCase_clicked()
{
    if(ui.lstCases->currentItem() != NULL)
    {
        if(ui.lstCases->currentIndex().row() >= 0)
        {
            DeleteCase(ui.lstCases->currentIndex().row());
        }
    }
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::on_lstCases_itemSelectionChanged()
{
    int caseIdx = ui.lstCases->currentIndex().row();

    if(caseIdx >= 0 &&
        caseIdx < m_caseBase->CaseContainer.size())
        m_caseView->View(m_caseBase->CaseContainer[caseIdx]);
    else if (caseIdx == m_caseBase->CaseContainer.size())
    {
        m_caseView->View(m_caseBase->CaseContainer[caseIdx -1]);
    }
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::OpenCaseBase()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open CaseBase"),
        QDir::currentPath(),
        CaseBaseFilter);

    if(QFile::exists(fileName))
    {
        Toolbox::MemoryClean(m_caseBase);

        m_caseBasePath = fileName;
        m_caseBase = new CaseBaseEx();
        g_ObjectSerializer.Deserialize(m_caseBase, string(fileName.toLocal8Bit()));
        Refresh();
    }
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::NewCaseBase()
{
    Toolbox::MemoryClean(m_caseBase);
    m_caseBase = new CaseBaseEx();
    Refresh();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::SaveCaseBaseAs()
{
    QString path = QDir::currentPath();
    QString fileName = QFileDialog::getSaveFileName(
        this, 
        tr("Open CaseBase"),
        QDir::currentPath(),
        CaseBaseFilter);

    if(!fileName.isEmpty())
    {
        g_ObjectSerializer.Serialize(m_caseBase, string(fileName.toLocal8Bit()));
    }
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::SaveCaseBase()
{
    if (m_caseBasePath.isEmpty())
        SaveCaseBaseAs();
    else
    {
        statusBar()->showMessage("Case base saved ...", 2000);
        g_ObjectSerializer.Serialize(m_caseBase, string(m_caseBasePath.toLocal8Bit()));
    }
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::Refresh()
{
    stringstream entryStream;
    string caseGoalName;
    GoalEx* pCaseGoal;

    ui.lstCases->clear();

    int i = 0;
    for(SVector<CaseEx*>::iterator caseItr = m_caseBase->CaseContainer.begin();
        caseItr != m_caseBase->CaseContainer.end();
        ++caseItr)
    {
        entryStream.str("");
        entryStream << i << ' ';

        if((*caseItr)->Goal() == NULL)
            entryStream << "UnnamedCase-" << i;
        else
        {
            pCaseGoal = const_cast<GoalEx*>((*caseItr)->Goal());
            assert(pCaseGoal);

            caseGoalName = m_idLookup.GetByFirst(pCaseGoal->StepTypeId());
            entryStream << caseGoalName;
        }

        ui.lstCases->addItem(new QListWidgetItem(entryStream.str().c_str()));

        ++i;
    }
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::NewCase()
{
    if(m_goalDialog->exec() == QDialog::Accepted)
    {
        GoalEx* newGoal = g_GoalFactory.GetGoal((GoalType)m_goalDialog->SelectedPlanStepId(), false);
        CaseEx* newCase = new CaseEx(new PlanGraph, newGoal, new GameStateEx, 1, 1);
        m_caseBase->CaseContainer.push_back(newCase);
        Refresh();
    }
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::NewCase(GoalType p_caseGoal)
{
    GoalEx* newGoal = g_GoalFactory.GetGoal(p_caseGoal, false);
    CaseEx* newCase = new CaseEx(new OlcbpPlanDigraph, newGoal, new GameStateEx, 1, 1);
    m_caseBase->CaseContainer.push_back(newCase);
    Refresh();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::DeleteCase(int p_caseIdx)
{
    CaseEx* c = *(m_caseBase->CaseContainer.begin() + p_caseIdx);
    Toolbox::MemoryClean(c);
    m_caseBase->CaseContainer.erase(m_caseBase->CaseContainer.begin() + p_caseIdx);
    Refresh();
}
//----------------------------------------------------------------------------------------------
void CaseVisualizer::EditCase()
{
}
//----------------------------------------------------------------------------------------------
CaseVisualizer::~CaseVisualizer()
{
    Toolbox::MemoryClean(m_caseBase);
    Toolbox::MemoryClean(m_caseView);
    Toolbox::MemoryClean(m_goalDialog);
}
