param (
    [Parameter(Mandatory=$true)]
    [ValidateSet("vs2022-deb","vs2022-rel", "vs2022-deb-shared", "vs2022-rel-shared")]$Preset
)   

$ProjectDir = Split-Path -Parent $PSScriptRoot
$BuildDir = Join-Path $ProjectDir "build\$Preset"

# Hacky way to figure whether it's a
# debug/release build as presets don't
# support it just yet
$Configuration = "Debug"
if ($Preset -like "*rel*")
{
    $Configuration = "Release"
}

cmake --install "$BuildDir" --config $Configuration
if(!$?) { Exit $LASTEXITCODE }
