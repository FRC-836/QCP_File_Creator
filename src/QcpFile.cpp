#include "QcpFile.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
QcpFile::QcpFile()
{
} //end QcpFile::QcpFile()
QcpFile::QcpFile(std::vector<QcpGroup> groups, const QString& comment)
{
}

//--------------------------------------------------
//public functions
//--------------------------------------------------
size_t QcpFile::size()
{
}
std::vector<std::vector<QString>> QcpFile::fileText()
{
}
bool QcpFile::addGroup(const QcpGroup& toAdd)
{
}
void QcpFile::removeGroup(const QcpGroup& toRemove)
{
}
void QcpFile::removeGroup(int index)
{
}
void QcpFile::removeGroup(const QString& toRemoveName)
{
}
void QcpFile::clearGroups()
{
}

//--------------------------------------------------
//getters
//--------------------------------------------------
QString QcpFile::getComment()
{
}

//--------------------------------------------------
//setters
//--------------------------------------------------
void QcpFile::setComment(const QString& comment)
{
}

//--------------------------------------------------
//op overloads
//--------------------------------------------------
QcpGroup& QcpFile::operator[](const int index)
{
}
const QcpGroup& QcpFile::operator[](const int index) const
{
}
