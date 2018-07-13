@echo off

setlocal enabledelayedexpansion

echo intensity,worksize,shuffle,int_math,unroll,hashrate > tests.csv

rem i = intensity
rem w = worksize
rem s = shuffle
rem m = int_math
rem u = unroll

for %%i in (448) do (
for %%w in (8) do (
for %%s in (0,1) do (
for %%m in (0,1) do (
for %%u in (1,2) do (
	xmr-stak-amd.exe %%i %%w %%s %%m %%u
	echo %%i,%%w,%%s,%%m,%%u,!errorlevel! >> tests.csv
)))))
