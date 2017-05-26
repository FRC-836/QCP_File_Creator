#include "Project.h"

//--------------------------------------------------
//private functions
//--------------------------------------------------
void Project::init(const QString& name, const std::map<QString, QcpFile>& files)
{
}

//--------------------------------------------------
//constructors
//--------------------------------------------------
Project::Project()
{
} //end Project::Project()
Project::Project(const QString& name)
{
}
Project::Project(const QString& name, const std::map<QString, QcpFile>& files)
{
}

//--------------------------------------------------
//public functions
//--------------------------------------------------
void Project::addFile(const QString& name, const QcpFile& file)
{
}
QcpFile Project::removeFile(const QString& name)
{
}
void Project::clearFiles()
{
}
QcpFile& Project::at(const QString& name)
{
}
const QcpFile& Project::at(const QString& name) const
{
}

//--------------------------------------------------
//getters
//--------------------------------------------------
QString Project::getName() const
{
}

//--------------------------------------------------
//setters
//--------------------------------------------------
void Project::setName(const QString& name)
{
}

//--------------------------------------------------
//op overloads
//--------------------------------------------------
QcpFile& Project::operator[](const QString& name)
{
}
const QcpFile& Project::operator[](const QString& name) const
{
}
