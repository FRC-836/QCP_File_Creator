//Qt includes
#include <QApplication>

//c++ included
#include <iostream>

//custom widget includes
#include "MainWindow.h"

//temporary
#include "NewDialog.h"
#include "SingleVarCreator.h"

int main(int argc, char** argv)
{
  //setup q application
  QApplication app(argc, argv);

  //create and run main window
  MainWindow mainWindow;
  mainWindow.show();

  //temporary just to see how they look
  NewDialog newdialog;
  newdialog.show();
  SingleVarCreator singleVarCreator;
  singleVarCreator.show();

  //run the application
  return app.exec();
}
