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
size_t QcpFile::size() const
{
}
std::vector<std::vector<QString>> QcpFile::fileText() const
{
}
bool QcpFile::addGroup(const QcpGroup& toAdd)
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
QString QcpFile::getComment() const
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
