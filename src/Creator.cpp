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
Creator::Creator(std::unique_ptr<Project> project, bool openInEditor)
{
  Q_UNUSED(project);
  Q_UNUSED(openInEditor); //TODO implement this ability

  //assign memeber variables

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
    std::cout << "INFO: Creator: deleting creator" << std::endl;
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
void Creator::createProject(const QString& name, const QString& filePath)
{
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: Creator: recieving command to create project at: "
              << filePath.toStdString() << std::endl;
  }//end  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)

  m_project = std::make_shared<Project>(name, filePath);
}
void Creator::openProject(const QString& filePath, bool openInEditor)
{
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: Creator: recieving command to open project at: "
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
