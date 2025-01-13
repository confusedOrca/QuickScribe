@echo off

cd /d "%~dp0"

set TEST_FILE=RecommendationsTest.cpp
set LIBRARY_FILE=Recommendations.lib
set OUTPUT=RecommendationsTest.exe

echo Compiling and linking %TEST_FILE% with %LIBRARY_FILE% to create %OUTPUT%...
cl /EHsc /Fe:%OUTPUT% %TEST_FILE% %LIBRARY_FILE%

if errorlevel 1 (
    echo Compilation and linking of %TEST_FILE% failed. Please check the code for errors.
    exit /b 1
)

echo Running %OUTPUT%...
%OUTPUT%