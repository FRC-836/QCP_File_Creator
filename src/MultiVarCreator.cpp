#include "MultiVarCreator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
MultiVarCreator::MultiVarCreator(QWidget* parent)
  : QWidget(parent)
{
  m_ui = new Ui_MultiVarCreator();
  m_ui->setupUi(this);
} //end MultiVarCreator::MultiVarCreator(QWidget* parent)

MultiVarCreator::~MultiVarCreator()
{
  delete m_ui;
} //end MultiVarCreator::~MultiVarCreator()
