@echo off

set OUTPUT=NodeTest.exe
set CLASS_FILE=Node.cpp
set TEST_FILE=NodeTest.cpp

echo Compiling %CLASS_FILE% and %TEST_FILE%...
cl /EHsc /Fe:%OUTPUT% %CLASS_FILE% %TEST_FILE%

if errorlevel 1 (
    echo Compilation failed. Please check the code for errors.
    exit /b 1
)

echo Running %OUTPUT%...
%OUTPUT%
