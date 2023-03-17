# Need "if(!$?) { Exit $LASTEXITCODE }" after
# every external command call as everything
# needs to work for the build

# Install conan with chocolatey
choco install conan --version=2.0.1 /PathType="Machine"
if(!$?) { Exit $LASTEXITCODE }
RefreshEnv
if(!$?) { Exit $LASTEXITCODE }

$ProjectDir = Split-Path -Parent $PSScriptRoot

conan profile detect --force
if(!$?) { Exit $LASTEXITCODE }

$ConanProfile = Get-Content -Path "$(conan profile path default)"
if(!$?) { Exit $LASTEXITCODE }
$ConanProfile = $ConanProfile -Replace "build_type=Debug", "build_type=Release"
$ConanProfile = $ConanProfile -Replace "compiler.runtime=dynamic", "compiler.runtime=static"
Set-Content -Path $ConanProfile -Value $ConanProfile
