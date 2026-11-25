@echo off
REM Smart Canteen Billing System - Compile and Run Script
REM This script compiles the C program and runs it

echo ==========================================
echo Smart Canteen Billing System - Build Script
echo ==========================================
echo.

REM Check if GCC is available
where gcc >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: GCC compiler not found in PATH
    echo Please install MinGW or add GCC to PATH
    echo.
    echo You can download MinGW from: https://www.mingw-w64.org/
    pause
    exit /b 1
)

echo Compiling canteen_billing.c...
gcc canteen_billing.c -o canteen_billing.exe

if %errorlevel% neq 0 (
    echo.
    echo ERROR: Compilation failed!
    echo Please check the code for errors.
    pause
    exit /b 1
)

echo.
echo Compilation successful!
echo.
echo Running Smart Canteen Billing System...
echo ==========================================
echo.

canteen_billing.exe

echo.
echo ==========================================
echo Program finished.
pause