#include "QcpGroup.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
QcpGroup::QcpGroup()
{
}

QcpGroup::QcpGroup(const std::vector<QcpVariable>& vars, const QString& name)
{
}
QcpGroup::QcpGroup(const std::vector<QcpVariable>& vars, const QString& name,
                   const QString& comment)
{
}

//--------------------------------------------------
//public functions
//--------------------------------------------------
size_t QcpGroup::size() const
{
}
std::vector<QString> QcpGroup::fileText() const
{
}
bool QcpGroup::addVar(const QcpVariable& toAdd)
{
}
void QcpGroup::removeVar(int index)
{
}
void QcpGroup::removeVar(const QString& toRemoveName)
{
}
void QcpGroup::clearVars()
{
}

//--------------------------------------------------
//getters
//--------------------------------------------------
QString QcpGroup::getComment() const
{
}
QString QcpGroup::getName() const
{
}

//--------------------------------------------------
//setters
//--------------------------------------------------
void QcpGroup::setComment(const QString& comment)
{
}
void QcpGroup::setName(const QString& name)
{
}

//--------------------------------------------------
//op overloads
//--------------------------------------------------
QcpVariable& QcpGroup::operator[](const int index)
{
}
const QcpVariable& QcpGroup::operator[](const int index) const
{
}
