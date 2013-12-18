#include "ParameterEdit.h"
#include <QCompleter>

#ifndef TOOLBOX_H
#include "Toolbox.h"
#endif

using namespace IStrategizer;

ParameterEdit::ParameterEdit(string p_paramName, string p_paramValue, CrossMap<unsigned, string>* p_idLookup, QWidget *parent)
: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);

	m_paramName = p_paramName;
	m_paramValue = p_paramValue;
	m_idLookup = p_idLookup;

	ui.lineEditParamValue->setEditable(true);
	InitializeAutoComplete();
}
//----------------------------------------------------------------------------------------------
void ParameterEdit::InitializeAutoComplete()
{
	vector<string> stdStringValues;
	m_idLookup->SecondValues(stdStringValues);

	QStringList qtStringParamValues;
	for(int i = 0, size = stdStringValues.size(); i < size; ++i)
	{
		qtStringParamValues << QString::fromLocal8Bit(stdStringValues[i].c_str());
	}

	m_autoComplete = new QCompleter(qtStringParamValues);
	m_autoComplete->setCompletionMode(QCompleter::PopupCompletion);
	m_autoComplete->setCaseSensitivity(Qt::CaseInsensitive);
	ui.lineEditParamValue->setCompleter(m_autoComplete);
	ui.lineEditParamValue->addItems(qtStringParamValues);
}
//----------------------------------------------------------------------------------------------
int ParameterEdit::exec()
{
	ui.lblActualParamName->setText(QString::fromLocal8Bit(m_paramName.c_str()));
	int idx = ui.lineEditParamValue->findText(QString::fromLocal8Bit(m_paramValue.c_str()));
	ui.lineEditParamValue->setCurrentIndex(idx);

	return QDialog::exec();
}
//----------------------------------------------------------------------------------------------
void ParameterEdit::on_btnOK_clicked()
{
	if(m_idLookup->ContainsSecond(string(ui.lineEditParamValue->currentText().toLocal8Bit())))
	{
		m_paramValue = ui.lineEditParamValue->currentText().toLocal8Bit();
	}

	this->accept();
}
//----------------------------------------------------------------------------------------------
void ParameterEdit::on_btnCancel_clicked()
{
	this->reject();
}
//----------------------------------------------------------------------------------------------
ParameterEdit::~ParameterEdit()
{
	Toolbox::MemoryClean(m_autoComplete);
}
