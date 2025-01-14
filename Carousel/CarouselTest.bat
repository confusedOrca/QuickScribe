@echo off

cd /d "%~dp0"

set TEST_FILE=CarouselTest.cpp
set OUTPUT=CarouselTest.exe

echo Compiling and linking %TEST_FILE% to create %OUTPUT%...
cl /EHsc /Fe:%OUTPUT% %TEST_FILE%

if errorlevel 1 (
    echo Compilation and linking of %TEST_FILE% failed. Please check the code for errors.
    exit /b 1
)

echo Running %OUTPUT%...
%OUTPUT%