#include "Creator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
Creator::Creator()
{
  m_ui = new Ui_creator();
  m_ui->setupUi(this);
}
Creator::~Creator()
{
  delete m_ui;
}
