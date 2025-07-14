chcp 65001

D:\Prog\Env\IDE\UE_5.5\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun ^
-project="%cd%\PingPongNet.uproject" ^
-platform=Win64 ^
-clientconfig=Shipping ^
-archivedirectory=build\client ^
-stagingdirectory=stage ^
-build -cook -package -stage -archive -pak -allmaps -client

pause

D:\Prog\Env\IDE\UE_5.5\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun ^
-project="%cd%\PingPongNet.uproject" ^
-platform=Win64 ^ 
-serverconfig=Shipping ^ 
-archivedirectory=build\server ^
-stagingdirectory=stage ^
-build -cook -package -stage -archive -pak -allmaps -server

pause