#ifndef QCP_PROJECT_H
#define QCP_PROJECT_H

#include <QString>
#include <QVector>
#include <QMap>

#include <utility>
#include <fstream>

#include "CommandOptions.h"
#include "QcpFile.h"

class Project
{
  private:
    //member variables
    QMap<QString, QcpFile> m_files; //first: name of file | second: file ADT
    QString m_name; //name of the project

    //private functions
    void init(const QString& name, const QMap<QString, QcpFile>& files);

  public:
    //constructors
    Project();
    Project(const QString& name);
    Project(const QString& name, const QMap<QString, QcpFile>& files);

    //public functions
    void addFile(const QString& name, const QcpFile& file);
    QcpFile removeFile(const QString& name);
    void clearFiles();
    QcpFile& at(const QString& name);
    const QcpFile& at(const QString& name) const;

    //getters
    QString getName() const;

    //setters
    void setName(const QString& name);

    //op overloads
    QcpFile& operator[](const QString& name);
    const QcpFile& operator[](const QString& name) const;
};

#endif //end #ifndef QCP_PROJECT_H
