@echo off

set OUTPUT_FILE=test-data\output.txt

echo Test 1
rem Тест невалидное количество аргументов
invert.exe > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test-output-args.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 2
rem Тест невалидной размерности матрицы
invert.exe test-data\test-input1.txt > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test-output1.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 3
rem Тест невалидного заполнение матрицы
invert.exe test-data\test-input2.txt > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test-output2.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 4
rem Тест матрицы c целыми числами
invert.exe test-data\test-input3.txt > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test-output3.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 5
rem Тест матрицы c нулевым определителем
invert.exe test-data\test-input4.txt > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test-output4.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Success!
exit /B 1

:err
echo Program testing failed
exit 1