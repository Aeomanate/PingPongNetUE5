chcp 65001

set UESourcesPath = D:\Prog\Env\IDE\UE_5.5

%UESourcesPath%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun ^
-project="%cd%\PingPongNet.uproject" ^
-platform=Win64 ^
-clientconfig=Shipping ^
-archivedirectory=build\client ^
-stagingdirectory=stage ^
-build -cook -package -stage -archive -pak -allmaps -client

pause

%UESourcesPath%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun ^
-project="%cd%\PingPongNet.uproject" ^
-platform=Win64 ^ 
-serverconfig=Shipping ^ 
-archivedirectory=build\server ^
-stagingdirectory=stage ^
-build -cook -package -stage -archive -pak -allmaps -server

pause