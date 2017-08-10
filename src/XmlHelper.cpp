#include "XmlHelper.h"

//--------------------------------------------------
//Qcp Project Visitor
//--------------------------------------------------
QcpProjectVisitor::QcpProjectVisitor(ProjectData_t& data) :
  m_data(data)
{
}
bool QcpProjectVisitor::visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
{
  if (xmlReader->name() == Project::TagsStr[Project::Tags::QCP_PROJECT])
  {
    auto attribs = xmlReader->attributes();
    QString attribName = Project::QcpProject::AttrStr[Project::QcpProject::Attributes::VERSION];
    if (!attribs.hasAttribute(attribName))
    {
      xmlReader->raiseError("Version tag not found on line " + xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(attribName))
    m_version = attribs.value(attribName).toString();
    return true;
  } //end if (xmlReader->name() == Project::TagsStr[Project::Tags::QCP_PROJECT])
  else if (xmlReader->name() == Project::TagsStr[Project::Tags::NAME])
  {
    QString name;
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(name);
    accept(std::move(chars));

    std::get<static_cast<int>(ProjectTuple::NAME)>(m_data) = name;
    return false;
  } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::NAME])
  else if (xmlReader->name() == Project::TagsStr[Project::Tags::PROJECT_ROOT_DIRECTORY])
  {
    QString directory;
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(directory);
    accept(std::move(chars));

    std::get<static_cast<int>(ProjectTuple::ROOT_DIRECTORY)>(m_data) = directory;
    return false;
  } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::PROJECT_ROOT_DIRECTORY])
  else if (xmlReader->name() == Project::TagsStr[Project::Tags::CONSTANT_LIST])
  {
    //nothing to do, move onto next tag
    return true;
  } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::CONSTANT_LIST])
  else if (xmlReader->name() == Project::TagsStr[Project::Tags::FILE_LIST])
  {
    //nothing to do, move onto next tag
    return true;
  } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::FILE_LIST])
  else if (xmlReader->name() == Project::TagsStr[Project::Tags::CONSTANT] ||
           xmlReader->name() == Project::TagsStr[Project::Tags::ARRAY_CONSTANT])
  {
    QcpVariable var;
    std::unique_ptr<VariableVisitor> variable = std::make_unique<VariableVisitor>(var);
    accept(std::move(variable));

    std::get<static_cast<int>(ProjectTuple::CONSTANT_LIST)>(m_data).push_back(var);
    return false;
  } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::CONSTANT]) ||
  else if (xmlReader->name() == Project::TagsStr[Project::Tags::QCP_FILE])
  {
    //get file path
    QString path;
    QString attribName = Project::QcpFile::AttrStr[Project::QcpFile::Attributes::Location];
    std::unique_ptr<NewXmlVisitor> fileGetter = 
      std::make_unique<NewXmlVisitor>(path, attribName);
    accept(std::move(fileGetter));

    //open new xml reader at file path
    QFile file(path);
    std::unique_ptr<QXmlStreamReader> xmlReader =
      std::make_unique<QXmlStreamReader>(&file);

    //handle the new xml file
    FileData_t fileData;
    std::unique_ptr<QcpFileVisitor> fileHandler = 
      std::make_unique<QcpFileVisitor>(fileData);
    accept(std::move(fileHandler));

    std::get<static_cast<int>(ProjectTuple::FILE_LIST)>(m_data).push_back(fileData);
    return false;
  } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::QCP_FILE])
  else
  {
    xmlReader->raiseError("Unrecognized tag " + xmlReader->name() + " at " +
                          xmlReader->lineNumber());
    return false;
  } //end  else
}

