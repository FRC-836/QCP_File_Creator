#include "NewDialog.h"

//constructors
NewDialog::NewDialog(QWidget* parent)
  :QWidget(parent)
{
  m_ui = new Ui_NewDialog();
  m_ui->setupUi(this);
}
NewDialog::~NewDialog()
{
  delete m_ui;
}
