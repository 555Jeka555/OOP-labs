@echo off

set INPUT_FILE=test-data\input.txt
set INPUT_BIG_FILE=test-data\input-big.txt
set OUTPUT_FILE=test-data\output.txt

echo Test 1
rem ѕроверка замены 1231234 в 12312345 на строку, чтобы проверить правильность обработки по част€м (теперь в проверке нет необходимости)
replace.exe %INPUT_FILE% %OUTPUT_FILE% "1231234" "good" || goto err
fc test-data\test1.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 2
rem ѕроверка замены строки на р€д таких же дл€ проверки циклически
replace.exe %INPUT_FILE% %OUTPUT_FILE% "good" "goodgoodgood" || goto err
fc test-data\test2.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 3
rem ѕроверка замены одной строки на вторую строку
replace.exe %INPUT_FILE% %OUTPUT_FILE% "may?" "not february(" || goto err
fc test-data\test3.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 4
rem ѕроверка на замену, при не существующей поисковой строки
replace.exe %INPUT_FILE% %OUTPUT_FILE% "bad" "good" || goto err
fc test-data\input.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 5
rem ѕроверка на замену, при пустой поисковой строки
replace.exe %INPUT_FILE% %OUTPUT_FILE% "" "silly" || goto err
fc test-data\input.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 6
rem ѕроверка на цикличность 1234 в 123123
replace.exe %INPUT_FILE% %OUTPUT_FILE% "123" "1234" || goto err
fc test-data\test4.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Test 7
rem ѕроверка на замену в большом файле
replace.exe %INPUT_BIG_FILE% %OUTPUT_FILE% "C++" "JAVA" || goto err
fc test-data\test5.txt %OUTPUT_FILE%
if %errorlevel% == 1 ( goto err )

echo Success!
exit /B 0

:err
echo Program testing failed
exit 1