#include <QApplication>
#include <QCommandLineParser>

#include <iostream>

#include "MainWindow.h"
#include "CommandOptions.h"

//forward declarations
bool parseCmd(QCommandLineParser& parser);

int main(int argc, char** argv)
{
  //setup q application
  QApplication app(argc, argv);

  QCommandLineParser parser;

  if (!parseCmd(parser))
  {
    parser.showHelp();
    exit(1);
  } //end  if (!parseCmd(app))

  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "debug level: " << CmdOptions::verbosity << std::endl;
  }

  //create and run main window
  MainWindow mainWindow;
  mainWindow.show();

  //run the application
  return app.exec();
} //end int main(int argc, char** argv)


bool parseCmd(QCommandLineParser& parser)
{
  //--------------------------------------------------
  //setup the cmd parser
  //--------------------------------------------------
  parser.addHelpOption();
  parser.setApplicationDescription("Used to create and modify QCP projects");

  //debug level option
  QCommandLineOption debugOption({"v", "verbosity"}, "Verbosity of the info printed",
                                      "debugLevel", "1");
  parser.addOption(debugOption);

  //--------------------------------------------------
  //parse the arguments into structure
  //--------------------------------------------------
  parser.process(QCoreApplication::arguments());
  bool convesionSuccess;

  //handle debug level processing
  int debugLevel = parser.value("verbosity").toInt(&convesionSuccess);
  if (convesionSuccess)
  {
    switch(debugLevel)
    {
      case 0:
        CmdOptions::verbosity = CmdOptions::DEBUG_LEVEL::NO_OUTPUT;
        break;
      case 1:
        CmdOptions::verbosity = CmdOptions::DEBUG_LEVEL::ERRORS_ONLY;
        break;
      case 2:
        CmdOptions::verbosity = CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS;
        break;
      case 3:
        CmdOptions::verbosity = CmdOptions::DEBUG_LEVEL::ALL_INFO;
        break;
      default:
        CmdOptions::verbosity = CmdOptions::DEBUG_LEVEL::ERRORS_ONLY;
        break;
    } //end  switch(debugLevel)
  } //end  if (convesionSuccess)
  else
  {
    return false;
  } //end  else

  //all command args processed sucessfully
  return true;
}  //end bool parseCmd(QCommandLineParser& parser)
