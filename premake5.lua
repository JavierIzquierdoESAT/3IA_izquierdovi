include "dependencies.lua"

workspace "DungeonGenerator"
  architecture "x86"

  configurations
  {
    "Debug",
    "Release",    
  }

  flags
  {
    "MultiProcessorCompile"
  }

group "Projects"
  include "Projects/Digger"
  include "Projects/TrialError"
  include "Projects/Isaac"
group ""

