#ifndef QCP_GROUP_H
#define QCP_GROUP_H

#include <QVector>
#include <QString>

#include "CommandOptions.h"
#include "QcpVariable.h"

class QcpGroup
{
  private:
    //member variables
    QVector<QcpVariable> m_vars;

  public:
    //constructors
    QcpGroup();
    QcpGroup(const QVector<QcpVariable>& vars);

    //public functions
    size_t size();
    QString fileText();

    //op overloads
    QcpVariable& operator[](const int index);
    const QcpVariable& operator[](const int index) const;
}; //end class QcpGroup

#endif //end #define QCP_GROUP_H
