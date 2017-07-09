#include "ConstCreator.h"

//--------------------------------------------------
//private functions
//--------------------------------------------------
std::pair<bool, double> ConstCreator::isValidDouble()
{
  bool ok;
  double val = m_ui->lneValue->text().toDouble(&ok);
  if (ok)
  {
    return {true, val};
  }
  else
  {
    return {false, 0.0};
  }
}
std::pair<bool, QVector<double>> ConstCreator::isValidDoubleArr()
{
  QVector<double> values;
  //iterate over every value of the comma seperated list
  for (auto value : m_ui->lneValue->text().split(QChar(',')))
  {
    bool ok;
    double valConverted = value.toDouble(&ok);
    if (ok)
    {
      values.push_back(std::stod(value.toStdString()));
    }
    else
    {
      return {false, {}};
    }
  } //end  for (auto value : m_ui->lneValue->text().split(QChar(',')))
  return {true, values};
}

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
  connect(m_ui->btnCreate, &QPushButton::clicked, this, &ConstCreator::createClicked);
  connect(m_ui->btnCancel, &QPushButton::clicked, this, &ConstCreator::cancelClicked);
  connect(m_ui->lneName, &QLineEdit::textEdited, this, &ConstCreator::nameChanged);
  connect(m_ui->lneValue, &QLineEdit::textEdited, this, &ConstCreator::valueChanged);
  connect(m_ui->cmbType, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
          this, &ConstCreator::typeChanged);
} //end ConstCreator::ConstCreator(QWidget* parent)
ConstCreator::~ConstCreator()
{
  delete m_ui;

  //debug
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: ConstCreator: deleting const creator" << std::endl;
  }
} //end ConstCreator::~ConstCreator()

//--------------------------------------------------
//public slots
//--------------------------------------------------
void ConstCreator::createClicked()
{
  QcpVariable constant(QString("name"));

  //check text sizes to ensure they are nonzero
  if (m_ui->lneName->text().size() == 0)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: ConstCreator: Cannot create a constant with a blank name." << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    return;
  } //end  if (m_ui->lneName->size() == 0)
  if (m_ui->lneValue->text().size() == 0)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: ConstCreator: Cannot create a constant with a blank value." << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    return;
  } //end  if (m_ui->lneName->size() == 0)

  //check that value is valid for the given cconstant type
  switch(QcpVariable::strToType(m_ui->cmbType->currentText().toStdString()))
  {
    case QcpVariable::Type::DOUBLE_ARRAY:
    {
      auto result = isValidDoubleArr();
      if (result.first)
      {
        //value text was valid
        constant = QcpVariable(m_ui->lneName->text(), QcpVariable::Type::DOUBLE_ARRAY,
                               result.second);
      } //end  if (result.first)
      else
      {
        //value text invalid
        if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
        {
          std::cout << "ERROR: ConstCreator: Value is invalid for the selected type. "
                    << "Please use only numbers that are seperated by commas."
                    << std::endl;
        } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
        return;
      } //end  else
      break;
    } //end  case QcpVariable::Type::DOUBLE_ARRAY:
    case QcpVariable::Type::DOUBLE:
    {
      auto result = isValidDouble();
      if (result.first)
      {
        constant = QcpVariable(m_ui->lneName->text(), QcpVariable::Type::DOUBLE,
                                result.second);
      } //end  if (result.first)
      else
      {
        if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
        {
          std::cout << "ERROR: ConstCreator: Value is invalid for the selected type. "
                    << "Please enter a number for the value." << std::endl;
        } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
        return;
      } //end  else
      break;
    } //end  case QcpVariable::Type::DOUBLE:
  } //end  switch(QcpVariable::strToType(m_ui->cmbType->currentText()))

  //all checks passed
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: ConstCreator: emitting newConstant singal" << std::endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  emit newConstant(constant);
  //close(); TEST uncomment when testing is done
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
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
      {
        std::cout << "WARNING: ConstCreator: Only alphanumeric characters are allowed in constant names."
                  << " Not updating constant name." << std::endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
      QString tempText = m_ui->lneName->text();
      tempText.chop(1);
      m_ui->lneName->setText(tempText);
    } //end  if (!std::isalnum(newText.at(newText.size() - 1).toLatin1()))
  }
}
void ConstCreator::valueChanged(const QString& newText)
{
  //intentionally left blank
}
void ConstCreator::typeChanged()
{
  //intentionally left blank
}
