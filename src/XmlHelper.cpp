#include "XmlHelper.h"

//--------------------------------------------------
//Qcp Project Visitor
//--------------------------------------------------
QcpProjectVisitor::QcpProjectVisitor(ProjectData_t& data)
  : m_data(data)
{
}
void QcpProjectVisitor::accept(std::unique_ptr<Visitor> nextElement)
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
      std::unique_ptr<ListVisitor<QcpVariable>> list =
          std::make_unique<ListVisitor<QcpVariable>>(constants);
      accept(std::move(list));
      std::get<static_cast<int>(ProjectTuple::CONSTANT_LIST)>(m_data) = constants;
    } //end  else if (xmlReader->name() == Project::TagsStr[Project::Tags::CONSTANT_LIST])
    else if (xmlReader->name() == Project::TagsStr[Project::Tags::FILE_LIST])
    {
      //grab all files from the file list
      QVector<QString> files;
      std::unique_ptr<ListVisitor<QString>> list =
          std::make_unique<ListVisitor<QString>>(files);
      accept(std::move(list));

      //get data from all qcprf calls
      FileList_t fileData;
      for (auto file : files)
      {
        //create the new xmlStreamReader
        QFile newXml(file);
        std::unique_ptr<QXmlStreamReader> newXmlReader =
            std::make_unique<QXmlStreamReader>(newXml);

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
    return false;
  } //end  else
}

//--------------------------------------------------
//Qcp File Visitor
//--------------------------------------------------
QcpFileVisitor::QcpFileVisitor(FileData_t& data)
  : m_data(data)
{
}
void QcpFileVisitor::accept(std::unique_ptr<Visitor> nextElement)
{
}
bool QcpFileVisitor::visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
{
}

//--------------------------------------------------
//Qcp Group Visitor
//--------------------------------------------------
QcpGroupVisitor::QcpGroupVisitor(GroupData_t& data)
  : m_data(data)
{
}
void QcpGroupVisitor::accept(std::unique_ptr<Visitor> nextElement)
{
}
bool QcpGroupVisitor::visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
{
}

//--------------------------------------------------
//Variable Visitor
//--------------------------------------------------
VariableVisitor::VariableVisitor(QcpVariable& variable)
  : m_variable(variable)
{
}
void VariableVisitor::accept(std::unique_ptr<Visitor> nextElement)
{
}
bool VariableVisitor::visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
{
}
