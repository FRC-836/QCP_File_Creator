#include "QcpGroup.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
QcpGroup::QcpGroup()
{
}

QcpGroup::QcpGroup(const QVector<QcpVariable>& vars, const QString& name)
{
}
QcpGroup::QcpGroup(const QVector<QcpVariable>& vars, const QString& name,
                  const QString& comment)
{
}

//--------------------------------------------------
//public functions
//--------------------------------------------------
size_t QcpGroup::size()
{
}
QVector<QString> QcpGroup::fileText()
{
}
bool QcpGroup::addVar(const QcpVariable& toAdd)
{
}
void QcpGroup::removeVar(const QcpVariable& toRemove)
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
QString QcpGroup::getComment()
{
}
QString QcpGroup::getName()
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
