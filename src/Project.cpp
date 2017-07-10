#include "Project.h"

//--------------------------------------------------
//static member variables
//--------------------------------------------------
int Project::m_defaultNameNum = 1;

//--------------------------------------------------
//private functions
//--------------------------------------------------
void Project::init(const QString& name, const QString& location,
                   const QVector<QcpFile>& files)
{
  //handle blank names
  QString realName;
  if (std::all_of(name.toStdString().begin(), name.toStdString().end(), isspace))
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    {
      std::cout << "WARNING: Project: Default name being used for Qcp Project because one wasn't provided"
                << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    realName = "QcpProject" + QString::fromStdString(std::to_string(m_defaultNameNum));
    m_defaultNameNum++;
  } //end  if (std::all_of(name.toStdString().begin(), name.toStdString().end(), isspace))
  else
  {
    realName = name;
  } //end  else

  //handle locations that don't exist
  QString realLocation = QDir::homePath();
  QFileInfo checkExists(location);
  if (std::all_of(location.toStdString().begin(), location.toStdString().end(),
                  isspace))
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: Projeect: Blank locaiton provided to project " << m_name.toStdString()
                << ". File will be saved in " << QDir::homePath().toStdString()
                << " by default." << std::endl;
    }
  } //end  if (std::all_of(location.toStdString().begin(), location.toStdString().end(),
  else
  {
    if (checkExists.exists() && checkExists.isDir())
    {
      realLocation = location;
    } //end  if (checkExists.exists() && checkExists.isDir())
    else
    {
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
      {
        std::cout << "ERROR: Project: Invalid file location " << location.toStdString()
                  << " provided for project " << m_name.toStdString() << "." << std::endl
                  << "\tProject will be saved in " << QDir::homePath().toStdString()
                  << " instead." << std::endl;
      }
    } //end  else
  } //end  else

  //set all values
  setName(realName);
  setLocation(realLocation);
  for (QcpFile file : files)
  {
    addFile(file);
  } //end  for (QcpFile file : files)
}
int Project::findFile(const QString& name) const
{
  bool found = false;
  int index = 0;
  while (index < m_files.size() && !found)
  {
    if (m_files[index].getName() == name)
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
//static constants
//--------------------------------------------------
const QString Project::PROJECT_FILE_EXTENSION = ".qcprj";
const QString Project::QCP_FILE_FILE_EXTENSION = ".qcprf";
const QString Project::GROUP_FILE_EXTENSION = ".qcprg";

//--------------------------------------------------
//constructors
//--------------------------------------------------
Project::Project()
{
  init("", "", {});
}
Project::Project(const QString& name, const QString& location)
{
  init(name, location, {});
}
Project::Project(const QString& name, const QString& location,
                 const QVector<QcpFile>& files)
{
  init(name, location, files);
}

//--------------------------------------------------
//public functions
//--------------------------------------------------
void Project::addFile(const QcpFile& file)
{
  int foundAt = findFile(file.getName());
  if (foundAt != -1)
  {
    //file exists, can't add it again
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: Project: cannot add file " << file.getName().toStdString()
                << " to project " << m_name.toStdString() << " because it already exists"
                << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  if (foundAt != -1)
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << "INFO: Project: adding file " << file.getName().toStdString() << " to project "
                << m_name.toStdString() << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    m_files.push_back(file);
  } //end  else
}
QcpFile Project::removeFile(const QString& name)
{
  int foundAt = findFile(name);
  if (foundAt != -1)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      std::cout << "INFO: Project: removing file " << m_files[foundAt].getName().toStdString()
                << " from project " << m_name.toStdString() << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    m_files.erase(m_files.begin() + foundAt);
  } //end  if (foundAt != -1)
  else
  {
    //file not found, inform user if debug level is high enough
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    {
      std::cout << "WARNING: Project: << cannot remove file " << name.toStdString()
                << "from project " << m_name.toStdString()
                << " because it doesn't exist." << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
  } //end  else
}
void Project::clearFiles()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: Project: Clearing all files from project " << m_name.toStdString()
              << std::endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  m_files.clear();
}
QcpFile& Project::at(const QString& name)
{
  int foundAt = findFile(name);
  if (foundAt == -1)
  {
    throw std::out_of_range("File " + name.toStdString() + " doesn't exist in project " +
                            m_name.toStdString());
  } //end  if (foundAt == -1)
  return m_files[foundAt];
}

//--------------------------------------------------
//getters
//--------------------------------------------------
QString Project::getName() const
{
  return m_name;
}
QString Project::getLocation() const
{
  return m_location;
}

//--------------------------------------------------
//setters
//--------------------------------------------------
void Project::setName(const QString& name)
{
  //handle blank names
  if (std::all_of(name.toStdString().begin(), name.toStdString().end(), isspace))
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: Project: Attempt to set project " << m_name.toStdString()
                << " to an empty string. Name not being updated" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  if (std::all_of(name.toStdString().begin(), name.toStdString().end(), isspace))
  else
  {
    m_name = name;
  } //end  else
}
void Project::setLocation(const QString& location)
{
  //handle file locations that don't exist
  QFileInfo fileExists(location);
  if (fileExists.exists() && fileExists.isDir())
  {
    m_location = location;
  } //end  if (fileExists.exists() && fileExists.isDir())
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: Project: Attempt to set project " << m_name.toStdString()
                << "'s locaiton to" << location.toStdString()
                << " failed because that location doesn't exist" << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  else
}

//--------------------------------------------------
//op overloads
//--------------------------------------------------
QcpFile& Project::operator[](const QString& name)
{
  return at(name);
}
