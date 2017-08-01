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
    if (!attribs.hasAttribute(Project::QcpProject::AttrStr[Project::QcpProject::Attributes::VERSION]))
    {
      xmlReader->raiseError("Version attribute not found " + QString::number(xmlReader->lineNumber()));
      return false;
    } //end  if (!attribs.hasAttribute(Project::QcpProject::AttrStr[Project::QcpProject::Attributes::VERSION]))
    version = attribs.value(Project::QcpProject::AttrStr[Project::QcpProject::Attributes::VERSION]).toString();
    return true;
  } //end  if (xmlReader->name() == Project::TagsStr[Project::Tags::QCP_PROJECT])
  else
  {
    if (xmlReader->name() == Project::TagsStr[Project::Tags::NAME])
    {
      QString name;
      std::unique_ptr<CharactersVisitor<QString>> chars =
          std::make_unique<CharactersVisitor<QString>>(name);
      accept(std::move(chars));
      std::get<static_cast<int>(ProjectTuple::NAME)>(m_data) = name;
    } //end  if (xmlReader->name() == Project::TagsStr[Project::Tags::NAME])
    else if (xmlReader->name() == Project::TagsStr[Project::Tags::PROJECT_ROOT_DIRECTORY])
    {
      QString rootPath;
      std::unique_ptr<CharactersVisitor<QString>> chars =
          std::make_unique<CharactersVisitor<QString>>(rootPath);
      accept(std::move(chars));
      std::get<static_cast<int>(ProjectTuple::ROOT_DIRECTORY)>(m_data) = rootPath;
    } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::PROJECT_ROOT_DIRECTORY])
    else if (xmlReader->name() == Project::TagsStr[Project::Tags::CONSTANT_LIST])
    {
      QVector<QcpVariable> constants;
      std::unique_ptr<Visitor> handler = std::make_unique<VariableVisitor>();
      std::unique_ptr<ListVisitor<QcpVariable>> list =
        std::make_unique<ListVisitor<QcpVariable>>(constants, handler);
      accept(std::move(list));
      std::get<static_cast<int>(ProjectTuple::CONSTANT_LIST)>(m_data) = constants;
    } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::CONSTANT_LIST])
    else if (xmlReader->name() == Project::TagsStr[Project::Tags::FILE_LIST])
    {
      //grab all files from the file list
      QVector<QString> filePaths;
      std::unique_ptr<NewXmlVisitor> handler;
      std::unique_ptr<ListVisitor<QString>> list =
        std::make_unique<ListVisitor<QString>>(filePaths, handler);
      accept(std::move(list));

      //get data from all qcprf calls
      for (auto file : filePaths)
      {
        //create the new xmlStreamReader
        QFile newXml(file);
        std::unique_ptr<QXmlStreamReader> newXmlReader =
            std::make_unique<QXmlStreamReader>(&newXml);
        //TODO figure out a way to update the xmlStreamReader to the new one

        //create the data holder
        FileData_t data;

        //create the new top level visitor
        std::unique_ptr<QcpFileVisitor> fileHandler =
            std::make_unique<QcpFileVisitor>(data);
        accept(std::move(fileHandler));

        //add file data to tuple
        std::get<static_cast<int>(ProjectTuple::FILE_LIST)>(m_data).push_back(data);
      } //end  for (auto file : files)
    } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::FILE_LIST])
    else
    {
      //TODO handle wrong tag
    }
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
    if (!attribs.hasAttribute(File::QcpFile::AttrStr[File::QcpFile::Attributes::VERSION]))
    {
      xmlReader->raiseError("Version attribute not found " + QString::number(xmlReader->lineNumber()));
      return false;
    } //end  if (!attribs.hasAttribute(File::QcpFile::AttrStr[File::QcpFile::Attributes::VERSION])
    version = attribs.value(File::QcpFile::AttrStr[File::QcpFile::Attributes::VERSION]).toString();
    return true;
  }
  else
  {
    if (xmlReader->name() == File::TagsStr[File::Tags::NAME])
    {
      QString name;
      std::unique_ptr<CharactersVisitor<QString>> chars = 
        std::make_unique<CharactersVisitor<QString>>(name);
      accept(std::move(chars));
      std::get<static_cast<int>(FileTuple::NAME)>(m_data) = name;
    } //end  if (xmlReader->name() == File::TagsStr[File::Tags::NAME]
    else if (xmlReader->name() == File::TagsStr[File::Tags::COMMENT])
    {
      QString comment;
      std::unique_ptr<CharactersVisitor<QString>> chars =
        std::make_unique<CharactersVisitor<QString>>(comment);
      accept(std::move(chars));
      std::get<static_cast<int>(FileTuple::COMMENT)>(m_data) = comment;
    } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::COMMENT]
    else if (xmlReader->name() == File::TagsStr[File::Tags::LOCATION])
    {
      QString location;
      std::unique_ptr<CharactersVisitor<QString>> chars =
        std::make_unique<CharactersVisitor<QString>>(location);
      accept(std::move(chars));
      std::get<static_cast<int>(FileTuple::EXPORT_LOCATION)>(m_data) = location;
    } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::LOCATION]
    else if (xmlReader->name() == File::TagsStr[File::Tags::DEFAULT_NUMBER])
    {
      int defaultNum;
      std::unique_ptr<CharactersVisitor<int>> chars =
        std::make_unique<CharactersVisitor<int>>(defaultNum);
      accept(std::move(chars));
      std::get<static_cast<int>(FileTuple::DEFAULT_NUMBER)>(m_data) = defaultNum;
    } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::DEFAULT_NUMBER]
    else if (xmlReader->name() == File::TagsStr[File::Tags::GROUP_LIST])
    {
      QVector<QString> groupFilePaths;
      std::unique_ptr<NewXmlVisitor> handler;
      std::unique_ptr<ListVisitor<QString>> list =
        std::make_unique<ListVisitor<QString>>(groupFilePaths, handler);
      accept(std::move(list));

      //get the data from all qcprg files
      for (auto filePath : groupFilePaths)
      {
        //create the new xml reader
        QFile file(filePath);
        std::unique_ptr<QXmlStreamReader> xmlFile = std::make_unique<QXmlStreamReader>(&file);
        //TODO figure out a way to update the xmlStreamReader to the new one

        //grab the data
        GroupData_t data;
        std::unique_ptr<QcpGroupVisitor> reader = std::make_unique<QcpGroupVisitor>(data);
        accept(std::move(reader));

        //store the data in the appropriate tuple location
        std::get<static_cast<int>(FileTuple::GROUP_LIST)>(m_data).push_back(data);
      } //end  for (auto file : groupFilePaths)
    } //end  else if (xmlReader->name() == File::TagsStr[File::Tags::GROUP_LIST]
    else
    {
      //TODO handle incorrect tag
      xmlReader->raiseError("Unrecognize tag " + xmlReader->name() + " on line " + xmlReader->lineNumber());
    } //end else
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
  if (xmlReader->name() == Group::TagsStr[Group::Tags::QCP_GROUP])
  {
    auto attribs = xmlReader->attributes();
    if (!attribs.hasAttribute(Group::QcpGroup::AttrStr[Group::QcpGroup::Attributes::VERSION]))
    {
      xmlReader->raiseError("Version attribute not found " + QString::number(xmlReader->lineNumber()));
      return false;
    } //end  if (!attribs.hasAttribute(Group::QcpGroup::AttrStr[Group::QcpGroup::Attributes::VERSION]))
    version = attribs.value(Group::QcpGroup::AttrStr[Group::QcpGroup::Attributes::VERSION]).toString();
    return true;
  } //end  if (xmlReader->name() == Group::TagsStr[Group::Tags::QCP_GROUP])
  else
  {
    if (xmlReader->name() == Group::TagsStr[Group::Tags::NAME])
    {
      QString name;
      std::unique_ptr<CharactersVisitor<QString>> chars =
        std::make_unique<CharactersVisitor<QString>>(name);
      accept(std::move(chars));

      std::get<static_cast<int>(GroupTuple::NAME)>(m_data) = name;
    } //end  if (xmlReader->name() == Group::TagsStr[Group::Tags::NAME])
    else if (xmlReader->name() == Group::TagsStr[Group::Tags::COMMENT])
    {
      QString comment;
      std::unique_ptr<CharactersVisitor<QString>> chars =
        std::make_unique<CharactersVisitor<QString>>(comment);
      accept(std::move(chars));

      std::get<static_cast<int>(GroupTuple::COMMENT)>(m_data) = comment;
    } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::COMMENT])
    else if (xmlReader->name() == Group::TagsStr[Group::Tags::DEFAULT_NUMBER])
    {
      int defaultNum;
      std::unique_ptr<CharactersVisitor<int>> chars =
        std::make_unique<CharactersVisitor<int>>(defaultNum);
      accept(std::move(chars));

      std::get<static_cast<int>(GroupTuple::DEFAULT_NUMBER)>(m_data) = defaultNum;
    } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::DEFAULT_NUMBER])
    else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE_LIST])
    {
      QVector<QcpVariable> vars;
      std::unique_ptr<VariableVisitor> handler;
      std::unique_ptr<ListVisitor<QcpVariable>> list =
        std::make_unique<ListVisitor<QcpVariable>>(vars, handler);
      accept(std::move(list));

      std::get<static_cast<int>(GroupTuple::VARIABLE_LIST)>(m_data) = vars;
    } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE_LIST])
    else
    {
      xmlReader->raiseError("Unrecognized tag " + xmlReader->name() + " on line " + xmlReader->lineNumber());
    } //end  else
    return false;
  } //end  else
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
  if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE])
  {
    auto attribs = xmlReader->attributes();
    QString nameAttrStr = Group::Variable::AttrStr[Group::Variable::Attributes::NAME];
    if (!attribs.hasAttribute(nameAttrStr))
    {
      xmlReader->raiseError(nameAttrStr + " attribute not found " + xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(nameAttrStr))
    m_variable.setName(attribs.value(nameAttrStr).toString());

    QString typeAttrStr = Group::Variable::AttrStr[Group::Variable::Attributes::TYPE];
    if (!attribs.hasAttribute(typeAttrStr))
    {
      xmlReader->raiseError(typeAttrStr + " attribute not found " + xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(typeAttrStr))
    m_type = QcpVariable::strToType(attribs.value(typeAttrStr).toString());

    QString valueAttrStr = Group::Variable::AttrStr[Group::Variable::Attributes::VALUE];
    if (!attribs.hasAttribute(valueAttrStr))
    {
      xmlReader->raiseError(valueAttrStr + " attribute not found " + xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(valueAttrStr))
    m_variable.changeValue(m_type, (attribs.value(valueAttrStr).toString()));
    return false; //don't want to go down to any value tags by accident
  } //end  if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE])
  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE_ARRAY])
  {
    auto attribs = xmlReader->attributes();
    QString nameAttrStr = Group::Variable::AttrStr[Group::Variable::Attributes::NAME];
    if (!attribs.hasAttribute(nameAttrStr))
    {
      xmlReader->raiseError(nameAttrStr + " attriubte not found " + xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(nameAttrStr))
    m_variable.setName(attribs.value(nameAttrStr).toString());

    QString typeAttrStr = Group::Variable::AttrStr[Group::Variable::Attributes::TYPE];
    if (!attribs.hasAttribute(typeAttrStr))
    {
      xmlReader->raiseError(typeAttrStr + " attriubte not found " + xmlReader->lineNumber());
      return false;
    } //end  if (!attribs.hasAttribute(typeAttrStr))
    m_type = QcpVariable::strToType(attribs.value(typeAttrStr).toString());
    return true;
  } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VARIABLE_ARRAY])
  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VALUE])
  {
    double value;
    std::unique_ptr<CharactersVisitor<double>> chars =
      std::make_unique<CharactersVisitor<double>>(value);
    accept(std::move(chars));

    //add value to variable values
    auto values = m_variable.getValue<QVector<double>>();
    values.push_back(value);
    m_variable.changeValue(m_type, values);
    return false;
  } //end  else if (xmlReader->name() == Group::TagsStr[Group::Tags::VALUE])
  else
  {
    xmlReader->raiseError("Unrecognized tag " + xmlReader->name() + " on line " + xmlReader->lineNumber());
    return false;
  } //end  else
}
