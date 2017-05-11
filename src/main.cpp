//Qt includes
#include <QApplication>

//c++ included
#include <iostream>

//custom widget includes
#include "MainWindow.h"

//temporary
#include "NewDialog.h"
#include "SingleVarCreator.h"
#include "MultiVarCreator.h"
#include "Creator.h"
#include "Editor.h"
#include "VarCreator.h"

int main(int argc, char** argv)
{
  //setup q application
  QApplication app(argc, argv);

  //create and run main window
  MainWindow mainWindow;
  mainWindow.show();

  //testing
  Creator creator;
  creator.show();

  //run the application
  return app.exec();
} //end int main(int argc, char** argv)
