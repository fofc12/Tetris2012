@echo off
echo �������v1.0 �����ڵ��ļ��ĳ���
echo ����ɾ��VC6/CF5�����Ķ����ļ�����
del /a/f/q *.o
del /a/f/q *.c~
del /a/f/q *.dsp
del /a/f/q *.dsw
del /a/f/q *.ncb
del /a/f/q *.opt
del /a/f/q *.plg
move Debug\*.exe .
rd /s/q Debug
echo ɾ����ɣ�
echo �����Ƿ�Ҫɾ����ǰĿ¼��exe�ļ�
set /p answer=
if "%answer%"=="y" del /a/f/q *.exe