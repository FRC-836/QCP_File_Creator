#include "SingleVarCreator.h"

//constructors
SingleVarCreator::SingleVarCreator(QWidget* parent)
  :QWidget(parent)
{
  m_ui = new Ui_SingleVarCreator();
  m_ui->setupUi(this);
}
SingleVarCreator::~SingleVarCreator()
{
  delete m_ui;
}
