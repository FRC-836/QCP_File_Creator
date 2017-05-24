#ifndef QCP_VARIABLE_H
#define QCP_VARIABLE_H

#include <QVariant>
#include <QVector>

#include "CommandOptions.h"

enum class Type;

class QcpVariable
{
  private:
    //member variables
    QVariant m_value; //value the variable holds
    Type m_type; //type of the variable
    QString m_name; //name of the variable

  public:
    //public enums
    enum class Type
    {
      DOUBLE,
      DOUBLE_ARRAY
    };

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
    template <typename T> QcpVariable(Type type, T value, const QString& name)
    {
    } //end  template <typename T> QcpVariable(Type type, T value)
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
    }
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
};

#endif //end #ifndef QCP_VARIABLE_H
