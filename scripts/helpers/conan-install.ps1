param (
    [Parameter(Mandatory=$true)]
    [ValidateSet("Debug","Release")]$BuildType
)   

# Need "if(!$?) { Exit $LASTEXITCODE }" after
# every external command call as everything
# needs to work for the build

# Install conan with chocolatey
choco install conan --version=2.0.1 --installargs '/PathType:Machine' -y --no-progress
if(!$?) { Exit $LASTEXITCODE }

# Set this because refreshenv doesn't work
# on the same powershell session
if (-not(Get-Command conan -ErrorAction SilentlyContinue))
{
    New-Alias -Name conan -Value "$Env:ProgramFiles\Conan\conan\conan.exe"
}

conan profile detect --force
if(!$?) { Exit $LASTEXITCODE }

$ConanProfileFile = "$(conan profile path default)"
if(!$?) { Exit $LASTEXITCODE }

# Update the conan profiles to build for
# debug with MTd runtime on MSVC
$ConanProfile = Get-Content -Path "$(conan profile path default)"
if(!$?) { Exit $LASTEXITCODE }
$ConanProfile = $ConanProfile -Replace "build_type=Release", "build_type=Debug"
$ConanProfile = $ConanProfile -Replace "compiler.runtime=dynamic", "compiler.runtime=static"
Write-Output "---- New conan profile -----"
Set-Content -Path $ConanProfileFile -Value $ConanProfile
Write-Output $ConanProfile

# Install all dependencies
$ProjectDir = (Get-Item "$PSScriptRoot").parent.parent.FullName
$ConanOutputDir = "${ProjectDir}/conan/deb"
if ($BuildType -eq "Release")
{
    $ConanOutputDir = "${ProjectDir}/conan/rel"
}

conan install `
  --output-folder="${ConanOutputDir}" `
  --build=missing `
  "${ProjectDir}"
if(!$?) { Exit $LASTEXITCODE }
