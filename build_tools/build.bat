@ECHO off
SetLocal EnableDelayedExpansion

REM Create list of all source files

SET sourceFiles=
FOR /R %%f in (*.cpp) do (
    SET sourceFiles=!sourceFiles! %%f
)

@REM ECHO "Files: " %sourceFiles%

SET includeArgs=-Isrc -Idependencies/include
SET linkerArgs=-Ldependencies/lib -lopengl32 -lglfw3 -lglew32 -lassimp

ECHO "Start building"
g++ -g %sourceFiles% %linkerArgs% %includeArgs% -o build/engine