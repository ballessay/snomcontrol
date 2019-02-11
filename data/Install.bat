set TARGET_DIR=%ProgramFiles%\snomcontrol

rmdir /Q /S "%TARGET_DIR%"

xcopy /S /I /Y /Q "%~dp0\..\snomcontrol" "%TARGET_DIR%" /EXCLUDE:%~dp0\excludes.txt

reg import "%~dp0\snomcontrol.reg"
pause