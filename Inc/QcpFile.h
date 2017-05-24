#ifndef QCP_FILE_H
#define QCP_FILE_H

#include <QString>

#include <vector>

#include "CommandOptions.h"
#include "QcpGroup.h"

class QcpFile
{
  private:
    //member variables
    std::vector<QcpGroup> m_groups; //groups contained within the file
    QString m_comment; //comment displayed at the top of the file

    //private functions
    /**
     * @brief init
     * @details initializes all of the member variables of the class
     * @param groups: list of groups the file contains
     * @param comment: comment displayed at top of the file
     */
    void init(std::vector<QcpGroup> groups, const QString& comment);

  public:
    //constructors
    /**
     * @brief QcpFile
     * @details default constructor
     */
    QcpFile();
    /**
     * @brief QcpFile
     * @details constructor that takes a list of gropus and optional comment
     * @param groups: groups contained in the file
     * @param comment: comment displayed at the top of the file
     */
    QcpFile(std::vector<QcpGroup> groups, const QString& comment = "");

    //public functions
    /**
     * @brief size
     * @details returns the number of groups contained in the file
     * @return size of group list
     */
    size_t size();
    /**
     * @brief fileText
     * @details converts the object into file printable text
     * @return vector of vector of variable strings. first vector represents the file
     * @return the second vector represents each group in the file
     */
    std::vector<std::vector<QString>> fileText();
    /**
     * @brief addGroup
     * @details adds a group to the file
     * @param toAdd: group to add to the file
     * @return true if the group was successfully added
     */
    bool addGroup(const QcpGroup& toAdd);
    /**
     * @brief removeGroup
     * @details removes a group from the file
     * @param toRemove: reference to the group to remove
     */
    void removeGroup(const QcpGroup& toRemove);
    /**
     * @brief removeGroup
     * @details removes a group from the file
     * @param index location of group in the list to remove
     */
    void removeGroup(int index);
    /**
     * @brief removeGroup
     * @details removes a group from the file
     * @param toRemoveName: name of the group to remove
     */
    void removeGroup(const QString& toRemoveName);
    /**
     * @brief clearGroups
     * @details removes all the groups from the file
     */
    void clearGroups();

    //getters
    /**
     * @brief getComment
     * @details returns the comment at the top of the file
     * @return comment at the top of the file
     */
    QString getComment();

    //setters
    /**
     * @brief setComment
     * @details changes the comment at the top of the file
     * @param comment: new comment at the top of the file
     */
    void setComment(const QString& comment);

    //op overloads
    /**
     * @brief operator []
     * @details provides direct access to the internal group vector
     * @param index: index of desired element
     * @return refernce to the desired element
     */
    QcpGroup& operator[](const int index);
    /**
     * @brief operator []
     * @details const version of operator[]
     * @param index: index of desired element
     * @return const ref to the desired element
     */
    const QcpGroup& operator[](const int index) const;
};

#endif //end #ifndef QCP_FILE_H
