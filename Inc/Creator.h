#ifndef CREATOR_H
#define CREATOR_H

//ui include
#include "ui_Creator.h"

#include "Project.h"
#include "CommandOptions.h"

#include <iostream>
#include <memory>

#include "Manager.h"

class Creator: public QMainWindow
{
    Q_OBJECT

  private:
    //member variables
    Ui_creator* m_ui;
    std::unique_ptr<Project> m_project;

    //private functions
    void loadProject();

  public:
    //constructors
    Creator(std::unique_ptr<Project> project = nullptr);
    ~Creator();

    //public functions

    //getters

    //setters

  signals:
    void exportProject(const Project& project);
    void saveProject(const Project& project);
    void newFile(const QString& filePath, const QString& fileName);
    void groupChangeRequest(const QcpGroup& newGroup);

  public slots:
    void constRequestHandler(const QString& constName, QcpVariable& variable);
    void newConstClicked();
    void saveClicked();
    void exportClicked();
    void groupBoxValueChanged(int index);
    void fileBoxValueChanged(int index);
    void varExplorerClicked(QTreeWidgetItem* item);
    void projectItemClicked(QTreeWidgetItem* item);
    void constItemClicked(QListWidgetItem* item);
    void createConst(const QcpVariable& value);
    static void createProject(const QString& filePath);
    static void openProject(const QString& filePath, bool openInEditor);
}; //end class Creator: public QMainWindow

#endif //end ifndef CREATOR_H

