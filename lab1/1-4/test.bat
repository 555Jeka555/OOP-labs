@echo off

set INPUT_FILE=test-data\input.txt
set OUTPUT_FILE=test-data\output.txt

echo Test 1
replace.exe %INPUT_FILE% %OUTPUT_FILE% "1231234" "good" || goto err
fc test-data\test1.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 2
replace.exe %INPUT_FILE% %OUTPUT_FILE% "good" "goodgoodgood" || goto err
fc test-data\test2.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 3
replace.exe %INPUT_FILE% %OUTPUT_FILE% "may?" "not february(" || goto err
fc test-data\test3.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 4
replace.exe %INPUT_FILE% %OUTPUT_FILE% "bad" "good" || goto err
fc test-data\input.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 5
replace.exe %INPUT_FILE% %OUTPUT_FILE% "" "silly" || goto err
fc test-data\input.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 6
replace.exe %INPUT_FILE% %OUTPUT_FILE% "123" "1234" || goto err
fc test-data\test4.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Success!
exit /B 0

:err
echo Program testing failed
exit 1