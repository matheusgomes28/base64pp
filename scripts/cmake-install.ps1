param (
    [Parameter(Mandatory=$true)]
    [ValidateSet("vs2022-deb","vs2022-rel")]$Preset
)   

$ProjectDir = Split-Path -Parent $PSScriptRoot
$BuildDir = Join-Path $ProjectDir "build\$Preset"

cmake --install "$BuildDir"
if(!$?) { Exit $LASTEXITCODE }
