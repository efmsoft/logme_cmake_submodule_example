#include <Logme/Logme.h>

int main()
{
  LogmeI("Example started: demonstrating log levels and colorized output");
  LogmeW("This is a demonstration warning (not an actual problem)");
  LogmeE("This is a demonstration error message (example only)");
  LogmeI("Example finished successfully");

#ifndef LOGME_DISABLE_STD_FORMAT
  fLogmeI("This message is shown only when std::format is supported by the system");
#endif

  return 0;
}
