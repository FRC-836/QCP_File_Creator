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
    QcpVariable();
    template <typename T> QcpVariable(Type type, T value, const QString& name)
    {
    } //end  template <typename T> QcpVariable(Type type, T value)
    QcpVariable(const QcpVariable& toCopy);
    ~QcpVariable();

    //public functions
    QString fileText();
    template <typename T> bool changeValue(Type newType, T newValue)
    {
    }

    //getters
    Type getType();
    template <typename T> getValue()
    {
    }
    QString getName();

    //setters
    void setName(const QString& name);

    //op overloads
    QcpVariable& operator=(const QcpVariable& toCopy);
    QcpVariable& operator=(double value);
    QcpVariable& operator=(const QVector<double>& value);
};

#endif //end #ifndef QCP_VARIABLE_H
