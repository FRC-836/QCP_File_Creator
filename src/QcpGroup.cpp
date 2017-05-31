#include "QcpGroup.h"

//--------------------------------------------------
//static member variables
//--------------------------------------------------
int QcpGroup::m_defaultGroupNum = 1;

//--------------------------------------------------
//private functions
//--------------------------------------------------
void QcpGroup::init(const QString& name, const QVector<QcpVariable>& vars,
                    const QString& comment)
{
  //correct for name blanking
  QString realName;
  if (std::all_of(name.toStdString().begin(), name.toStdString().end(),
                  std::isspace))
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << "dfault group name being used due to empty name" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    realName = "Group";
    realName += QString::fromStdString(std::to_string(m_defaultGroupNum));
    m_defaultGroupNum++;
  } //end  if (std::all_of(name.toStdString().begin(), name.toStdString().end(), isspace))
  else
  {
    realName = name;
  } //end  else

  setName(realName);
  setComment(comment);

}
int QcpGroup::findVar(const QString& name) const
{
  bool found = false;
  int index = 0;
  while (index < m_vars.size() && !found)
  {
    if (m_vars[index].getName() == name)
    {
      found = true;
    } //end  if (m_vars[index].getName() == name)
    else
    {
      index++;
    } //end  else
  } //end  while (index < m_vars.size() && !found)
  return (found ? index : -1);
}

//--------------------------------------------------
//constructors
//--------------------------------------------------
QcpGroup::QcpGroup()
{
  init("", {}, "");
}
QcpGroup::QcpGroup(const QString& name, const QVector<QcpVariable>& vars)
{
  init(name, vars, "");
}
QcpGroup::QcpGroup(const QString& name, const QVector<QcpVariable>& vars,
                   const QString& comment)
{
  init(name, vars, comment);
}

//--------------------------------------------------
//public functions
//--------------------------------------------------
size_t QcpGroup::size() const
{
  return m_vars.size();
}
QVector<QString> QcpGroup::fileText() const
{
  QVector<QString> varsText; //stores each variables file writeable text

  //add the comment to the file text, if it is blank use a default comment
  if (m_comment.toStdString().begin(), m_comment.toStdString().end(),
      std::isspace)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << "No comment provided for group " << m_name.toStdString()
                << ", provideing default comment" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    varsText.push_back("#" + m_name + " Group Variables\n");
  } //end  if (m_comment.toStdString().begin(), m_comment.toStdString().end(), isspace)
  else
  {
    varsText.push_back(m_comment);
  } //end  else

  //iterate over each variable and grab its file text
  for (QcpVariable var : m_vars)
  {
    varsText.push_back(var.fileText());
  } //end  for (auto& var : m_vars)

  //add a blank line to the end of the group
  varsText.push_back("\n");

  return varsText;
}
bool QcpGroup::addVar(const QcpVariable& toAdd)
{
  //only add the variable if the name doesn't already exist
  if (findVar(toAdd.getName()) != -1)
  {
    m_vars.push_back(toAdd);
    return true;
  } //end  if (!findVar(toAdd.getName()))
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: cannot add variable " << toAdd.getName().toStdString()
                << " because variable with that name already exists" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    return false;
  } //end  else
}
void QcpGroup::removeVar(int index)
{
  if (index < 0 || index >= m_vars.size())
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    {
      std::cout << "WARNING: No variable found at index " << index << " in group "
                << m_name.toStdString() << " to remove" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
  } //end  if (index < 0 || index >= m_vars.size())
  else
  {
    m_vars.erase(m_vars.begin() + index);
  } //end  else
}
void QcpGroup::removeVar(const QString& toRemoveName)
{
  int foundAt = findVar(toRemoveName);
  if (foundAt != -1)
  {
    m_vars.erase(m_vars.begin() + foundAt);
  } //end  if (foundAt != -1)
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    {
      std::cout << "WARNING: cannot remove variable " << toRemoveName.toStdString()
                << " because no variable with that name exists in group "
                << m_name.toStdString() << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
  } //end  else
}
void QcpGroup::clearVars()
{
  m_vars.clear();
}

//--------------------------------------------------
//getters
//--------------------------------------------------
QString QcpGroup::getComment() const
{
  return m_comment;
}
QString QcpGroup::getName() const
{
  return m_name;
}

//--------------------------------------------------
//setters
//--------------------------------------------------
void QcpGroup::setComment(const QString& comment)
{
  m_comment = comment;

  //add a newline to the comment if it wasn't provided
  if (!m_comment.endsWith('\n'))
  {
     m_comment.append("\n");
  }
}
void QcpGroup::setName(const QString& name)
{
  //ensure the name is not being blanked
  if (!std::all_of(name.toStdString().begin(), name.toStdString().end(),
                   std::isspace))
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
}

//--------------------------------------------------
//op overloads
//--------------------------------------------------
QcpVariable& QcpGroup::operator[](const int index)
{
  if (index < 0 || index > m_vars.size() - 1)
  {
    throw std::out_of_range("No variable at position " + std::to_string(index) +
                            " in group " + m_name.toStdString());
  } //end  if (index < 0 || index > m_vars.size() - 1)
  return m_vars[index];
}
const QcpVariable& QcpGroup::operator[](const int index) const
{
  if (index < 0 || index > m_vars.size() - 1)
  {
    throw std::out_of_range("No variable at position " + std::to_string(index) +
                            " in group " + m_name.toStdString());
  } //end  if (index < 0 || index > m_vars.size() - 1)
  return m_vars[index];
}
QcpVariable& QcpGroup::operator[](const QString& name)
{
  int foundAt = findVar(name);
  if (foundAt == -1)
  {
    //not found
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << name.toStdString() << " not found in group " << m_name.toStdString()
                << ", adding it" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    m_vars.push_back(QcpVariable(name));
  } //end  if (foundAt == -1)
  else
  {
    return m_vars[foundAt];
  } //end  else
}
