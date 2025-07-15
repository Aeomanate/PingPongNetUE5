cd /d "%~dp0"
set ServerExePath=%cd%\Build\WindowsServer\PingPongNetServer.exe

start "" "%ServerExePath%" -log