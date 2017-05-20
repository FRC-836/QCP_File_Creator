#include "CommandOptions.h"

//member variable initializations
CmdOptions::DEBUG_LEVEL CmdOptions::verbosity = CmdOptions::DEBUG_LEVEL::ERRORS_ONLY;

//output operators for enums
std::ostream& operator<<(std::ostream& out, CmdOptions::DEBUG_LEVEL toPrint)
{
  switch(toPrint)
  {
    case CmdOptions::DEBUG_LEVEL::NO_OUTPUT:
      out << "No output";
      break;
    case CmdOptions::DEBUG_LEVEL::ERRORS_ONLY:
      out << "Errors only";
      break;
    case CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS:
      out << "Errors and warnings";
      break;
    case CmdOptions::DEBUG_LEVEL::ALL_INFO:
      out << "All info";
      break;
  }
  return out;
}

