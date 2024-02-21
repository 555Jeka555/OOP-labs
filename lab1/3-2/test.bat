@echo off

set OUTPUT_FILE=test-data\output.txt

echo Test 1
rem “ест невалидное количество аргументов
invert.exe > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test-output-args.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 2
rem “ест невалидной размерности матрицы
invert.exe test-data\test-input1.txt > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test-output1.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 3
rem “ест невалидного заполнение матрицы
invert.exe test-data\test-input2.txt > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test-output2.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 4
rem “ест матрицы c целыми числами
invert.exe test-data\test-input3.txt > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test-output3.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 5
rem “ест матрицы c нулевым определителем
invert.exe test-data\test-input4.txt > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test-output4.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 6
rem “ест матрицы c вещественными числами
invert.exe test-data\test-input5.txt > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test-output5.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 7
rem “ест матрицы c очень малыми вещественными числами
invert.exe test-data\test-input6.txt > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test-output6.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Success!
exit /B 1

:err
echo Program testing failed
exit 1