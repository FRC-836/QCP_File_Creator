#include "Creator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
Creator::Creator()
{
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
