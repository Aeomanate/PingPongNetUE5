@echo off
chcp 65001

set UESourcesPath=D:\Prog\Env\Libraries\UnrealEngine
set Project=%cd%\PingPongNet.uproject
set Config=%1
set StagePath=%cd%\Stage\%Config%
set ArchPath=%cd%\Build\%Config%
set Platform=Win64

echo Cleaning prev build
:: Backup old build if it exists
if exist "%ArchPath%" (
    setlocal enabledelayedexpansion
    set counter=1
    :find_available_name
    if exist "%ArchPath%_Old(!counter!)" (
        set /a counter+=1
        goto find_available_name
    )
    echo Moving existing build to %ArchPath%_Old(!counter!)
    move "%ArchPath%" "%ArchPath%_Old(!counter!)"
    endlocal
)

mkdir %ArchPath%

echo Copying starting scripts...
copy /Y "%cd%\start_server.bat" "%ArchPath%"
copy /Y "%cd%\start_client1.bat" "%ArchPath%"
copy /Y "%cd%\start_client2.bat" "%ArchPath%"

echo Starting UAT BuildCookRun...
echo Project: %Project%
echo Config: %Config%

explorer %ArchPath%

start "" %UESourcesPath%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun ^
-project=%Project% ^
-platform=%Platform% ^
-clientconfig=%Config% ^
-serverconfig=%Config% ^
-archivedirectory=%ArchPath% ^
-stagingdirectory=%StagePath% ^
-build -client -server -allmaps ^
-cook -stage -pak -archive ^
-crashreporter

pause
