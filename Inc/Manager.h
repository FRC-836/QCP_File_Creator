#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVector>

#include <iostream>

#include "CommandOptions.h"
#include "Project.h"

/**
 * @brief The Manager class
 */
class Manager : public QObject
{
    Q_OBJECT

  private:

  public:
    //constants
    static const QString FILE_EXTENSION;

    //constructors
    Manager();

    //pubolic functions

    //getters

    //setters

  signals:

  public slots:
    /**
     * @brief createProject
     * @details Creates a new QCP File Creator project.
     * @param filePath: path where the project sbould be created
     */
    createProject(const QString& filePath);
    /**
     * @brief openProject
     * @details opens an alerady existing QCP File Creator project
     * @param filePath: path where the project exists
     * @param openInEditor: true if the project should be opened in editor view
     */
    openProject(const QString&filePath, bool openInEditor);
}; //end class Manager

#endif //end #ifndef MANAGER_H
