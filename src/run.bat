@echo off
REM
setlocal enabledelayedexpansion

REM
set OUTPUT=dev.jam@1_1_0.exe

REM
set SOURCES=

REM
for /r %%f in (*.cpp) do (
    set SOURCES=!SOURCES! %%f
)

REM
clang++ !SOURCES! -o %OUTPUT% -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces -g -O0 C:/raylib/raylib/src/raylib.rc.data -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -L. -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -DPLATFORM_DESKTOP

REM
if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed. Please check for errors in your code.
    pause
    exit /b %ERRORLEVEL%
)

REM 
echo Running %OUTPUT%...
%OUTPUT%
pause