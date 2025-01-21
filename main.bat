@echo off

cd /d "%~dp0"

set TEST_FILE=main.cpp
set OUTPUT=main.exe

set LIBRARIES[0]=./QuickScribe/QuickScribe.lib
set LIBRARIES[1]=./QuickScribe/StringCarousel/StringCarousel.lib
set LIBRARIES[2]=./Serializer/TreeSerializer.lib
set LIBRARIES[3]=./Recommender/Recommender.lib
set LIBRARIES[4]=./Recommender/Node/Node.lib
set LIBRARIES[5]=./Recommender/Recommendations/Recommendations.lib
set LIBRARIES[6]=user32.lib

setlocal enabledelayedexpansion

echo Compiling %TEST_FILE%...
cl /std:c++17 /EHsc /c %TEST_FILE%

set LINK_CMD=link %TEST_FILE:.cpp=.obj%

for /L %%i in (0, 1, 6) do (
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
