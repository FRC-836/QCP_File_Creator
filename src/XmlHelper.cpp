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
