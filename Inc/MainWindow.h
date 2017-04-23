#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

//ui include
#include "ui_MainWindow.h"

class MainWindow: public QMainWindow
{
  private:
    Ui_MainWindow* ui;
  public:
    MainWindow()
    {
      ui = new Ui_MainWindow();
      ui->setupUi(this);
    }
};

#endif //end ifndef MAIN_WINDOW_H
