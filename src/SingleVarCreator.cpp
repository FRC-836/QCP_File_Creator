#include "SingleVarCreator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
SingleVarCreator::SingleVarCreator(QWidget* parent)
  :QWidget(parent)
{
  m_ui = new Ui_SingleVarCreator();
  m_ui->setupUi(this);

  //connections
  connect(m_ui->cmbType,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
          this, &SingleVarCreator::variableTypeChanged);
  connect(m_ui->btnAdd, &QPushButton::clicked,
          this, &SingleVarCreator::addButtonClicked);
  connect(m_ui->btnClear, &QPushButton::clicked,
          this, &SingleVarCreator::clearButtonClicked);
  connect(m_ui->lneName, &QLineEdit::textChanged,
          this, &SingleVarCreator::variableNameChanged);
  connect(m_ui->txtValues, &QTextEdit::textChanged,
          this, &SingleVarCreator::variableValuesChanged);
} //end SingleVarCreator::SingleVarCreator(QWidget* parent)

SingleVarCreator::~SingleVarCreator()
{
  delete m_ui;

  //debug
  std::cout << "deleting single var creator" << std::endl;
} //end SingleVarCreator::~SingleVarCreator()


//--------------------------------------------------
//public slots
//--------------------------------------------------
void SingleVarCreator::variableTypeChanged(int index)
{
}
void SingleVarCreator::addButtonClicked()
{
}
void SingleVarCreator::clearButtonClicked()
{
}
void SingleVarCreator::variableNameChanged(const QString& newText)
{
}
void SingleVarCreator::variableValuesChanged()
{
}
