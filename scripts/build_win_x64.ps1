$ProjectDir = Split-Path -Parent $PSScriptRoot

cmake "$ProjectDir" --preset="vs2022-deb"
if(!$?) { Exit $LASTEXITCODE }

cmake --build "$ProjectDir" -- preset="vs2022-deb"
if(!$?) { Exit $LASTEXITCODE }
