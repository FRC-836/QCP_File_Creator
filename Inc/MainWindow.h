#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

//ui include
#include "ui_MainWindow.h"

//QT includes
#include "QString"

class MainWindow: public QMainWindow
{
  private:
    //member variables
    Ui_MainWindow* m_ui;

  public:
    //constructors
    MainWindow();
    ~MainWindow();

    //public functions

    //getters

    //setters

  signals:
    void createProject(const QString& filePath);
    void openProject(const QString& filePath, bool openInEditor);

  public slots:
    void newButtonPressed();
    void openButtonPressed();
    void editorButtonPressed();
    void recentFileClicked(QListWidgetItem* item);

}; //end class MainWindow: public QMainWindow

#endif //end ifndef MAIN_WINDOW_H
