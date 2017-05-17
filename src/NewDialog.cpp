#include "NewDialog.h"

//--------------------------------------------------
//private functions
//--------------------------------------------------
bool NewDialog::isGoodPath(const QString& filePath)
{
  return false;
}


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
  connect(m_ui->lneLocation, &QLineEdit::editingFinished,
          this, &NewDialog::locationTextChanged);
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
} //end void NewDialog::browseButtonClicked()
void NewDialog::createButtonClicked()
{
} //end void NewDialog::createButtonClicked()
void NewDialog::cancelButtonClicked()
{
  if (parentWidget() != nullptr)
  {
    parentWidget()->show();
  } //end  if (parentWidget() != nullptr)
  this->close();
} //end void NewDialog::cancelButtonClicked()
void NewDialog::nameTextChanged(const QString& newText)
{
  //allow the name if the newest character is a letter or number
  if (!std::isalnum(newText.at(newText.size() - 1).toLatin1()))
  {
    std::cout << "invalid character entered into name text field" << std::endl;
    QString tempText = m_ui->lneName->text();
    tempText.chop(1);
    m_ui->lneName->setText(tempText);
  }
} //end void NewDialog::nameTextChanged(const QString& newText)
void NewDialog::locationTextChanged()
{
  QString newText = m_ui->lneLocation->text();
  if (!isGoodPath(newText))
  {
    m_ui->lneLocation->setText("");

    //TODO replace with dialog box
    std::cout << "clearing text because its not a good path" << std::endl;
  } //end  if (!isGoodPath(newText))
} //end void NewDialog::locationTextChanged(const QString& newText)
void NewDialog::projectTypeChanged()
{
  //do nothing because there is currently only one type of project
} //end void NewDialog::projectTypeChanged()