//--------------------------------------------------
//Qcp File Visitor
//--------------------------------------------------
QcpFileVisitor::QcpFileVisitor(FileData_t& data) :
  m_data(data)
{
}
bool QcpFileVisitor::visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
{
  if (xmlReader->name() == File::TagsStr[File::Tags::QCP_FILE])
  {
    auto attribs = xmlReader->attributes();
    QString attribName = File::QcpFile::AttrStr[File::QcpFile::Attributes::VERSION];
    if (!attribs.hasAttribute(attribName))
    {
      xmlReader->raiseError("Missing version attribute on line " + xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(attribName))
    m_version = attribs.value(attribName).toString();
    return true;
  } //end  if (xmlReader->name() == File::TagsStr[File::Tags::QCP_FILE])
  else if (xmlReader->name() == File::TagsStr[File::Tags::NAME])
  {
    QString name;
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(name);
    accept(std::move(chars));

    std::get<static_cast<int>(FileTuple::NAME)>(m_data) = name;
    return false;
  } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::NAME])
  else if (xmlReader->name() == File::TagsStr[File::Tags::LOCATION])
  {
    QString location;
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(location);
    accept(std::move(chars));

    std::get<static_cast<int>(FileTuple::EXPORT_LOCATION)>(m_data) = location;
    return false;
  } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::LOCATION])
  else if (xmlReader->name() == File::TagsStr[File::Tags::COMMENT])
  {
    QString comment;
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(comment);
    accept(std::move(chars));

    std::get<static_cast<int>(FileTuple::COMMENT)>(m_data) = comment;
    return false;
  } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::COMMENT])
  else if (xmlReader->name() == File::TagsStr[File::Tags::DEFAULT_NUMBER])
  {
    int defaultNum;
    std::unique_ptr<CharactersVisitor<int>> chars =
      std::make_unique<CharactersVisitor<int>>(defaultNum);
    accept(std::move(chars));

    std::get<static_cast<int>(FileTuple::DEFAULT_NUMBER)>(m_data) = defaultNum;
    return false;
  } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::DEFAULT_NUMBER])
  else if (xmlReader->name() == File::TagsStr[File::Tags::GROUP_LIST])
  {
    //doesn't actually do anything
    return true;
  } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::GROUP_LIST])
  else if (xmlReader->name() == File::TagsStr[File::Tags::QCP_GROUP])
  {
    //get file path
    QString path;
    QString attribName = File::QcpGroup::AttrStr[File::QcpGroup::Attributes::LOCATION];
    std::unique_ptr<NewXmlVisitor> fileGetter = 
      std::make_unique<NewXmlVisitor>(path, attribName);
    accept(std::move(fileGetter));

    //open new xml reader at file path
    QFile file(path);
    std::unique_ptr<QXmlStreamReader> xmlReader =
      std::make_unique<QXmlStreamReader>(&file);

    //handle the new xml file
    GroupData_t groupData;
    std::unique_ptr<QcpGroupVisitor> fileHandler = 
      std::make_unique<QcpGroupVisitor>(groupData);
    accept(std::move(fileHandler));

    std::get<static_cast<int>(FileTuple::GROUP_LIST)>(m_data).push_back(groupData);
    return false;
  } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::QCP_GROUP])
  else
  {
    xmlReader->raiseError("Unrecognized tag " + xmlReader->name() + " at " +
                          xmlReader->lineNumber());
    return false;
  } //end  else
}

//--------------------------------------------------
//Qcp Group Visitor
//--------------------------------------------------
QcpGroupVisitor::QcpGroupVisitor(GroupData_t& data) :
  m_data(data)
{
}
bool QcpGroupVisitor::visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
{
  //TODO implement
  return false;
}

//--------------------------------------------------
//Variable Visitor
//--------------------------------------------------
VariableVisitor::VariableVisitor(QcpVariable& variable) :
  m_variable(variable)
{
}
bool VariableVisitor::visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
{
  //TODO implement
  return false;
}

//--------------------------------------------------
//New XML Visitor
//--------------------------------------------------
NewXmlVisitor::NewXmlVisitor(QString& path, const QString& attribName) :
  m_path(path),
  m_attribName(attribName)
{
}
bool NewXmlVisitor::visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
{
  //TODO implement
  return false;
}
