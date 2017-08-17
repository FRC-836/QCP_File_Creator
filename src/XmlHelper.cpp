#include "XmlHelper.h"

//--------------------------------------------------
//Xml Reader
//--------------------------------------------------
void XmlReader::setNextVisitor(std::shared_ptr<Visitor> nextVisitor)
{
  m_visitors.push(nextVisitor);
}
bool XmlReader::acceptDoc(const QString& path)
{
  QFile* xmlFile = new QFile(path);

  if (!xmlFile->exists())
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: XmlHelper: file " << path.toStdString() << " doesn't exist" 
                << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    return false;
  } //end  if (!xmlFile->exists())
  if (!xmlFile->isReadable())
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      std::cout << "ERROR: XmlHelper: file " << path.toStdString() << " isn't readable"
                << std::endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    return false;
  } //end  if (!xmlFile->isReadable())

  m_reader = std::make_unique<QXmlStreamReader>(xmlFile);
  while (m_reader->isStartDocument())
  {
    m_reader->readNext();
  } //end  while (m_reader->isStartDocument())
  return true;
}
void XmlReader::accept(std::shared_ptr<Visitor> visitor)
{
}
QXmlStreamReader::Error XmlReader::getError() const
{
  return m_reader->error();
}
QString XmlReader::getErrorString() const
{
  return m_reader->errorString();
}

//--------------------------------------------------
//Visitor
//--------------------------------------------------
Visitor::Visitor(std::shared_ptr<XmlReader> reader)
{
  m_reader = reader;
}
void Visitor::accept(std::shared_ptr<Visitor> nextElement)
{
  m_reader->setNextVisitor(nextElement);
}
void Visitor::setReader(std::shared_ptr<XmlReader> reader)
{
  m_reader = reader;
}

