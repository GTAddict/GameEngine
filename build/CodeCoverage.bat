@echo off
setlocal ENABLEDELAYEDEXPANSION

set PROJECTS_DIR=..\source
set PROJECT_UNDER_TEST=Library.Desktop
set UNIT_TEST_PROJECT=UnitTest.Library.Desktop
set DEFAULT_BINARY_PATH=Win32\Release
set COVERAGE_REPORTS_PATH=CoverageReports
set TEST_RESULTS_PATH=TestResults

set GENERATE_COVERAGE_COMMAND=vstest.console.exe /InIsolation /Enablecodecoverage
set GENERATE_XML_COMMAND=CodeCoverage.exe analyze /output:
set GENERATE_REPORT_COMMAND=ReportGenerator.exe
set START_WEB_SERVER_COMMAND=python -m SimpleHTTPServer
set COVERAGE_SERVER_PORT=9000

if exist !TEST_RESULTS_PATH! rd /s /q !TEST_RESULTS_PATH!
if exist !COVERAGE_REPORTS_PATH! rd /s /q !COVERAGE_REPORTS_PATH!

!GENERATE_COVERAGE_COMMAND! !DEFAULT_BINARY_PATH!\!UNIT_TEST_PROJECT!.dll
set REPORTS=
for /f "tokens=* USEBACKQ" %%i in (`dir *.coverage /s /b`) do (
	!GENERATE_XML_COMMAND!"%%i.xml" "%%i"
	set REPORTS=!REPORTS!;%%i.xml
)
!GENERATE_REPORT_COMMAND! "-reports:!REPORTS!" "-targetdir:CoverageReports" "-sourcedirs:!PROJECTS_DIR!\!PROJECT_UNDER_TEST!"

cd !COVERAGE_REPORTS_PATH!
!START_WEB_SERVER_COMMAND! !COVERAGE_SERVER_PORT!
cd -

endlocal
@echo on