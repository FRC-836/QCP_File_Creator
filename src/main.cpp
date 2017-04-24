//Qt includes
#include <QApplication>

//c++ included
#include <iostream>

//custom widget includes
#include "MainWindow.h"

int main(int argc, char** argv)
{
  //setup q application
  QApplication app(argc, argv);

  //create and run main window
  MainWindow mainWindow;
  mainWindow.show();

  //run the application
  return app.exec();
}
