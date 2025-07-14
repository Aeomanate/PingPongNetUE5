chcp 65001

set UESourcesPath = D:\Prog\Env\IDE\UE_5.5
set ClientPath = Build\Client
set ServerPath = Build\Server

%UESourcesPath%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun ^
-project="%cd%\PingPongNet.uproject" ^
-platform=Win64 ^
-clientconfig=Development ^
-archivedirectory=%ClientPath% ^
-stagingdirectory=Stage ^
-build -cook -package -stage -archive -pak -allmaps -client

pause

%UESourcesPath%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun ^
-project="%cd%\PingPongNet.uproject" ^
-platform=Win64 ^ 
-serverconfig=Development ^ 
-archivedirectory=%ServerPath% ^
-stagingdirectory=Stage ^
-build -cook -package -stage -archive -pak -allmaps -server

pause