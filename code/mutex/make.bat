@SETLOCAL
@DEL .\*.exe
@CALL "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" "mutex.sln" /p:configuration="Debug"
@COPY x64\Debug\*.exe .\
