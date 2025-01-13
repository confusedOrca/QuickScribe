@echo off

cd /d "%~dp0"

set CLASS_FILE=Node.cpp
set OBJECT_FILE=Node.obj
set LIBRARY_FILE=Node.lib

echo Compiling %CLASS_FILE% into object file...
cl /c /EHsc %CLASS_FILE%

if errorlevel 1 (
    echo Compilation of %CLASS_FILE% failed. Please check the code for errors.
    exit /b 1
)

echo Creating static library %LIBRARY_FILE%...
lib /out:%LIBRARY_FILE% %OBJECT_FILE%

if errorlevel 1 (
    echo Creation of %LIBRARY_FILE% failed. Please check the code for errors.
    exit /b 1
)

echo Cleaning up intermediate files...
del %OBJECT_FILE%

echo Static library %LIBRARY_FILE% created successfully.
