for /r ..\Untitled-Motor\MotorCasaPaco\dependencies\ogre-1.12.4\Build\bin\debug\ %%f in (*.dll) do @copy "%%f" ..\bin\
for /r ..\Untitled-Motor\MotorCasaPaco\dependencies\ogre-1.12.4\Build\bin\release\ %%f in (*.dll) do @copy "%%f" ..\bin\
for /r ..\Untitled-Motor\MotorCasaPaco\dependencies\SDL2-2.0.10\lib\x64 %%f in (*.dll) do @copy "%%f" ..\bin\
for /r ..\Untitled-Motor\MotorCasaPaco\dependencies\fmod-2.00.07\ %%f in (*.dll) do @copy "%%f" ..\bin\
for /r ..\Untitled-Motor\MotorCasaPaco\dependencies\bullet3-2.89\build\lib %%f in (*.dll) do @copy "%%f" ..\bin\
for /r ..\Untitled-Motor\MotorCasaPaco\dependencies\cegui-0.8.7\build\bin\ %%f in (*.dll) do @copy "%%f" ..\bin\
for /r ..\Untitled-Motor\MotorCasaPaco\dependencies\cegui-0.8.7\dependencies\bin %%f in (*.dll) do @copy "%%f" ..\bin\