#ifndef QCP_FILE_CREATOR_XML_HELPER_H
#define QCP_FILE_CREATOR_XML_HELPER_H

#include <QVector>
#include <QString>
#include <QXmlStreamReader>
#include <QStack>
#include <QFile>
#include <QtAlgorithms>
#include <qvariant.h>

#include <tuple>
#include <memory>

#include "QcpVariable.h"

class Visitor;

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

namespace Group
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

class XmlReader
{
public:
  //member variables
  QStack<std::shared_ptr<Visitor>> m_visitors;
  std::unique_ptr<QXmlStreamReader> m_reader;

  //constructors

  //public functions
  void setNextVisitor(std::shared_ptr<Visitor> nextVisitor);
  bool acceptDoc(const QString& path);
  void accept(std::shared_ptr<Visitor> visitor);

  //getters
  QXmlStreamReader::Error getError() const;
  QString getErrorString() const;
};

class Visitor
{
  public:
    //member variables
    QString m_version = "";
    std::shared_ptr<XmlReader> m_reader;

    //constructors
    Visitor(std::shared_ptr<XmlReader> reader);
    virtual ~Visitor() = default;

    //public funcions
    virtual void accept(std::shared_ptr<Visitor> nextElement);
    virtual bool visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader) = 0;

    //setters
    void setReader(std::shared_ptr<XmlReader> reader);
};

//top level visitors
class QcpProjectVisitor : public Visitor
{
  public:
    //member variables
    ProjectData_t& m_data;

    //constructors
    QcpProjectVisitor(ProjectData_t& data, std::shared_ptr<XmlReader> reader);
    virtual ~QcpProjectVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader);
};
class QcpFileVisitor : public Visitor
{
  public:
    //member variables
    FileData_t& m_data;

    //constructors
    QcpFileVisitor(FileData_t& data, std::shared_ptr<XmlReader> reader);
    virtual ~QcpFileVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader);
};
class QcpGroupVisitor : public Visitor
{
  public:
    //member variables
    GroupData_t& m_data;

    //constructors
    QcpGroupVisitor(GroupData_t& data, std::shared_ptr<XmlReader> reader);
    virtual ~QcpGroupVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader);
};

template <typename T>
class CharactersVisitor : public Visitor
{
  public:
    //member variables
    T& m_characters;

    //constructors
    CharactersVisitor(T& characters, std::shared_ptr<XmlReader> reader) :
      Visitor(reader),
      m_characters(characters)
    {
    }
    virtual ~CharactersVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader)
    {
      //ensure that the reader is at characters
      if (!xmlReader->isCharacters())
      {
        xmlReader->raiseError("No characters found at " + xmlReader->lineNumber());
        return false;
      } //end  if (!xmlReader->isCharacters())

      //read the characters 
      QVariant variant = QVariant::fromValue(xmlReader->text().toString());

      //make sure the characters can be converted to the desired type
      if (!variant.canConvert<T>())
      {
        xmlReader->raiseError("Cannot properly interperat characters at " + 
                              xmlReader->lineNumber());
        return false;
      } //end  if (!variant.canConvert<T>())

      //interperat the characters as the correct type
      m_characters = variant.value<T>();
      return false;
    }
};

class VariableVisitor : public Visitor
{
  public:
    //member variables
    QcpVariable& m_variable;
    QcpVariable::Type m_type;

    //constructors
    VariableVisitor(QcpVariable& variable, std::shared_ptr<XmlReader> reader);
    virtual ~VariableVisitor() = default;

    //public functions
    virtual bool visitorEnter(std::shared_ptr<QXmlStreamReader> xmlReader);
};
#endif
