#include "NewDialog.h"

//--------------------------------------------------
//cconstructors
//--------------------------------------------------
NewDialog::NewDialog(QWidget* parent)
  :QWidget(parent)
{
  m_ui = new Ui_NewDialog();
  m_ui->setupUi(this);

  //connections
  connect(m_ui->btnBrowse, &QPushButton::clicked, this, &NewDialog::browseButtonClicked);
  connect(m_ui->btnCreate, &QPushButton::clicked, this, &NewDialog::createButtonClicked);
  connect(m_ui->btnCancel, &QPushButton::clicked, this, &NewDialog::cancelButtonClicked);
  connect(m_ui->lneName, &QLineEdit::textEdited, this, &NewDialog::nameTextChanged);
  connect(m_ui->lneLocation, &QLineEdit::textEdited, this, &NewDialog::locationTextChanged);
  connect(m_ui->cmbProjectType, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
          this, &NewDialog::projectTypeChanged);
} //end NewDialog::NewDialog(QWidget* parent)

NewDialog::~NewDialog()
{
  delete m_ui;
} //end NewDialog::~NewDialog()


//--------------------------------------------------
//public slots
//--------------------------------------------------
void NewDialog::browseButtonClicked()
{
}
void NewDialog::createButtonClicked()
{
}
void NewDialog::cancelButtonClicked()
{
}
void NewDialog::nameTextChanged()
{
}
void NewDialog::locationTextChanged()
{
}
void NewDialog::projectTypeChanged()
{
}
