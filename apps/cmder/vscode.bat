@echo off
SET CurrentWorkingDirectory=%CD%
SET CMDER_ROOT=%~dp0
CALL %CMDER_ROOT%\vendor\init.bat
CD /D %CurrentWorkingDirectory%