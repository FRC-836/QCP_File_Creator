#include "SingleVarCreator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
SingleVarCreator::SingleVarCreator(QWidget* parent)
  :QWidget(parent)
{
  m_ui = new Ui_SingleVarCreator();
  m_ui->setupUi(this);
} //end SingleVarCreator::SingleVarCreator(QWidget* parent)

SingleVarCreator::~SingleVarCreator()
{
  delete m_ui;
} //end SingleVarCreator::~SingleVarCreator()
