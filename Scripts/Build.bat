@echo off
pushd %~dp0\..\
call Vendors\Premake5\Binaries\premake5.exe vs2022
popd
PAUSE