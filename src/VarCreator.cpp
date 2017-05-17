#include "VarCreator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
VarCreator::VarCreator(QWidget* parent)
  :QWidget(parent)
{
  m_ui = new Ui_VarCreator();
  m_ui->setupUi(this);

  //connections
  connect(m_ui->btnCreateGroup, &QPushButton::clicked,
          this, &VarCreator::createGroupClicked);
  connect(m_ui->btnChangeGroup, &QPushButton::clicked,
          this, &VarCreator::changeGroupClicked);
  connect(m_ui->lneHeaderComment, &QLineEdit::textEdited,
          this, &VarCreator::headerCommentChanged);
  connect(m_ui->lneGroupName, &QLineEdit::textEdited,
          this, &VarCreator::groupNameChanged);
  connect(m_ui->tabSingle, &SingleVarCreator::variableCreated,
          this, &VarCreator::variableCreated);
  connect(m_ui->tabMulti, &MultiVarCreator::variablesCreated,
          this, &VarCreator::variablesCreated);
  connect(m_ui->tabMulti, &MultiVarCreator::valuesChanged,
          this, &VarCreator::valuesChangedHandle);
  connect(m_ui->tabSingle, &SingleVarCreator::valuesChanged,
          this, &VarCreator::valuesChangedHandle);
  connect(m_ui->tabMulti, &MultiVarCreator::constRequest,
          this, &VarCreator::constRequestHandle);
  connect(m_ui->tabSingle, &SingleVarCreator::constRequest,
          this, &VarCreator::constRequestHandle);
} //end VarCreator::VarCreator(QWidget* parent)
VarCreator::~VarCreator()
{
  delete m_ui;

  //debug purposes
  std::cout << "deleting var creator" << std::endl;
} //end VarCreator::~VarCreator()


//--------------------------------------------------
//public slots
//--------------------------------------------------
void VarCreator::createGroupClicked()
{
}
void VarCreator::changeGroupClicked()
{
}
void VarCreator::headerCommentChanged(const QString& newText)
{
}
void VarCreator::groupNameChanged(const QString& newText)
{
}
void VarCreator::variableCreated(const QcpVariable& variable)
{
}
void VarCreator::variablesCreated(const std::vector<QcpVariable> variables)
{
}
void VarCreator::changeGroup(const QcpGroup& newGroup)
{
}
void VarCreator::valuesChangedHandle()
{
}
void VarCreator::constRequestHandle(const QString& varName, QcpVariable& variable)
{
}
