set ClientExePath=%cd%\build\client\PingPongNetClient.exe

start "" "%ClientExePath%" -WINDOWED -FullscreenMode=2 -ResX=640 -ResY=480 -WinX=10 -WinY=50 -ExecCmds="open 127.0.0.1"
