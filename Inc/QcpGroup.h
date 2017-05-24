#ifndef QCP_GROUP_H
#define QCP_GROUP_H

#include <QString>

#include <vector>

#include "CommandOptions.h"
#include "QcpVariable.h"

class QcpGroup
{
  private:
    //member variables
    std::vector<QcpVariable> m_vars;
    QString m_comment;
    QString m_name;

    //private functions
    init(const std::vector<QcpVariable>& vars, const QString& name,
         const QString& comment);

  public:
    //constructors
    QcpGroup();
    QcpGroup(const std::vector<QcpVariable>& vars, const QString& name);
    QcpGroup(const std::vector<QcpVariable>& vars, const QString& name,
             const QString& comment);

    //public functions
    size_t size();
    std::vector<QString> fileText();
    bool addVar(const QcpVariable& toAdd);
    void removeVar(const QcpVariable& toRemove);
    void removeVar(int index);
    void removeVar(const QString& toRemoveName);
    void clearVars();

    //getters
    QString getComment();
    QString getName();

    //setters
    void setComment(const QString& comment);
    void setName(const QString& name);

    //op overloads
    QcpVariable& operator[](const int index);
    const QcpVariable& operator[](const int index) const;
}; //end class QcpGroup

#endif //end #define QCP_GROUP_H
