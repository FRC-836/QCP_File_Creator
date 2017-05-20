#ifndef QCP_CREATOR_COMMAND_OPTIONS_H
#define QCP_CREATOR_COMMAND_OPTIONS_H

#include <ostream>

struct CmdOptions
{
  public:
    //enumbs
    enum class DEBUG_LEVEL
    {
      NO_OUTPUT,
      ERRORS_ONLY,
      ERRORS_AND_WARNINGS,
      ALL_INFO
    };

    //options and arguments
    static DEBUG_LEVEL verbosity;
}; //end struct CommandOptions

std::ostream& operator<<(std::ostream& out, CmdOptions::DEBUG_LEVEL toPrint);

#endif
