@echo off

set OUTPUT_FILE=test-data\output.txt

echo Test 1
REM Test positive integer
radix.exe 10 16 12345 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)
fc test-data\test1.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 2
REM Test negative integer
radix.exe 10 16 -12345 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)
fc test-data\test2.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 3
REM Test zero
radix.exe 10 16 0 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)
fc test-data\test3.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 4
REM Test maximum integer
radix.exe 10 16 2147483647 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)
fc test-data\test4.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 5
REM Test minimum input
radix.exe 10 16 -2147483647 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)
fc test-data\test5.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 6
REM Test non-integer value
radix.exe 10 16 12.34 > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err)
fc test-data\test6.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 7
REM Test non-existent source notation
radix.exe 37 16 12345 > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err)
fc test-data\test7.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 8
REM Test non-existent destination notation
radix.exe 10 37 12345 > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err)
fc test-data\test8.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 9
REM Test invalid value in source notation
radix.exe 16 10 1234G > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err)
fc test-data\test9.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 10
REM Test invalid number of arguments
radix.exe 16 10 > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err)
fc test-data\test10.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 11
REM Test max source notation
radix.exe 36 10 ZEBRA > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)
fc test-data\test11.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 12
REM Test max destination notation
radix.exe 10 36 1234567 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)
fc test-data\test12.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 13
REM Test integer minimum
radix.exe 16 10 -80000000 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)
fc test-data\test13.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Test 14
REM Test integer minimum
radix.exe 16 10 7FFFFFFF > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)
fc test-data\test13.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err)

echo Success!
exit /B 1

:err
echo Program testing failed
exit 1