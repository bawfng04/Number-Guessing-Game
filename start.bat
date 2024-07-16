@echo off
cd main
g++ NumberGuessing.cpp -o ../bin/NumberGuessing
if %ERRORLEVEL% == 0 (
    cd ../bin
    NumberGuessing
    cd ..
) else (
    echo Compilation failed.
)