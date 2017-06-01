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
  close();
}
void ConstCreator::nameChanged(const QString& newText)
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
}
void ConstCreator::valueChanged(const QString& newText)
{
}

