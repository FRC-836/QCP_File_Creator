#include "NewDialog.h"

//--------------------------------------------------
//cconstructors
//--------------------------------------------------
NewDialog::NewDialog(std::shared_ptr<Manager> manager, QWidget* parent)
  :m_manager(manager), QWidget(parent)
{
  //setup UI
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
  connect(this, &NewDialog::newProject, m_manager.get(), &Manager::createProject);
} //end NewDialog::NewDialog(QWidget* parent)

NewDialog::~NewDialog()
{
  delete m_ui;

  //debug
  std::cout << "deleting new dialog" << std::endl;
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
  if (parentWidget() != nullptr)
  {
    parentWidget()->show();
  }
  this->close();
}
void NewDialog::nameTextChanged(const QString& newText)
{
}
void NewDialog::locationTextChanged(const QString& newText)
{
}
void NewDialog::projectTypeChanged()
{
}
