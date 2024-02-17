@echo off

set OUTPUT_FILE=test-data\output.txt

echo Test 1
rem ���� �������������� �����
radix.exe 10 16 12345 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test1.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 2
rem ���� �������������� �����
radix.exe 10 16 -12345 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test2.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 3
rem ���� ����
radix.exe 10 16 0 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test3.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 4
rem ���� ������������� integer
radix.exe 10 16 2147483647 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test4.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 5
rem ���� ������������ integer
radix.exe 10 16 -2147483647 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test5.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 6
rem ���� �������� �����
radix.exe 10 16 12.34 > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test6.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 7
rem ���� ���������� ��������� ������� ���������
radix.exe 37 16 12345 > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test7.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 8
rem ���� ���������� ��������� ������� ���������
radix.exe 10 37 12345 > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test8.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 9
rem ���� ����������� ����� � ��������� ������� ���������
radix.exe 16 10 1234G > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test9.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 10
rem ���� ����������� ���������� ����������
radix.exe 16 10 > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test10.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 11
rem ���� ������������ ��������� ������� ���������
radix.exe 36 10 ZEZRZ > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test11.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 12
rem ���� ������������ ��������� ������� ���������
radix.exe 10 36 1234567 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test12.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 13
rem ���� ������������ integer
radix.exe 16 10 -80000000 > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test13.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 14
rem ���� ������������� integer
radix.exe 16 10 7FFFFFFF > %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )
fc test-data\test14.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 15
rem ���� ������������� integer
radix.exe 16 10 2147483648 > %OUTPUT_FILE%
if %errorlevel% == 0 ( goto err )
fc test-data\test15.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )


echo Success!
exit /B 1

:err
echo Program testing failed
exit 1