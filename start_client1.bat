chcp 65001
cd /d "%~dp0"
set ClientExePath=%cd%\WindowsClient\PingPongNetClient.exe

start "" "%ClientExePath%" -log -WINDOWED -ResX=640 -ResY=480
