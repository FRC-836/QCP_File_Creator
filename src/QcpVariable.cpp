#include "QcpVariable.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
QcpVariable::QcpVariable()
{
} //end QcpVariable::QcpVariable()
QcpVariable::QcpVariable(const QcpVariable& toCopy)
{
}
QcpVariable::~QcpVariable()
{
}

//--------------------------------------------------
//public functions
//--------------------------------------------------
QString QcpVariable::fileText() const
{
}

//--------------------------------------------------
//getters
//--------------------------------------------------
QcpVariable::Type QcpVariable::getType() const
{
}
QString QcpVariable::getName() const
{
}

//--------------------------------------------------
//setters
//--------------------------------------------------
void QcpVariable::setName(const QString& name)
{
}

//--------------------------------------------------
//op overloads
//--------------------------------------------------
QcpVariable& QcpVariable::operator=(const QcpVariable& toCopy)
{
}
QcpVariable& QcpVariable::operator=(double value)
{
}
QcpVariable& QcpVariable::operator=(const QVector<double>& value)
{
}
