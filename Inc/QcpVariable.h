#ifndef QCP_VARIABLE_H
#define QCP_VARIABLE_H

#include <QVariant>
#include <QVector>

#include <iostream>
#include <sstream>
#include <typeinfo>
#include <algorithm>
#include <cctype>

#include "CommandOptions.h"

class QcpVariable
{
  public:
    //public enums
    enum class Type
    {
      DOUBLE,
      DOUBLE_ARRAY
    };

  private:
    //member variables
    QVariant m_value; //value the variable holds
    Type m_type; //type of the variable
    QString m_name; //name of the variable
    static int m_defaultVarNum;

    //private functions
    template <typename T> init(const QString& name, Type type, T value)
    {
      QString actualName; //handles the case when name is not provided
      //handle blank names
      if (!std::all_of(name.toStdString().begin(), name.toStdString().end(), isspace))
      {
        if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
        {
          std::cout << "default variable name being used due to empty name" << std::endl;
        } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
        actualName = QString("Var");
        actualName += QString::fromStdString(std::to_string(m_defaultVarNum));
        m_defaultVarNum++;
      }//end if(!std::all_of(name.toStdString().begin(),name.toStdString().end(),isspace))
      else
      {
        actualName = name;
      } //end  else

      setName(name);
      changeValue(type, value);
    } //end  template <typename T> init(const QString& name, Type type, T value)
    /**
     * @brief doubleText
     * @details responsible for converting m_value to text when m_type is double
     * @return QCP file compatible text representation of m_value
     */
    QString doubleText() const;
    /**
     * @brief doubleArrayText
     * @details responsible for converting m_value to text when m_type is double array
     * @return QCP file compatible text representation of m_value
     */
    QString doubleArrayText() const;

  public:
    //constructors
    /**
     * @brief QcpVariable
     * @details default constructor
     */
    QcpVariable();
    /**
     * @brief QcpVariable
     * @details Templated constructor for creating QCP Variable with a value
     * @param type: The type of value that is being provided
     * @param value: the value to be stored inside the QVariant
     * @param name: The name of the variable
     */
    template <typename T> QcpVariable(const QString& name, Type type, T value)
    {
      init(name, type, value);
    } //end  template <typename T> QcpVariable(Type type, T value)
    QcpVariable(const QString& name);
    /**
     * @brief QcpVariable
     * @details copy constructor
     * @param toCopy: QcpVariable to copy from
     */
    QcpVariable(const QcpVariable& toCopy);
    /**
     * @brief ~QcpVariable
     * @details destructor
     */
    ~QcpVariable();

    //public functions
    /**
     * @brief fileText
     * @details Generates the text to be written to the file for this variable
     * @return QString containing this variable in file ready text format
     * @return or blank if the typeing information got messed up
     */
    QString fileText() const;
    /**
     * @brief changeValue
     * @details Changes the value stored within the QVariant
     * @details Can also be used to change the type of value being stored
     * @param newType: The type of the new data you're providing
     * @param newValue: The new value to be stored in the QVariant
     * @return True if the assignment works, false otherwise
     */
    template <typename T> bool changeValue(Type newType, T newValue)
    {
      //TODO figure out a way to ensure type is correct for value, may be impossible
      m_type = newType;
      m_value = QVariant::fromValue(newValue);
    }

    //getters
    /**
     * @brief getType
     * @details Returns the type of value being stored
     * @return Enum version of the type being stored
     */
    Type getType() const;
    /**
     * @brief getValue
     * @details Gets the value that is stored within the QVariant, converted to type T
     * @return Value stored in the QVariant, or an empty construction if it failed
     */
    template <typename T> T getValue() const
    {
      if (m_value.canConvert<T>())
      {
        return m_value.value<T>();
      } //end  if (m_value.canConvert<T>())
      else
      {
        if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
        {
          std::cout << "ERROR: Cannot convert " << m_name.toStdString()
                    << " to type " << typeid(T).name() << std::endl;
          std::cout << "Returning a default construction of the type" << std::endl;
        } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
        return T();
      } //end  else
    } //end  template <typename T> T getValue() const
    /**
     * @brief getName
     * @details Returns the name of the variable
     * @return variable's name
     */
    QString getName() const;

    //setters
    /**
     * @brief setName
     * @details Sets the name of the variable
     * @param name: Variable's name
     */
    void setName(const QString& name);

    //op overloads
    /**
     * @brief operator =
     * @details copy assignment operator
     * @param toCopy: Value to copy from
     * @return Reference to the newly copied object
     */
    QcpVariable& operator=(const QcpVariable& toCopy);
    /**
     * @brief operator =
     * @details Assignment operator for storing a double in the variable
     * @param value: value to be stored in variable
     * @return Reference to the newly copied object
     */
    QcpVariable& operator=(double value);
    /**
     * @brief operator =
     * @details Assignment operator for storing an array of doubles in the variable
     * @param value: Value to be stored in the variable
     * @return Reference to the newly copied object
     */
    QcpVariable& operator=(const QVector<double>& value);
    /**
     * @brief operator =
     * @details Assignment operator for storing an array of doubles from std vector
     * @param value: std::vector containing desired values to store in variable
     * @return  Reference to the newly copied object
     */
    QcpVariable& operator=(const std::vector<double>& value);
};

#endif //end #ifndef QCP_VARIABLE_H
