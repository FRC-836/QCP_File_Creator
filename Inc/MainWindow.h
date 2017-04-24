#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

//ui include
#include "ui_MainWindow.h"

class MainWindow: public QMainWindow
{
  private:
    Ui_MainWindow* m_ui;
  public:
    MainWindow();
};

#endif //end ifndef MAIN_WINDOW_H
