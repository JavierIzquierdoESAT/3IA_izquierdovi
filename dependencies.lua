SourceCode = {}

SourceCode["Common"] = "%{wks.location}/common/src"

IncludeDirs = {}

IncludeDirs["ESAT"] = "%{wks.location}/deps/include/"
IncludeDirs["Common"] = "%{wks.location}/common/include"

Library = {};
Library["ESAT"] = {};
Library["System"] = {"opengl32", "gdi32", "shell32"};

Library["ESAT"]["Debug"] = "%{wks.location}/deps/bin/ESAT_d.lib"
Library["ESAT"]["Release"] = "%{wks.location}/deps/bin/ESAT.lib"