#include "NewDialog.h"

//--------------------------------------------------
//cconstructors
//--------------------------------------------------
NewDialog::NewDialog(QWidget* parent)
  :QWidget(parent)
{
  m_ui = new Ui_NewDialog();
  m_ui->setupUi(this);
} //end NewDialog::NewDialog(QWidget* parent)

NewDialog::~NewDialog()
{
  delete m_ui;
} //end NewDialog::~NewDialog()
