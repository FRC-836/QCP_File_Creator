#include "ConstCreator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
ConstCreator::ConstCreator(QWidget* parent)
  : QWidget(parent)
{
  m_ui = new Ui_ConstCreatorDialog();
  m_ui->setupUi(this);
} //end ConstCreator::ConstCreator(QWidget* parent)
ConstCreator::~ConstCreator()
{
  delete m_ui;
} //end ConstCreator::~ConstCreator()
