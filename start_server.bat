chcp 65001
cd /d "%~dp0"
set ServerExePath=%cd%\WindowsServer\PingPongNetServer.exe

start "" "%ServerExePath%" -log 
