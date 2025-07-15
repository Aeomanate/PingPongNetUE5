chcp 65001

set UESourcesPath=D:\Prog\Env\Libraries\UnrealEngine
set Project=%cd%\PingPongNet.uproject
set StagePath=%cd%\Stage
set ArchPath=%cd%\Build
set Config=Development
set Platform=Win64

%UESourcesPath%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun ^
-project=%Project% ^
-platform=%Platform% ^
-clientconfig=%Config% ^
-serverconfig=%Config% ^
-archivedirectory=%ArchPath% ^
-stagingdirectory=%StagePath% ^
-build -client -server -allmaps ^
-cook -stage -pak -archive ^
-nocompileeditor -compressed -multiprocess -NumCookers=7