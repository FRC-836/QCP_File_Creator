//Qt includes
#include <QApplication>

//c++ included
#include <iostream>

//custom widget includes
#include "MainWindow.h"

//temporary
#include "ConstCreator.h"
#include "Creator.h"

int main(int argc, char** argv)
{
  //setup q application
  QApplication app(argc, argv);

  //create and run main window
  MainWindow mainWindow;
  mainWindow.show();

  //run the application
  return app.exec();
} //end int main(int argc, char** argv)
