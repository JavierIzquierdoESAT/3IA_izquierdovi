project "TrialError"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  staticruntime "Off"

  location "build"

  targetdir "bin"

  objdir "build"

  defines
  {
    "_CRT_SECURE_NO_WARNINGS"
  }

  includedirs
  {
    "src",
    "%{IncludeDirs.ESAT}",
    "%{IncludeDirs.Common}",
  }
  
  files
  {
    "%{IncludeDirs.Common}/**.hpp",
    "%{SourceCode.Common}/**.*",
    "src/**.*",
    "premake5.lua"
  }

  links
  {
    Library.System,
  }

  filter "configurations:Debug"
    defines { "DEBUG" }
    runtime "Debug"
    symbols "on"
    links {"%{Library.ESAT.Debug}"}

  filter "configurations:Release"
    defines { "NDEBUG" }
    runtime "Release"
    optimize "on"
    links {"%{Library.ESAT.Release}"}