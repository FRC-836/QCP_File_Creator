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
void Manager::createProject(const QString& filePath)
{
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "recieving command to create project at: "
              << filePath.toStdString() << std::endl;
  }//end  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void Manager::openProject(const QString& filePath, bool openInEditor)
{
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "recieving command to open project at: "
              << filePath.toStdString() << " ";
    if (openInEditor)
    {
      std::cout << "in editor mode";
    } //end  if (openInEditor)
    else
    {
      std::cout << "in normal mode";
    } //end  else
    std::cout << std::endl;
  } //end  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void Manager::exportToQcp(const Project& projectName)
{
}
void Manager::saveProject(const Project& toSave, const QString& location)
{
}
