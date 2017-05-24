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
    /**
     * @brief init
     * @details Initialization function called by all constructors
     * @param vars Variables to be stored in the group
     * @param name Name of the group
     * @param comment Comment for the top of the group
     */
    init(const std::vector<QcpVariable>& vars, const QString& name,
         const QString& comment);

  public:
    //constructors
    /**
     * @brief QcpGroup
     * @details Default constructor
     */
    QcpGroup();
    /**
     * @brief QcpGroup
     * @details constructor that assigns a variable list and name to the group
     * @param vars: variables to store in the group
     * @param name: name of the group
     */
    QcpGroup(const std::vector<QcpVariable>& vars, const QString& name);
    /**
     * @brief QcpGroup
     * @details Constructor that takes a group of variables, name, and comment
     * @param vars Variables to be stored in the group
     * @param name Name of the group
     * @param comment Comment for the top of the group
     */
    QcpGroup(const std::vector<QcpVariable>& vars, const QString& name,
             const QString& comment);

    //public functions
    /**
     * @brief size
     * @details Gets the number of variables in the group
     * @return number of vars in the group
     */
    size_t size() const;
    /**
     * @brief fileText
     * @details Generates the proper text to be stored in the QCP file fo the group
     * @return Vector of strings where each element represents the text of a given variable from the group
     */
    std::vector<QString> fileText() const;
    /**
     * @brief addVar
     * @details add a variable to the group
     * @param toAdd: variable to add
     * @return True if the insertion was successful
     */
    bool addVar(const QcpVariable& toAdd);
    /**
     * @brief removeVar
     * @details Remove a variable from the group
     * @param index: index of the variable to be removed
     */
    void removeVar(int index);
    /**
     * @brief removeVar
     * @details Remove a variable from the group
     * @param toRemoveName: Name of the variable to remove
     */
    void removeVar(const QString& toRemoveName);
    /**
     * @brief clearVars
     * @details Removes all the variables from the group
     */
    void clearVars();

    //getters
    /**
     * @brief getComment
     * @details Gets the comment at the top of the group
     * @return m_comment
     */
    QString getComment() const;
    /**
     * @brief getName
     * @details Gets the name of the group
     * @return m_name
     */
    QString getName() const;

    //setters
    /**
     * @brief setComment
     * @details Sets the comment to be displayed at the top of the group
     * @param comment: comment for the group
     */
    void setComment(const QString& comment);
    /**
     * @brief setName
     * @details Sets the name of the group
     * @param name: group name
     */
    void setName(const QString& name);

    //op overloads
    /**
     * @brief operator []
     * @details provides direct access to the variables array
     * @param index: index of desired variable
     * @return reference to the requested variable
     */
    QcpVariable& operator[](const int index);
    /**
     * @brief operator []
     * @details provides a way to grab const refs from the variables array
     * @param index: index of desired variable
     * @return const ref to the requested variable
     */
    const QcpVariable& operator[](const int index) const;
}; //end class QcpGroup

#endif //end #define QCP_GROUP_H
