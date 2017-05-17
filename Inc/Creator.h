#ifndef CREATOR_H
#define CREATOR_H

//ui include
#include "ui_Creator.h"

#include "Project.h"

#include <iostream>

class Creator: public QMainWindow
{
    Q_OBJECT

  private:
    //member variables
    Ui_creator* m_ui;

  public:
    //constructors
    Creator();
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
}; //end class Creator: public QMainWindow

#endif //end ifndef CREATOR_H

