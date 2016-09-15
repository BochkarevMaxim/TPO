echo off

echo =====================================================
echo -----Run without command line parametres
echo =====================================================
triangle.exe > result.txt
fc /b result.txt tests/empty_command_line_params.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo =====================================================
echo -----Run with incorrect amount of command line parametres
echo =====================================================
echo parametres less than 3
triangle.exe 1 2 > result.txt
fc /b result.txt tests/incorrect_command_line_params.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo parametres more than 3
triangle.exe 1 2 3 4 > result.txt
fc /b result.txt tests/incorrect_command_line_params.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo =====================================================
echo -----Run with incorrect command line parametres (symbols or signs)
echo =====================================================
echo symbols in input
triangle.exe 3 4 f > result.txt
fc /b result.txt tests/not_numeric_symbols.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo signs in input
triangle.exe 3 # f > result.txt
fc /b result.txt tests/not_numeric_symbols.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo =====================================================
echo -----Run with negative values
echo =====================================================
triangle.exe -3 4 5 > result.txt
fc /b result.txt tests/negative_values_input.txt
IF ERRORLEVEL 1 GOTO testsFailed

triangle.exe 3 -4 -5 > result.txt
fc /b result.txt tests/negative_values_input.txt
IF ERRORLEVEL 1 GOTO testsFailed

triangle.exe -3 -4 -5 > result.txt
fc /b result.txt tests/negative_values_input.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo =====================================================
echo -----Run with correct parametres (common triangle)
echo =====================================================
triangle.exe 3.0 4.0 5.0 > result.txt
fc /b result.txt tests/common.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo =====================================================
echo -----Run with correct parametres (equilateral triangle)
echo =====================================================
triangle.exe 7.0 7.0 7.0 > result.txt
fc /b result.txt tests/equilateral.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo =====================================================
echo -----Run with correct parametres (isosceles triangle)
echo =====================================================
triangle.exe 7.0 7.0 12.0 > result.txt
fc /b result.txt tests/isosceles.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo =====================================================
echo -----Run with correct parametres (but not triangle)
echo =====================================================
echo zero side
triangle.exe 7.0 0.0 12.0 > result.txt
fc /b result.txt tests/non_triangle.txt
IF ERRORLEVEL 1 GOTO testsFailed

echo 2 sides sum less than 3rd side
triangle.exe 1.0 2.0 12.0 > result.txt
fc /b result.txt tests/non_triangle.txt
IF ERRORLEVEL 1 GOTO testsFailed
echo =====================================================

echo Testing Succecfully Completed
del result.txt
pause
exit /b

:testsFailed
echo Testing Failed
pause
exit /b