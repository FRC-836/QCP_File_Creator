#ifndef QCP_FILE_CREATOR_XML_HELPER_H
#define QCP_FILE_CREATOR_XML_HELPER_H

#include <QVector>
#include <QString>
#include <QXmlStreamReader>
#include <QStack>
#include <QFile>
#include <QtAlgorithms>

#include <tuple>
#include <memory>

#include "QcpVariable.h"

namespace Project
{
  namespace Tags
  {
    enum Tags
    {
      QCP_PROJECT,
      NAME,
      PROJECT_ROOT_DIRECTORY,
      CONSTANT_LIST,
      CONSTANT,
      ARRAY_CONSTANT,
      VALUE,
      FILE_LIST,
      QCP_FILE
    }; //end  enum Tags
  } //end  namespace Tags
  static QStringList TagsStr = {
    "QcpProject",
    "Name",
    "ProjectRootDirectory",
    "ConstantList",
    "Constant",
    "ArrayConstant",
    "Value",
    "FileList",
    "QcpFile"
  }; //end  QString TagsStr[] = {

  namespace QcpProject
  {
    namespace Attributes
    {
      enum Attributes
      {
        VERSION
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "version"
    }; //end  QString AttrStr[] = {
  } //end  namespace QcpProject

  namespace Constant
  {
    namespace Attributes
    {
      enum Attributes
      {
        NAME,
        TYPE,
        VALUE
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "name",
      "type",
      "value"
    }; //end  QString AttrStr[] = {
  } //end  namespace Constant

  namespace ArrayConstant
  {
    namespace Attributes
    {
      enum Attributes
      {
        NAME,
        TYPE
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "name",
      "type"
    }; //end  QString AttrStr[] = {
  } //end  namespace ArrayConstant

  namespace QcpFile
  {
    namespace Attributes
    {
      enum Attributes
      {
        Location
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "Location"
    }; //end  QString AttrStr[] = {
  } //end  namespace QcpFile
} //end namespace Project

namespace File
{
  namespace Tags
  {
    enum Tags
    {
      QCP_FILE,
      NAME,
      LOCATION,
      COMMENT,
      DEFAULT_NUMBER,
      GROUP_LIST,
      QCP_GROUP
    }; //end  enum Tags
  } //end  namespace Tags
  static QStringList TagsStr = {
    "QcpFile",
    "Name",
    "Location",
    "Comment",
    "DefaultNumber",
    "GroupList",
    "QcpGroup"
  }; //end  QString TagsStr[] = {

  namespace QcpFile
  {
    namespace Attributes
    {
      enum Attributes
      {
        VERSION
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "version"
    }; //end  QString AttrStr[] = {
  } //end  namespace QcpFile

  namespace QcpGroup
  {
    namespace Attributes
    {
      enum Attributes
      {
        LOCATION
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "Location"
    }; //end  QString AttrStr[] = {
  } //end  namespace QcpGroup
} //end namespace File

namespace Gruop
{
  namespace Tags
  {
    enum Tags
    {
      QCP_GROUP,
      NAME,
      COMMENT,
      DEFAULT_NUMBER,
      VARIABLE_LIST,
      VARIABLE_ARRAY,
      VALUE,
      VARIABLE
    }; //end  enum Tags
  } //end  namespace Tags
  static QStringList TagsStr = {
    "QcpGroup",
    "Name",
    "Comment",
    "DefaultNumber",
    "VariableList",
    "VariableArray",
    "Value",
    "Variable"
  }; //end  QString TagsStr[] = {

  namespace QcpGroup
  {
    namespace Attributes
    {
      enum Attributes
      {
        VERSION
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "version"
    }; //end  QString AttrStr[] = {
  } //end  namespace QcpGroup

  namespace VariableArray
  {
    namespace Attributes
    {
      enum Attributes
      {
        NAME,
        TYPE
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "name",
      "type"
    }; //end  QString AttrStr[] = {
  } //end  namespace VariableArray

  namespace Variable
  {
    namespace Attributes
    {
      enum Attributes
      {
        NAME,
        TYPE,
        VALUE
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "name",
      "type",
      "value"
    }; //end  QString AttrStr[] = {
  } //end  namespace Variable
} //end namespace Gruop

using VariableList_t = QVector<QcpVariable>; //acts as both variable and constant lists

//<group name, group comment, default number, variable list>
using GroupData_t = std::tuple<QString, QString, int, VariableList_t>;
enum class GroupTuple
{
  NAME,
  COMMENT,
  DEFAULT_NUMBER,
  VARIABLE_LIST
}; //end  enum class GroupTuple
using GroupList_t = QVector<GroupData_t>;

//<file name, export location, file comment, default number, group list>
using FileData_t = std::tuple<QString, QString, QString, int, GroupList_t>;
enum class FileTuple
{
  NAME,
  EXPORT_LOCATION,
  COMMENT,
  DEFAULT_NUMBER,
  GROUP_LIST
}; //end  enum class FileTuple
using FileList_t = QVector<FileData_t>;

//<project name, project directory, constant list, file list>
using ProjectData_t = std::tuple<QString, QString, VariableList_t, FileList_t>;
enum class ProjectTuple
{
  NAME,
  ROOT_DIRECTORY,
  CONSTANT_LIST,
  FILE_LIST
};

class Visitor
{
  public:
    //member variables
    QString version;

    //constructors
    virtual ~Visitor() = default;

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement)
    {
    }
    virtual bool visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader) = 0;
    virtual bool hasError()
    {
      //TODO implement
      return false;
    }
};

//top level visitors
class QcpProjectVisitor : public Visitor
{
  public:
    //member variables
    ProjectData_t& m_data;

    //constructors
    QcpProjectVisitor(ProjectData_t& data);
    virtual ~QcpProjectVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader);
};
class QcpFileVisitor : public Visitor
{
  public:
    //member variables
    FileData_t& m_data;

    //constructors
    QcpFileVisitor(FileData_t& data);
    virtual ~QcpFileVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader);
};
class QcpGroupVisitor : public Visitor
{
  public:
    //member variables
    GroupData_t& m_data;

    //constructors
    QcpGroupVisitor(GroupData_t& data);
    virtual ~QcpGroupVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader);
};

template <typename T>
class CharactersVisitor : public Visitor
{
  public:
    //member variables
    T& m_characters;

    //constructors
    CharactersVisitor(T& characters)
      : m_characters(characters)
    {
    }
    virtual ~CharactersVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
    {
      //TODO implement
      return false;
    }
};

template <typename T>
class ListVisitor : public Visitor
{
  public:
    //member variables
    QVector<T>& m_list;

    //constructors
    ListVisitor(QVector<T>& list)
      : m_list(list)
    {
    }
    virtual ~ListVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader)
    {
      //TODO implement
      return false;
    }
};

class VariableVisitor : public Visitor
{
  public:
    //member variables
    QcpVariable& m_variable;

    //constructors
    VariableVisitor(QcpVariable& variable);
    virtual ~VariableVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::unique_ptr<QXmlStreamReader> xmlReader);
};
#endif
