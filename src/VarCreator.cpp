#include "VarCreator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
VarCreator::VarCreator(QWidget* parent)
  :QWidget(parent)
{
  m_ui = new Ui_VarCreator();
  m_ui->setupUi(this);
}
VarCreator::~VarCreator()
{
  delete m_ui;
}
