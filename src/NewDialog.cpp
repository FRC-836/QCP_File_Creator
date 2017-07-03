#include "NewDialog.h"

//--------------------------------------------------
//private functions
//--------------------------------------------------
bool NewDialog::isGoodPath(const QString& filePath)
{
  QFileInfo checkExists(filePath);
  return checkExists.exists() && checkExists.isDir();
} //end bool NewDialog::isGoodPath(const QString& filePath)
void NewDialog::normalizePath(QString& path)
{
  QString normalizedPath = ""; //empty path to put chars into
  State curState = State::INIT; //initial state for narmalize path SM

  //TODO spin off in own thread
  for (QChar curChar : path)
  {
    switch(curState)
    {
      case State::INIT:
        normalizedPath += curChar;
        curState = (curChar == '/' || curChar == '\\') ? State::PREV_WAS_SLASH :
                                                         State::PREV_WAS_CHAR;
        break;
      case State::PREV_WAS_CHAR:
        normalizedPath += curChar;
        curState = (curChar == '/' || curChar == '\\') ? State::PREV_WAS_SLASH :
                                                         State::PREV_WAS_CHAR;
        break;
      case State::PREV_WAS_SLASH:
        if (curChar != '/' && curChar != '\\')
        {
          normalizedPath += curChar;
          curState = State::PREV_WAS_CHAR;
        } //end  if (prevChar != '/' && prevChar != '\\')
        else
        {
          curState == State::PREV_WAS_SLASH;
        } //end  else
        break;
    } //end  switch(curState)
  } //end  for (QChar curChar : path)

  //apply normalized path
  path = normalizedPath;
} //end void normalizePath(QString& path)


//--------------------------------------------------
//cconstructors
//--------------------------------------------------
NewDialog::NewDialog(QWidget* parent)
  :QWidget(parent)
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
  connect(this, &NewDialog::newProject, &Creator::createProject);
} //end NewDialog::NewDialog(QWidget* parent)

NewDialog::~NewDialog()
{
  delete m_ui;

  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "deleting new dialog" << std::endl;
  }
} //end NewDialog::~NewDialog()


//--------------------------------------------------
//public slots
//--------------------------------------------------
void NewDialog::browseButtonClicked()
{
  QString filePath = QFileDialog::getExistingDirectory(this,
                                                       "Choose location for project",
                                                       QDir::homePath(),
                                                       QFileDialog::ShowDirsOnly |
                                                       QFileDialog::DontResolveSymlinks);

  if (isGoodPath(filePath))
  {
    m_ui->lneLocation->setText(filePath);
  } //end  if (isGoodPath(filePath))
} //end void NewDialog::browseButtonClicked()
void NewDialog::createButtonClicked()
{
  //make sure both location and name are valid
  if (!isGoodPath(m_ui->lneLocation->text()))
  {
    if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << "empty path can't be used" << std::endl;
    } //end  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
    return;
  } //end  if (!isGoodPath(m_ui->lneLocation->text()))
  else if (m_ui->lneName->text().size() == 0)
  {
    if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << "can't use an empty name" << std::endl;
    } //end  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
    return;
  } //end  else if (m_ui->lneName->text().size() == 0)

  QString fullPath = m_ui->lneLocation->text() + '/' + m_ui->lneName->text() +
                     Project::PROJECT_FILE_EXTENSION;
  normalizePath(fullPath);

  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "Emitting creation of file at: " << fullPath.toStdString() << std::endl;
  } //end  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)

  emit newProject(fullPath);
  this->close();
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
  if (newText.size() != 0)
  {
    if (!std::isalnum(newText.at(newText.size() - 1).toLatin1()))
    {
      QString tempText = m_ui->lneName->text();
      tempText.chop(1);
      m_ui->lneName->setText(tempText);
    } //end  if (!std::isalnum(newText.at(newText.size() - 1).toLatin1()))
  } //end  if (newText.size() != 0)
} //end void NewDialog::nameTextChanged(const QString& newText)
void NewDialog::locationTextChanged()
{
  QString newText = m_ui->lneLocation->text();
  if (!isGoodPath(newText))
  {
    m_ui->lneLocation->setText("");

    //TODO replace with dialog box
    if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << "clearing text because its not a good path" << std::endl;
    }
  } //end  if (!isGoodPath(newText))
} //end void NewDialog::locationTextChanged(const QString& newText)
void NewDialog::projectTypeChanged()
{
  //do nothing because there is currently only one type of project
} //end void NewDialog::projectTypeChanged()
