#ifndef NEW_DIALOG_H
#define NEW_DIALOG_H

//ui include
#include "ui_NewDialog.h"

#include "Manager.h"
#include "CommandOptions.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo> //checking if file exists
#include <QDir>

#include <iostream>
#include <memory> //shared_ptr
#include <cctype> //isalnum

class NewDialog: public QWidget
{
    Q_OBJECT

  private:
    //normalize path state machine states
    enum class State
    {
      PREV_WAS_SLASH,
      PREV_WAS_CHAR,
      INIT
    }; //end  enum class STATE
    //member variables
    Ui_NewDialog* m_ui; //user interface
    std::shared_ptr<Manager> m_manager; //reference to global manager

    //private functions
    /**
     * @brief isGoodPath
     * @details Checks if the input string represents a path directory on the computer
     * @param filePath: the path to check if it exists and is a directory
     * @return true if the path exists
     */
    bool isGoodPath(const QString& filePath);
    /**
     * @brief normalizePath
     * @details Removes any extra '/' or '\' characters from a path. Also normalizes
     * @details all slashes to '/'
     * @param path: the path to be normalized
     */
    void normalizePath(QString& path);

  public:
    //constructors
    /**
     * @brief NewDialog
     * @details constructor for NewDialog
     * @param manager: reference to the global manager for the project
     * @param parent: parent who created this widget
     */
    NewDialog(std::shared_ptr<Manager> manager, QWidget* parent = nullptr);
    /**
     * @brief ~NewDialog
     * @details destructor for the NewDialog
     */
    ~NewDialog();

  signals:
    /**
     * @brief newProject
     * @details Signals that a new project is to be creates at a given location
     * @param filePath: path where project should be created. contains the projects name
     */
    void newProject(const QString& filePath); //name is part of the path

  public slots:
    /**
     * @brief browseButtonClicked
     * @details handler for when the browse button is clicked
     */
    void browseButtonClicked();
    /**
     * @brief createButtonClicked
     * @details handler for when the creation button is clicked
     */
    void createButtonClicked();
    /**
     * @brief cancelButtonClicked
     * @details handler for when the cancel button is clicked
     */
    void cancelButtonClicked();
    /**
     * @brief nameTextChanged
     * @details handler for when the user changes the name text field. Ensures that
     * @details the name can only be alphanumeric characters
     * @param newText: Text the user tried to change the field to
     */
    void nameTextChanged(const QString& newText);
    /**
     * @brief locationTextChanged
     * @details handler for when the location text field is finished being edited
     * @details ensures that the text field can only contain valid paths
     */
    void locationTextChanged();
    /**
     * @brief projectTypeChanged
     * @details handler for when the user changes the project type combo box
     */
    void projectTypeChanged();
}; //end class NewDialog: public QWidget

#endif //end ifndef NEW_DIALOG_H
