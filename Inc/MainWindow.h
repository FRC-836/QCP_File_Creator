#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

//ui include
#include "ui_MainWindow.h"

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
};

#endif //end ifndef MAIN_WINDOW_H
