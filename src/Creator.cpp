#include "Creator.h"

//--------------------------------------------------
//private functions
//--------------------------------------------------
void Creator::loadProject()
{
}

//--------------------------------------------------
//constructors
//--------------------------------------------------
Creator::Creator(std::unique_ptr<Project> project)
{
  //assign memeber variables
  if (project == nullptr)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << "INFO: Creator: Creating new project" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  } //end  if (project == nullptr)

  //setup UI
  m_ui = new Ui_creator();
  m_ui->setupUi(this);

  //connections
  connect(this, &Creator::groupChangeRequest, m_ui->varCreator, &VarCreator::changeGroup);
  connect(m_ui->varCreator, &VarCreator::constRequest, this, &Creator::constRequestHandler);
  connect(m_ui->btnNewConst, &QPushButton::clicked, this, &Creator::newConstClicked);
  connect(m_ui->btnSave, &QPushButton::clicked, this, &Creator::saveClicked);
  connect(m_ui->btnExport, &QPushButton::clicked, this, &Creator::exportClicked);
  connect(m_ui->cmbGroup, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
          this, &Creator::groupBoxValueChanged);
  connect(m_ui->cmbFile, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
          this, &Creator::fileBoxValueChanged);
  connect(m_ui->treVarExplorer, &QTreeWidget::itemDoubleClicked,
          this, &Creator::varExplorerClicked);
  connect(m_ui->treProjExplorer, &QTreeWidget::itemDoubleClicked,
          this, &Creator::projectItemClicked);
  connect(m_ui->lstConstants, &QListWidget::itemDoubleClicked,
          this, &Creator::constItemClicked);
} //end Creator::Creator()
Creator::~Creator()
{
  delete m_ui;

  //debug
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "deleting creator" << std::endl;
  }
} //end Creator::~Creator()

//--------------------------------------------------
//public slots
//--------------------------------------------------
void Creator::constRequestHandler(const QString& constName, QcpVariable& variable)
{
}
void Creator::newConstClicked()
{
}
void Creator::saveClicked()
{
}
void Creator::exportClicked()
{
}
void Creator::groupBoxValueChanged(int index)
{
}
void Creator::fileBoxValueChanged(int index)
{
}
void Creator::varExplorerClicked(QTreeWidgetItem* item)
{
}
void Creator::projectItemClicked(QTreeWidgetItem* item)
{
}
void Creator::constItemClicked(QListWidgetItem* item)
{
}
void Creator::createConst(const QcpVariable& value)
{
}
void Creator::createProject(const QString& filePath)
{
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "recieving command to create project at: "
              << filePath.toStdString() << std::endl;
  }//end  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)

  QFile projectFile(filePath);
  if (!projectFile.open(QIODevice::Text | QIODevice::ReadWrite))
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: Manager: Couldn't create file " << filePath.toStdString()
                << ". Please ensure the permissions are correct." << std::endl
                << "Exiting application." << std::endl;
    }
    exit(-1);
  } //end  if (!projectFile.open(QIODevice::Text | QIODevice::ReadWrite))
}
void Creator::openProject(const QString& filePath, bool openInEditor)
{
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "recieving command to open project at: "
              << filePath.toStdString() << " ";
    if (openInEditor)
    {
      std::cout << "in editor mode";
    } //end  if (openInEditor)
    else
    {
      std::cout << "in normal mode";
    } //end  else
    std::cout << std::endl;
  } //end  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
