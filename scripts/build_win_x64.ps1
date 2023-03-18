$ProjectDir = Split-Path -Parent $PSScriptRoot

cmake "$ProjectDir" --preset="vs2022-deb" -DCMAKE_VERBOSE_MAKEFILE="True"
if(!$?) { Exit $LASTEXITCODE }

cmake --build --preset="vs2022-deb"
if(!$?) { Exit $LASTEXITCODE }
