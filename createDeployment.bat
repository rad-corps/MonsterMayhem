for /f "delims=" %%a in ('wmic OS Get localdatetime  ^| find "."') do set dt=%%a
set datestamp=%dt:~0,8%
set timestamp=%dt:~8,6%
set YYYY=%dt:~0,4%
set MM=%dt:~4,2%
set DD=%dt:~6,2%
set HH=%dt:~8,2%
set Min=%dt:~10,2%
set Sec=%dt:~12,2%

set stamp=%YYYY%-%MM%-%DD%--%HH%-%Min%
set dirName="MonsterMayhemBuild-%stamp%"

Xcopy ".\bin\MonsterMayhem.exe" ".\resources\" /y
XCopy ".\resources" ".\%dirName%" /y /i /s /e

7z a "%dirName%.zip" "%dirName%\"
pause