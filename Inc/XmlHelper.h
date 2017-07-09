#ifndef QCP_FILE_CREATOR_XML_HELPER_H
#define QCP_FILE_CREATOR_XML_HELPER_H

#include <QVector>
#include <QString>
#include <QXmlStreamReader>
#include <QStack>

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
  QString TagsStr[] = {
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
    QString AttrStr[] = {
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
    QString AttrStr[] = {
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
    QString AttrStr[] = {
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
  QString TagsStr[] = {
    "QcpFile",
    "Name",
    "Location",
    "Comment",
    "DefaultNumber",
    "GroupList",
    "QcpGroup"
  }; //end  QString TagsStr[] = {

  namespace QcpGroup
  {
    namespace Attributes
    {
      enum Attributes
      {
        LOCATION
      }; //end  enum Attributes
    } //end  namespace Attributes
    QString AttrStr[] = {
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
  QString TagsStr[] = {
    "QcpGroup",
    "Name",
    "Comment",
    "DefaultNumber",
    "VariableList",
    "VariableArray",
    "Value",
    "Variable"
  };
   //end  QString TagsStr[] = {
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
    QString AttrStr[] = {
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
    QString AttrStr[] = {
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
    using GroupList_t = QVector<GroupData_t>;
    //<file name, export location, file comment, default number, group list>
    using FileData_t = std::tuple<QString, QString, QString, int, GroupList_t>;
    using FileList_t = QVector<FileData_t>;
    //<project name, project directory, constant list, file list>
    using ProjectData_t = std::tuple<QString, QString, VariableList_t, FileList_t>;

  private:
    //member variables
    static QXmlStreamReader m_reader;

  public:
    static std::unique_ptr<ProjectData_t> parseXml(const QString& projectLocation);
};

#endif
