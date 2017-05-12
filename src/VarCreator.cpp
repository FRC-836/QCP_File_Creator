#include "VarCreator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
VarCreator::VarCreator(QWidget* parent)
  :QWidget(parent)
{
  m_ui = new Ui_VarCreator();
  m_ui->setupUi(this);
} //end VarCreator::VarCreator(QWidget* parent)
VarCreator::~VarCreator()
{
  delete m_ui;
} //end VarCreator::~VarCreator()
