@echo off
IF "%VCPKG%"=="" (
ECHO Environment variable VCPKG is NOT defined, for example SET VCPKG=C:\VCPKG
EXIT /B
)
IF "%1"=="" ( 
SET "arch=Win64"
) ELSE ( 
SET "arch=%1"
)
IF "%WX_VS_VER%"=="" ( 
SET "generator=Visual Studio 16 2019"
) ELSE (
SET "generator=Visual Studio 15 2017"
)

IF "%arch%"=="Win32" ( 
SET "target=Win32"
) ELSE ( 
SET "target=x64"
)
IF "%2"=="" ( SET "build=Release" ) ELSE ( SET "build=%2" )
IF "%3"=="" ( SET "linking=dynamic" ) ELSE ( SET "linking=%3" )
set "builddir=%build%%arch%%linking%" 
RMDIR .\%builddir% /S /Q
echo Building %build% %arch% using %linking% libraries..
cmake -G "%generator%" -A %target% -DCMAKE_BUILD_TYPE=%build% -H. -B%builddir% -DCMAKE_TOOLCHAIN_FILE=%VCPKG%\scripts\buildsystems\vcpkg.cmake -DLINKING_TYPE=%linking%
cmake --build .\%builddir% --config %build%
echo Start application:
echo cd %builddir% ^& %build%\boid_app.exe