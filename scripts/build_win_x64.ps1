param (
    [Parameter(Mandatory=$true)]
    [ValidateSet("vs2022-deb","vs2022-rel", "vs2022-deb-shared", "vs2022-rel-shared")]$Preset
)

# Need this to load cl.exe
& "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

$ProjectDir = Split-Path -Parent $PSScriptRoot

cmake "$ProjectDir" --preset="$Preset"
if(!$?) { Exit $LASTEXITCODE }

cmake --build --preset="$Preset"
if(!$?) { Exit $LASTEXITCODE }
