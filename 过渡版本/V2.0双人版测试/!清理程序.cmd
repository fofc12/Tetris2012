@echo off
echo 清理程序v1.0 适用于单文件的程序
echo 正在删除VC6/CF5产生的多余文件……
del /a/f/q *.o
del /a/f/q *.c~
del /a/f/q *.dsp
del /a/f/q *.dsw
del /a/f/q *.ncb
del /a/f/q *.opt
del /a/f/q *.plg
move Debug\*.exe .
rd /s/q Debug
echo 删除完成！
echo 请问是否要删除当前目录下exe文件
set /p answer=
if "%answer%"=="y" del /a/f/q *.exe