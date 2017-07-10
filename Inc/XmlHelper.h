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

class XmlHelper
{
  public:
    //type alliases
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

  private:
    //member variables
    QXmlStreamReader m_reader;

    //private functions
    std::unique_ptr<ProjectData_t> parseProjectXmlOne(); //version 1.0 files
    std::unique_ptr<FileData_t> parseFileXmlOne(); //version 1.0 files
    std::unique_ptr<GroupData_t> parseGroupXmlOne(); //version 1.0 files

  public:
    //constructors
    XmlHelper();

    //public functions
    std::unique_ptr<ProjectData_t> parseXml(const QString& projectLocation);
};

#endif