//--------------------------------------------------
//Qcp Project Visitor
//--------------------------------------------------
QcpProjectVisitor::QcpProjectVisitor(ProjectData_t& data,std::shared_ptr<XmlReader> reader) :
  Visitor(reader), 
  m_data(data)
{
}
bool QcpProjectVisitor::visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader)
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
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(std::get<static_cast<int>(ProjectTuple::NAME)>(m_data), m_reader);
    accept(std::move(chars));

    return false;
  } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::NAME])
  else if (xmlReader->name() == Project::TagsStr[Project::Tags::PROJECT_ROOT_DIRECTORY])
  {
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(std::get<static_cast<int>(ProjectTuple::ROOT_DIRECTORY)>(m_data), m_reader);
    accept(std::move(chars));

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
    std::get<static_cast<int>(ProjectTuple::CONSTANT_LIST)>(m_data).push_back(QcpVariable());
    std::unique_ptr<VariableVisitor> variable = 
      std::make_unique<VariableVisitor>(std::get<static_cast<int>(ProjectTuple::CONSTANT_LIST)>(m_data).last(), m_reader);
    accept(std::move(variable));

    return false;
  } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::CONSTANT]) ||
  else if (xmlReader->name() == Project::TagsStr[Project::Tags::QCP_FILE])
  {
    //get file path
    QString path;
    QString attribName = Project::QcpFile::AttrStr[Project::QcpFile::Attributes::Location];
    std::unique_ptr<NewXmlVisitor> fileGetter = 
      std::make_unique<NewXmlVisitor>(path, attribName, m_reader);
    accept(std::move(fileGetter));

    //open new xml reader at file path
    QFile file(path);
    std::unique_ptr<QXmlStreamReader> xmlReader =
      std::make_unique<QXmlStreamReader>(&file);

    //handle the new xml file
    std::get<static_cast<int>(ProjectTuple::FILE_LIST)>(m_data).push_back(FileData_t());
    std::unique_ptr<QcpFileVisitor> fileHandler = 
      std::make_unique<QcpFileVisitor>(std::get<static_cast<int>(ProjectTuple::FILE_LIST)>(m_data).last(), m_reader);
    accept(std::move(fileHandler));

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
QcpFileVisitor::QcpFileVisitor(FileData_t& data, std::shared_ptr<XmlReader> reader) :
  Visitor(reader),
  m_data(data)
{
}
bool QcpFileVisitor::visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader)
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
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(std::get<static_cast<int>(FileTuple::NAME)>(m_data), m_reader);
    accept(std::move(chars));

    return false;
  } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::NAME])
  else if (xmlReader->name() == File::TagsStr[File::Tags::LOCATION])
  {
    QString location;
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(location, m_reader);
    accept(std::move(chars));

    std::get<static_cast<int>(FileTuple::EXPORT_LOCATION)>(m_data) = location;
    return false;
  } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::LOCATION])
  else if (xmlReader->name() == File::TagsStr[File::Tags::COMMENT])
  {
    QString comment;
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(comment, m_reader);
    accept(std::move(chars));

    std::get<static_cast<int>(FileTuple::COMMENT)>(m_data) = comment;
    return false;
  } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::COMMENT])
  else if (xmlReader->name() == File::TagsStr[File::Tags::DEFAULT_NUMBER])
  {
    int defaultNum;
    std::unique_ptr<CharactersVisitor<int>> chars =
      std::make_unique<CharactersVisitor<int>>(defaultNum, m_reader);
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
      std::make_unique<NewXmlVisitor>(path, attribName, m_reader);
    accept(std::move(fileGetter));

    //open new xml reader at file path
    QFile file(path);
    std::unique_ptr<QXmlStreamReader> xmlReader =
      std::make_unique<QXmlStreamReader>(&file);

    //handle the new xml file
    GroupData_t groupData;
    std::unique_ptr<QcpGroupVisitor> fileHandler = 
      std::make_unique<QcpGroupVisitor>(groupData, m_reader);
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
QcpGroupVisitor::QcpGroupVisitor(GroupData_t& data, std::shared_ptr<XmlReader> reader) :
  Visitor(reader),
  m_data(data)
{
}
bool QcpGroupVisitor::visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader)
{
  if (xmlReader->name() == Group::TagsStr[Group::Tags::QCP_GROUP])
  {
    auto attribs = xmlReader->attributes();
    QString attribName = Group::QcpGroup::AttrStr[Group::QcpGroup::Attributes::VERSION];
    if (!attribs.hasAttribute(attribName))
    {
      xmlReader->raiseError("Version tag not found on line " + xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(attribName))
    m_version = attribs.value(attribName).toString();
    return true;
  } //end  if (xmlReader->name() == Group::TagsStr[Group::Tags::QCP_GROUP])
  else if (xmlReader->name() == Group::TagsStr[Group::Tags::NAME])
  {
    QString name;
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(name, m_reader);
    accept(std::move(chars));

    std::get<static_cast<int>(GroupTuple::NAME)>(m_data) = name;
    return false;
  } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::NAME])
  else if (xmlReader->name() == Group::TagsStr[Group::Tags::COMMENT])
  {
    QString comment;
    std::unique_ptr<CharactersVisitor<QString>> chars =
      std::make_unique<CharactersVisitor<QString>>(comment, m_reader);
    accept(std::move(chars));

    std::get<static_cast<int>(GroupTuple::COMMENT)>(m_data) = comment;
    return false;
  } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::COMMENT])
  else if (xmlReader->name() == Group::TagsStr[Group::Tags::DEFAULT_NUMBER])
  {
    int defaultNum;
    std::unique_ptr<CharactersVisitor<int>> chars =
      std::make_unique<CharactersVisitor<int>>(defaultNum, m_reader);
    accept(std::move(chars));

    std::get<static_cast<int>(GroupTuple::DEFAULT_NUMBER)>(m_data) = defaultNum;
    return false;
  } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::DEFAULT_NUMBER])
  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE_LIST])
  {
    //doesn't actually do anything
    return true;
  } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE_LIST])
  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE] ||
           xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE_ARRAY])
  {
    QcpVariable var;
    std::unique_ptr<VariableVisitor> variable = std::make_unique<VariableVisitor>(var, m_reader);
    accept(std::move(variable));

    std::get<static_cast<int>(GroupTuple::VARIABLE_LIST)>(m_data).push_back(var);
    return false;
  } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE] ||
  else
  {
    xmlReader->raiseError("Unrecognized tag " + xmlReader->name() + " at " +
                          xmlReader->lineNumber());
    return false;
  } //end  else
}

