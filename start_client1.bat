cd /d "%~dp0"
set ClientExePath=%cd%\Build\WindowsClient\PingPongNetClient.exe

start "" "%ClientExePath%" -WINDOWED -FullscreenMode=2 -ResX=640 -ResY=480 -ExecCmds="open 127.0.0.1"
