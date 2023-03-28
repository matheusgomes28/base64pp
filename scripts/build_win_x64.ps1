param (
    [Parameter(Mandatory=$true)]
    [ValidateSet("vs2022-deb","vs2022-rel")]$Preset
)   

$ProjectDir = Split-Path -Parent $PSScriptRoot

cmake "$ProjectDir" --preset="$Preset"
if(!$?) { Exit $LASTEXITCODE }

cmake --build --preset="$Preset"
if(!$?) { Exit $LASTEXITCODE }
