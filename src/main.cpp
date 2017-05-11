//Qt includes
#include <QApplication>

//c++ included
#include <iostream>

//custom widget includes
#include "MainWindow.h"

//temporary
#include "ConstCreator.h"

int main(int argc, char** argv)
{
  //setup q application
  QApplication app(argc, argv);

  //create and run main window
  MainWindow mainWindow;
  mainWindow.show();

  //testing
  ConstCreator constCreator;
  constCreator.show();


  //run the application
  return app.exec();
} //end int main(int argc, char** argv)
