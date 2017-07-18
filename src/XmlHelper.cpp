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
    }
    return true;
  } //end  if (xmlReader->name() == Project::TagsStr[Project::Tags::QCP_PROJECT])
  else
  {
    if (xmlReader->name() == Project::TagsStr[Project::Tags::NAME])
    {
      QString name;
      std::unique_ptr<Visitor> chars =
          std::make_unique<CharactersVisitor<QString>>(name);
      accept(std::move(chars));
      std::get<static_cast<int>(ProjectTuple::NAME)>(m_data);
    }
    else if (xmlReader->name() == Project::TagsStr[Project::Tags::PROJECT_ROOT_DIRECTORY])
    {
    }
    else if (xmlReader->name() == Project::TagsStr[Project::Tags::CONSTANT_LIST])
    {
    }
    else if (xmlReader->name() == Project::TagsStr[Project::Tags::FILE_LIST])
    {
    }
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

//--------------------------------------------------
//Call Visitor
//--------------------------------------------------
CallVisitor::CallVisitor(std::unique_ptr<Visitor> newHandler)
  : m_newHandler(std::move(newHandler))
{
}
void CallVisitor::accept(std::unique_ptr<Visitor> nextElement)
{
}
bool CallVisitor::visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
{
}
