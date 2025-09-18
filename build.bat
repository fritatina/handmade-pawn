@echo off

IF NOT EXIST .\bin mkdir .\bin

gcc .\src\main.c -std=c99 -g -o .\bin\hhpawn.exe -Og -Wall -Wextra -pedantic -Wmisleading-indentation -Wimplicit-fallthrough -Wvla