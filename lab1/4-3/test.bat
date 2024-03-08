@echo off

set CRYPT_FILE=test-data\crypted.txt
set DECRYPT_FILE=test-data\decrypted.txt
set DECRYPT_FILE_EXE=test-data\decrypted.exe

echo Test 1
rem ����������� � ������������� �����
crypt.exe crypt "test-data\test-input.txt" %CRYPT_FILE% 100
if %errorlevel% == 1 ( goto err )
crypt.exe decrypt %CRYPT_FILE% %DECRYPT_FILE% 100
if %errorlevel% == 1 ( goto err )
fc %DECRYPT_FILE% "test-data\test-input.txt"
if %errorlevel% == 1 ( goto err )

echo Test 2
rem ���������� ���� �������������
crypt.exe crypt "test-data\test-input.txt" %CRYPT_FILE% 100
if %errorlevel% == 1 ( goto err )
crypt.exe decrypt %CRYPT_FILE% %DECRYPT_FILE% 10
if %errorlevel% == 1 ( goto err )
fc %DECRYPT_FILE% "test-data\test-input.txt" > nul
if %errorlevel% == 0 ( goto err )

echo Test 3
rem ����������� � ������������� ����
crypt.exe crypt "test-data\test-input-empty.txt" %CRYPT_FILE% 100
if %errorlevel% == 1 ( goto err )
crypt.exe decrypt %CRYPT_FILE% %DECRYPT_FILE% 100
if %errorlevel% == 1 ( goto err )
fc %DECRYPT_FILE% "test-data\test-input-empty.txt"
if %errorlevel% == 1 goto err

echo Test 4
rem �������� ����������� � ������������� �� binary ����
crypt.exe crypt crypt.exe %CRYPT_FILE% 100
if %errorlevel% == 1 ( goto err )
crypt.exe decrypt %CRYPT_FILE% %DECRYPT_FILE% 100
if %errorlevel% == 1 ( goto err )
fc %DECRYPT_FILE% crypt.exe
if %errorlevel% == 1 goto err

echo Test 5
rem ���������� ���� �� �������� ��������
crypt.exe crypt "test-data\test-input.txt" %CRYPT_FILE% 256
if %errorlevel% == 0 ( goto err )

echo Test 6
rem ���������� ���� �� ������� ��������
crypt.exe crypt "test-data\test-input.txt" %CRYPT_FILE% -1
if %errorlevel% == 0 ( goto err )

echo Test 7
rem ���������� ����
crypt.exe crypt "test-data\test-input.txt" %CRYPT_FILE% "gfda"
if %errorlevel% == 0 ( goto err )

echo Test 8
rem ���������� �����
crypt.exe read "test-data\test-input.txt" %CRYPT_FILE% 100
if %errorlevel% == 0 ( goto err )

echo Test 9
rem �������� �� �������� �� ������������� �����
crypt.exe crypt "test.txt" %CRYPT_FILE% 100
if %errorlevel% == 0 ( goto err )

echo Test 10
rem �������� �� �������� ������������� �����
crypt.exe crypt "test-data\test-input.txt" "./crypt.exe" 100
if %errorlevel% == 0 ( goto err )

echo Success!
exit /B 1

:err
echo Program testing failed
exit 1