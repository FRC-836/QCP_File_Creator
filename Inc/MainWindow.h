#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_MainWindow.h"
#include "Manager.h"
#include "NewDialog.h"
#include "CommandOptions.h"

#include <QString>
#include <QFileDialog>

#include <memory>
#include <iostream>

/**
 * @brief The MainWindow class
 * @details Main window that is displayed when the program is first run.
 *          The user can create or open projects through here.
 */
class MainWindow: public QMainWindow
{
    Q_OBJECT

  private:
    //member variables
    Ui_MainWindow* m_ui; //UI container
    std::shared_ptr<Manager> m_manager;

    //private functions
    /**
     * @brief getOpenPath
     * @details finds the path where the project the user wants to open is.
     * @return: The path where the project is located, blank if the op was canceled
     */
    QString getOpenPath();

  public:
    //constructors
    /**
     * @brief MainWindow constructor
     */
    MainWindow();
    /**
     * @brief MainWindow destructor
     */
    ~MainWindow();

  signals:
    /**
     * @brief openProject
     * @details emitted when an already existing project needs opening
     * @param filePath: The path to the already existing project
     * @param openInEditor: true if the user wants the project opened in editor mode
     */
    void openProject(const QString& filePath, bool openInEditor);

  public slots:
    /**
     * @brief newButtonPressed
     * @details handler function for when the create new project button is pressed
     */
    void newButtonPressed();
    /**
     * @brief openButtonPressed
     * @details handler function for when the open file button is pressed
     */
    void openButtonPressed();
    /**
     * @brief editorButtonPressed
     * @details handler function for when the open editor button is pressed
     */
    void editorButtonPressed();
    /**
     * @brief recentFileClicked
     * @details handler function for when an item in the recently opened
     *          items list is clicked
     * @param item: pointer to the item that was pressed
     */
    void recentFileClicked(QListWidgetItem* item);
    /**
     * @brief newProjectChosen
     * @details Called when a project is created new. Takes the information necessary
     *          to create the project and passes it to Manager
     * @param filePath: path where the project should be stored
     * @param projectName: name of the project
     */

}; //end class MainWindow: public QMainWindow

#endif //end ifndef MAIN_WINDOW_H
