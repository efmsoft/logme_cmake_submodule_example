#include <Logme/Logme.h>
#include <Logme/Template.h>
#include <Logme/AnsiColorEscape.h>

void ConfigDemo();

int main(int argc, char* argv[])
{
  LogmeI("Example started: demonstrating log levels and colorized output");
  LogmeW("This is a demonstration warning (not an actual problem)");
  LogmeE("This is a demonstration error message (example only)");
  LogmeI("Example finished successfully");

#ifndef LOGME_DISABLE_STD_FORMAT
  fLogmeI("This message is shown only when std::format is supported by the system");
#endif

// If the `USE_ALLSTAT` option is enabled, the output message will show not error 
// code 13, but the name of the constant.
//
// Using the Override is not mandatory. You can simply omit the first parameter 
// when calling the `LogmeW` macro. However, if it is specified, the module name and 
// line number will be added when printing the message.

  Logme::Override ovr;
  ovr.Add.Location = Logme::Detality::DETALITY_SHORT;

  int errno_value = 13; // Example errno value
  LogmeW(ovr, "errno_value: %s", ERRNO_STR(errno_value));

  ConfigDemo();
  return 0;
}

const char* Config = R"json(
{
  "logger": {
    "flags": {
      "default": {
        "Timestamp": "tz",
        "Signature": true,
        "Method": true,
        "ThreadID": true,
        "Highlight": false,
        "eol": true
      }
    },
    "channels": [
      {
        "name": "",
        "level": "info",
        "flags": "default",
        "backends": [
          {
            "type": "ConsoleBackend",
            "build": "any"
          },
          {
            "type": "FileBackend",
            "append": true,
            "max-size": "16Mb",
            "file": "{%ROOT_LOG}"
          }
        ]
      }
    ]
  }
}
")json";

static void ConfigDemo()
{
  // Of course, it’s better to load the configuration from a file on disk. 
  // In this example, however, it’s done from an in-memory string for the 
  // sake of compactness. Typically, logging settings are just a section 
  // within a larger application configuration file. In this example, we 
  // placed the settings into the `"logger"` section.

  // Please note that if USE_JSONCPP is not defined, the configuration will 
  // not be loaded. However, it is still safe to call the LoadConfiguration 
  // function — it will simply return without doing anything.

  // When loading the configuration, variable substitution can be used. 
  // Variable values can be set programmatically by calling `EnvSetVar`. In 
  // this case, the file name is specified via a variable.
  // If the file name does not contain a full path, it is resolved relative 
  // to the Home Directory (see `Logger::SetHomeDirectory`). If the Home Directory 
  // was not explicitly set, it defaults to the directory from which the application 
  // is launched.
  Logme::EnvSetVar("ROOT_LOG", "root_log.log");

  if (Logme::Instance->LoadConfiguration(Config, "logger"))
  {
    LogmeI("Logger configuration loaded successfully from in-memory string");
  }
  else
  {
#ifdef USE_JSONCPP
    LogmeE("Failed to load logger configuration");
#endif
  }
}