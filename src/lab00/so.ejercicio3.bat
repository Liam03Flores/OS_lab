@echo off 
set /p tiempo=Ingresa el tiempo en segundos para el apagado: 
echo La computadora se apagará en %tiempo% segundos. 
C:\Windows\System32\shutdown.exe /s /t %tiempo% 
timeout /t 10 /nobreak >nul 
C:\Windows\System32\shutdown.exe /a 
echo El apagado programado ha sido cancelado después de 10 segundos. 
pause
