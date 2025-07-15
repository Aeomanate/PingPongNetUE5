chcp 65001
cd /d "%~dp0"
set ClientExePath=%cd%\WindowsClient\PingPongNetClient.exe

start "" "%ClientExePath%" -WINDOWED -ResX=640 -ResY=480 -WinX=10 -WinY=50 -ExecCmds="open 127.0.0.1"
