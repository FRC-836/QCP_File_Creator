#include "Manager.h"

//--------------------------------------------------
//constants
//--------------------------------------------------
const QString Manager::FILE_EXTENSION = ".qcprj";

//--------------------------------------------------
//constructors
//--------------------------------------------------
Manager::Manager()
{
} //end Manager::Manager()

//--------------------------------------------------
//public slots
//--------------------------------------------------
Manager::createProject(const QString& filePath)
{
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "recieving command to create project at: "
              << filePath.toStdString() << std::endl;
  }//end  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
Manager::openProject(const QString& filePath, bool openInEditor)
{
}
