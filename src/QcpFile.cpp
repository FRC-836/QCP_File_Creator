#include "QcpFile.h"

//--------------------------------------------------
//static member variables
//--------------------------------------------------
int QcpFile::m_defaultFileNumber = 1;

//--------------------------------------------------
//private functions
//--------------------------------------------------
void QcpFile::init(const QString& name, const QString& location,
                   const QVector<QcpGroup>& groups, const QString& comment)
{
  //handle blank name
  QString realName;
  if (std::all_of(name.toStdString().begin(), name.toStdString().end(), std::isspace))
  {
    realName = "QcpFile" + std::to_string(m_defaultFileNumber);
    m_defaultFileNumber++;
  } //end  if (std::all_of(name.toStdString().begin(), name.toStdString().end(), std::isspace))
  else
  {
    realName = name;
  }

  //handle blank file location
  QString realLocation;
  if (std::all_of(location.toStdString().begin(), location.toStdString().end(),
                  std::std::isspace))
  {
    realLocation = QDir::homePath();
  } //end  if (std::all_of(location.toStdString().begin(), location.toStdString().end(),
  else
  {
    //only check if the location is empty, setLocation checks for validity of path
    realLocation = location;
  } //end  else

  //set values
  setName(name);
}
int QcpGroup::findGroup(const QString& name) const
{
  bool found = false;
  int index = 0;
  while (index < m_groups.size() && !found)
  {
    if (m_groups[index].getName() == name)
    {
      found = true;
    } //end  if (m_groups[index].getName() == name)
    else
    {
      index++;
    } //end  else
  } //end  while (index < m_groups.size() && !found)
  return (found ? index : -1);
}

//--------------------------------------------------
//constructors
//--------------------------------------------------
QcpFile::QcpFile()
{
  init("", "", {}, "");
}
QcpFile::QcpFile(const QString& name, const QString& location)
{
  init(name, location, {}, "");
}
QcpFile::QcpFile(const QString& name, const QString& location,
                 const QVector<QcpGroup>& groups, const QString& comment)
{
  init(name, location, groups, comment);
}

//--------------------------------------------------
//public functions
//--------------------------------------------------
size_t QcpFile::size() const
{
  return m_groups.size();
}
QVector<QVector<QString>> QcpFile::fileText() const
{
  QVector<QVector<QString>> groupTexts; //used to store each group's file text

  //handle blank comment
  if (std::all_of(m_comment.toStdString().begin(), m_comment.toStdString.end(),
                  std::isspace))
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << "Comment was left blank for " << m_name.toStdString()
                << " file, providing a default one" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    groupTexts.push_back((m_name + " file"));
  } //end  if (std::all_of(m_comment.toStdString().begin(), m_comment.toStdString.end(),
  else
  {
    groupTexts.push_back(m_comment);
  } //end  else

  //push back each groups file text
  for (QcpGroup group : m_groups)
  {
    groupTexts.push_back(group.fileText());
  } //end  for (QcpGroup group : m_groups)
}
bool QcpFile::addGroup(const QcpGroup& toAdd)
{
  int foundAt = findGroup(toAdd.getName());

  if (foundAt == -1)
  {
    //not found, okay to add
    m_groups.push_back(toAdd);
    return true;
  } //end  if (foundAt == -1)
  else
  {
    //found, can't add
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR:Can't add group " << toAdd.getName().toStdString() << "to file "
                << m_name.toStdString() << " because it already exists" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    return false;
  } //end  else
}
void QcpFile::removeGroup(int index)
{
  if (index <0 || index >= m_groups.size())
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "No Group at index " + std::to_string(index) << "in group "
                << m_name.toStdString() << " to remove" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  if (index <0 || index >= m_groups.size())
  else
  {
    m_groups.erase(m_groups.begin() + index);
  } //end  else
}
void QcpFile::removeGroup(const QString& toRemoveName)
{
  int foundAt = findGroup(toRemoveName);

  if (foundAt != -1)
  {
    m_groups.erase(m_groups.begin() + foundAt);
  } //end  if (foundAt != -1)
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    {
      std::cout << "WARNING: cannot remove group " << toRemoveName.toStdString()
                << " from file " << m_name.toStdString() << " because it doesn't exist"
                << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
  } //end  else
}
void QcpFile::clearGroups()
{
  m_groups.clear();
}
QcpGroup& QcpFile::at(const QString& name) const
{
  int foundAt = findGroup(name);
  if (foundAt == -1)
  {
    throw std::out_of_range("No group with name " + name.toStdString() + " in file "
                            + m_name.toStdString() + "\n");
  }
  return m_groups[foundAt];
}

//--------------------------------------------------
//getters
//--------------------------------------------------
QString QcpFile::getComment() const
{
  return m_comment;
}
QString QcpFile::getName() const
{
  return m_name;
}
QString QcpFile::getLocation() const
{
  return m_location;
}

//--------------------------------------------------
//setters
//--------------------------------------------------
void QcpFile::setComment(const QString& comment)
{
  m_comment = comment;
}
void QcpFile::setName(const QString& name)
{
  if (std::all_of(m_name.toStdString().begin(), m_name.toStdString().end(), std::isspace))
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: attempting to set variable " << m_name.toStdString()
                << "'s name to an empty string. Name will remane unchanged" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end if(std::all_of(m_name.toStdString().begin(),m_name.toStdString().end(),isspace))
  else
  {
    m_name = name;
  } //end  else
}
void QcpFile::setLocation(const QString& location)
{
}

//--------------------------------------------------
//op overloads
//--------------------------------------------------
QcpGroup& QcpFile::operator[](const int index)
{
  if (index < 0 || index >= m_groups.size())
  {
    throw std::out_of_range("No group at index " + std::to_string(index) + " in file "
                            + m_name.toStdString());
  }
  return m_groups[index];
}
QcpGroup& QcpFile::operator[](const QString& name)
{
  return at(name);
}
