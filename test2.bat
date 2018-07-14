@echo off

rem Two GPU threads.
rem !!! Edit config.txt first and set it to run 2 GPU threads !!!
rem !!! Set all parameters to some sane values and then run this script !!!

setlocal enabledelayedexpansion

echo intensity1,worksize1,intensity2,worksize2,shuffle,int_math,unroll,hashrate > tests2.csv

rem i,j = intensity
rem v,w = worksize
rem s = shuffle
rem m = int_math
rem u = unroll

for %%i in (200) do (
for %%v in (8) do (
for %%j in (200) do (
for %%w in (8) do (
for %%s in (0,1) do (
for %%m in (0,1) do (
for %%u in (1,2) do (
	xmr-stak-amd.exe %%i %%v %%j %%w %%s %%m %%u
	echo %%i,%%v,%%j,%%w,%%s,%%m,%%u,!errorlevel! >> tests2.csv
)))))))
