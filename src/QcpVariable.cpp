#include "QcpVariable.h"

//--------------------------------------------------
//enum related stuff
//--------------------------------------------------
const QVector<std::string> QcpVariable::typeStr
{
  "Double",
  "Array of Doubles"
};
std::string QcpVariable::typeToStr(Type toConvert)
{
  return typeStr[static_cast<int>(toConvert)];
}
QcpVariable::Type QcpVariable::strToType(const std::string& toConvert)
{
  auto foundAt = std::find(typeStr.begin(), typeStr.end(), toConvert);
  if (foundAt != typeStr.end())
  {
    return static_cast<Type>(foundAt - typeStr.begin());
  } //end  if (foundAt != typeStr.end())
  else
  {
    throw std::out_of_range("No type " + toConvert + " is supported by this application");
  } //end  else
}
std::ostream& operator<<(std::ostream& os, const QcpVariable::Type& type)
{
  std::cout << QcpVariable::typeStr[static_cast<int>(type)];
}

//--------------------------------------------------
//static variables
//--------------------------------------------------
int QcpVariable::m_defaultVarNum = 1;

//--------------------------------------------------
//private functions
//--------------------------------------------------
QString QcpVariable::doubleText() const
{
  return QString(std::to_string(m_value.value<double>()).c_str());
} //end QString QcpVariable::doubleText()
QString QcpVariable::doubleArrayText() const
{
  std::stringstream ss;

  QVector<double> vals = m_value.value<QVector<double>>();

  //write all the elements to the stream
  for (double val : vals)
  {
    ss << std::to_string(val);

    //only write comma if the element is not the last one
    if (val != vals[vals.size() - 1])
    {
      ss << ", ";
    } //end  if (val != vals[vals.size() - 1])
  } //end  for (double val : vals)

  return QString(ss.str().c_str());
} //end QString QcpVariable::doubleArrayText()
void QcpVariable::errorConverting() const
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  {
    std::cout << "ERROR: typing information for variable " << m_name.toStdString()
              << " has been corrupted, can't convert to file text" << std::endl
              << "Returning blank string instead of file text" << std::endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
} //end void QcpVariable::errorConverting(const QString& name)

//--------------------------------------------------
//constructors
//--------------------------------------------------
QcpVariable::QcpVariable()
{
  init("", Type::DOUBLE, 0.0);
} //end QcpVariable::QcpVariable()
QcpVariable::QcpVariable(const QString& name)
{
  init(name, Type::DOUBLE, 0.0);
} //end QcpVariable::QcpVariable(const QString& name)
QcpVariable::QcpVariable(const QcpVariable& toCopy)
{
  init(toCopy.m_name, toCopy.m_type, toCopy.m_value);
} //end QcpVariable::QcpVariable(const QcpVariable& toCopy)
QcpVariable::~QcpVariable()
{
  //does nothing
} //end QcpVariable::~QcpVariable()

//--------------------------------------------------
//public functions
//--------------------------------------------------
QString QcpVariable::fileText() const
{
  std::stringstream ss;
  ss << m_name.toStdString() << ", ";

  //call the proper text conversion function based on type
  switch(m_type)
  {
    case Type::DOUBLE:
      //check that conversion is possible, if not error out:
      if (m_value.canConvert<double>())
      {
        ss << doubleText().toStdString();
      } //end  if (m_value.canConvert<double>())
      else
      {
        errorConverting();
        return "";
      } //end  else
      break; //end  case Type::DOUBLE:

    case Type::DOUBLE_ARRAY:
      //check that conversion is possible, if not error out
      if (m_value.canConvert<QVector<double>>())
      {
        ss << doubleArrayText().toStdString();
      } //end  if (m_value.canConvert<QVector<double>>())
      else
      {
        errorConverting();
        return "";
      } //end  else
      break; //end  case Type::DOUBLE_ARRAY:
  } //end  switch(m_type)

  //add newline because variable is done being converted
  ss << std::endl;

  return QString(ss.str().c_str());
} //end QString QcpVariable::fileText() const

//--------------------------------------------------
//getters
//--------------------------------------------------
QcpVariable::Type QcpVariable::getType() const
{
  return m_type;
} //end QcpVariable::Type QcpVariable::getType() const
QString QcpVariable::getName() const
{
  return m_name;
} //end QString QcpVariable::getName() const

//--------------------------------------------------
//setters
//--------------------------------------------------
void QcpVariable::setName(const QString& name)
{
  std::string testName = name.toStdString();
  if (!std::all_of(testName.begin(), testName.end(),
                   isspace))
  {
    m_name = name;
  } //end  if (!std::all_of(name.toStdString().begin(), name.toStdString().end(), isspace))
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: attempting to set variable " << m_name.toStdString()
                << "'s name to an empty string. Name will remane unchanged" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  else
} //end void QcpVariable::setName(const QString& name)

//--------------------------------------------------
//op overloads
//--------------------------------------------------
QcpVariable& QcpVariable::operator=(const QcpVariable& toCopy)
{
  m_name = toCopy.m_name;
  m_value = toCopy.m_value;
  m_type = toCopy.m_type;
} //end QcpVariable& QcpVariable::operator=(const QcpVariable& toCopy)
QcpVariable& QcpVariable::operator=(double value)
{
  m_type = Type::DOUBLE;
  m_value = value;
} //end QcpVariable& QcpVariable::operator=(double value)
QcpVariable& QcpVariable::operator=(const QVector<double>& value)
{
  m_type = Type::DOUBLE_ARRAY;
  m_value = QVariant::fromValue(value);
} //end QcpVariable& QcpVariable::operator=(const QVector<double>& value)
