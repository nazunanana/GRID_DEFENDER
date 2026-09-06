$ErrorActionPreference = "Stop"

$name = "GridDefender"
$version = "v1.0.0"
$dist = "release/$name"

# 前回の成果物を消す
if (Test-Path "release") { Remove-Item "release" -Recurse -Force }
New-Item -ItemType Directory -Path $dist -Force | Out-Null

# exe と素材をコピー
Copy-Item "build/$name.exe" -Destination $dist
Copy-Item "img", "audio" -Destination $dist -Recurse

# ZIP 化
Compress-Archive -Path $dist -DestinationPath "release/${name}_${version}.zip" -Force

Write-Host "done: release/${name}_${version}.zip"