#include "ConstCreator.h"

ConstCreator::ConstCreator(QWidget* parent)
  : QWidget(parent)
{
  m_ui = new Ui_ConstCreatorDialog();
  m_ui->setupUi(this);
}
ConstCreator::~ConstCreator()
{
  delete m_ui;
}
