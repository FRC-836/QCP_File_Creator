#include "ConstCreator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
ConstCreator::ConstCreator(Creator* caller, QWidget* parent)
  : QWidget(parent)
{
  m_ui = new Ui_ConstCreatorDialog();
  m_ui->setupUi(this);

  //connections
  connect(this, &ConstCreator::newConstant, caller, &Creator::createConst);
  connect(m_ui->btnCreate, &QPushButton::clicked, this, createClicked);
  connect(m_ui->btnCancel, &QPushButton::clicked, this, cancelClicked);
  connect(m_ui->lneName, &QLineEdit::textEdited, this, nameChanged);
  connect(m_ui->lneValue, &QLineEdit::textEdited, this, valueChanged);
} //end ConstCreator::ConstCreator(QWidget* parent)
ConstCreator::~ConstCreator()
{
  delete m_ui;

  //debug
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "deleting const creator" << std::endl;
  }
} //end ConstCreator::~ConstCreator()

//--------------------------------------------------
//public slots
//--------------------------------------------------
void ConstCreator::createClicked()
{
}
void ConstCreator::cancelClicked()
{
}
void ConstCreator::nameChanged(const QString& newText)
{
}
void ConstCreator::valueChanged(const QString& newText)
{
}

