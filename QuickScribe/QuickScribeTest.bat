@echo off

cd /d "%~dp0"

set TEST_FILE=QuickScribeTest.cpp
set OUTPUT=QuickScribeTest.exe

set LIBRARIES[0]=QuickScribe.lib
set LIBRARIES[1]=./StringCarousel/StringCarousel.lib
set LIBRARIES[2]=../Serializer/TreeSerializer.lib
set LIBRARIES[3]=../Recommender/Recommender.lib
set LIBRARIES[4]=../Recommender/Node/Node.lib
set LIBRARIES[5]=../Recommender/Recommendations/Recommendations.lib

setlocal enabledelayedexpansion

echo Compiling %TEST_FILE%...
cl /std:c++17 /EHsc /c %TEST_FILE%

set LINK_CMD=link %TEST_FILE:.cpp=.obj%

for /L %%i in (0, 1, 5) do (
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