//--------------------------------------------------
//Variable Visitor
//--------------------------------------------------
VariableVisitor::VariableVisitor(QcpVariable& variable, std::shared_ptr<XmlReader> reader) :
  Visitor(reader),
  m_variable(variable)
{
}
bool VariableVisitor::visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader)
{
  if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE])
  {
    //get attributes
    auto attribs = xmlReader->attributes();

    //handle name attribute
    QString attribName = Group::Variable::AttrStr[Group::Variable::Attributes::NAME];
    if (!attribs.hasAttribute(attribName))
    {
      xmlReader->raiseError("No attribute " + attribName + " found at " +
                            xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(attribName))
    m_variable.setName(attribs.value(attribName).toString());

    //handle type attribute
    attribName = Group::Variable::AttrStr[Group::Variable::Attributes::TYPE];
    if (!attribs.hasAttribute(attribName))
    {
      xmlReader->raiseError("No attribute " + attribName + " found at " +
                            xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(attribName))
    
    //ensure a valid type was supplied
    QcpVariable::Type type = QcpVariable::strToType(attribs.value(attribName).toString());
    if (type == QcpVariable::Type::INVALID)
    {
      xmlReader->raiseError("Invalid type provided for variable on line " +
                            xmlReader->lineNumber());
      return false;
    } //end  if (type == QcpVariable::Type::INVALID)

    //handle value attribute
    attribName = Group::Variable::AttrStr[Group::Variable::Attributes::VALUE];
    if (!attribs.hasAttribute(attribName))
    {
      xmlReader->raiseError("No attribute " + attribName + " found at " +
                            xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(attribName))
    m_variable.changeValue(type, attribs.value(attribName).toString());
  } //end  if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE])
  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE_ARRAY])
  {
    auto attribs = xmlReader->attributes();

    //handle name attribute
    QString attribName = Group::VariableArray::AttrStr[Group::VariableArray::Attributes::NAME];
    if (!attribs.hasAttribute(attribName))
    {
      xmlReader->raiseError("No attribute " + attribName + " found at " +
                            xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(attribName))
    m_variable.setName(attribs.value(attribName).toString());

    //handle type attribute
    attribName = Group::VariableArray::AttrStr[Group::VariableArray::Attributes::TYPE];
    if (!attribs.hasAttribute(attribName))
    {
      xmlReader->raiseError("No attribute " + attribName + " found at " +
                            xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(attribName))

    //ensure type is valid
    QcpVariable::Type type = QcpVariable::strToType(attribs.value(attribName).toString());
    if (type == QcpVariable::Type::INVALID)
    {
      xmlReader->raiseError("Invalid type provided at " + xmlReader->lineNumber());
      return false;
    } //end  if (type == QcpVariable::Type::INVALID)

    //TODO figure out how to handle other types
    m_variable.changeValue(type, m_variable.getValue<QVector<double>>());
  } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE_ARRAY])
  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VALUE])
  {
    double value;
    std::unique_ptr<CharactersVisitor<double>> chars =
      std::make_unique<CharactersVisitor<double>>(value, m_reader);
    accept(std::move(chars));

    auto values = m_variable.getValue<QVector<double>>();
    values.push_back(value);
    m_variable.changeValue(m_variable.getType(), values);
  } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VALUE])
  else
  {
    xmlReader->raiseError("Unrecognized tag " + xmlReader->name() + " at " +
                          xmlReader->lineNumber());
    return false;
  } //end  else
}

//--------------------------------------------------
//New XML Visitor
//--------------------------------------------------
NewXmlVisitor::NewXmlVisitor(QString& path, const QString& attribName, 
                             std::shared_ptr<XmlReader> reader) :
  Visitor(reader),
  m_path(path),
  m_attribName(attribName)
{
}
bool NewXmlVisitor::visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader)
{
  auto attribs = xmlReader->attributes();
  if (!attribs.hasAttribute(m_attribName))
  {
    xmlReader->raiseError("Unrecognized attribute " + m_attribName + " found at " +
                          xmlReader->lineNumber());
    return false;
  } //end  if (!attribs.hasAttribute(m_attribName))
  m_path = attribs.value(m_attribName).toString();
  return false;
}
