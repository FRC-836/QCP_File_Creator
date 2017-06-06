#ifndef QCP_PROJECT_H
#define QCP_PROJECT_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QFileInfo>

#include <fstream>

#include "CommandOptions.h"
#include "QcpFile.h"

class Project
{
  private:
    //member variables
    QVector<QcpFile> m_files; //list of files in the project
    QString m_name; //name of the project
    QString m_location; //location where the project file gets saved
    static int m_defaultNameNum; //used for default naming of projects

    //private functions
    void init(const QString& name, const QString& location, const QVector<QcpFile>& files);
    int findFile(const QString& fileName) const;

  public:
    //constructors
    Project();
    Project(const QString& name, const QString& location);
    Project(const QString& name, const QString& location, const QVector<QcpFile>& files);

    //public functions
    void addFile(const QcpFile& file);
    QcpFile removeFile(const QString& name);
    void clearFiles();
    QcpFile& at(const QString& name);

    //getters
    QString getName() const;
    QString getLocation() const;

    //setters
    void setName(const QString& name);
    void setLocation(const QString& location);

    //op overloads
    QcpFile& operator[](const QString& name);
};

#endif //end #ifndef QCP_PROJECT_H
