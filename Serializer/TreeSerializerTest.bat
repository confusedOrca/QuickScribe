@echo off

cd /d "%~dp0"

set TEST_FILE=TreeSerializerTest.cpp
set OUTPUT=TreeSerializerTest.exe

set LIBRARIES[0]=TreeSerializer.lib
set LIBRARIES[1]=../Recommender/Node/Node.lib

setlocal enabledelayedexpansion

echo Compiling %TEST_FILE%...
cl /std:c++17 /EHsc /c %TEST_FILE%

set LINK_CMD=link %TEST_FILE:.cpp=.obj%

for /L %%i in (0, 1, 1) do (
    set LIBRARY_FILE=!LIBRARIES[%%i]!
    set LINK_CMD=!LINK_CMD! !LIBRARY_FILE!
)

set LINK_CMD=!LINK_CMD! /OUT:%OUTPUT%

echo Linking with libraries...
!LINK_CMD!

if errorlevel 1 (
    echo Compilation and linking failed. Please check the code for errors.
    exit /b 1
)

echo Running %OUTPUT%...
%OUTPUT%

endlocal
