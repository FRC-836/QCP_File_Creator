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
    //constructors
    virtual ~Visitor();

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement) = 0;
};

//beggining file parsers
class QcpProjectVisitor : public Visitor
{
  public:
    //constructors
    QcpProjectVisitor(ProjectData_t& data, std::unique_ptr<QXmlStreamReader> xmlReader);
    virtual ~QcpProjectVisitor();

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement);
};
class QcpFileVisitor : public Visitor
{
  public:
    //constructors
    QcpFileVisitor(FileData_t& data, std::unique_ptr<QXmlStreamReader> xmlReader);
    virtual ~QcpFileVisitor();

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement);
};
class QcpGroupVisitor : public Visitor
{
  public:
    //constructors
    QcpGroupVisitor(GroupData_t& data, std::unique_ptr<QXmlStreamReader> xmlReader);
    virtual ~QcpGroupVisitor();

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement);
};
template <typename T>
class CharactersVisitor : public Visitor
{
  public:
    //constructors
    CharactersVisitor(T& characters, std::unique_ptr<QXmlStreamReader> xmlReader);
    virtual ~CharactersVisitor();

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement);
};
template <typename T>
class ListVisitor : public Visitor
{
  public:
    //constructors
    ListVisitor(QVector<T>& list, std::unique_ptr<QXmlStreamReader> xmlReader);
    virtual ~ListVisitor();

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement);
};
class VariableVisitor : public Visitor
{
  public:
    //constructors
    VariableVisitor(QcpVariable& variable, std::unique_ptr<QXmlStreamReader> xmlReader);
    virtual ~VariableVisitor();

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement);
};
class QcPfileCallVisitor : public Visitor
{
  public:
    //constructors
    QcPfileCallVisitor(std::unique_ptr<QXmlStreamReader> nextElement);
    virtual ~QcPfileCallVisitor();

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement);
};
class QcpGroupCallVisitor : public Visitor
{
  public:
    //constructors
    QcpGroupCallVisitor(std::unique_ptr<QXmlStreamReader> nextElement);
    virtual ~QcpGroupCallVisitor();

    //public functions
    virtual void accept(std::unique_ptr<Visitor> nextElement);
};

#endif
