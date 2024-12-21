@echo off

for /l %%x in (6, 1, 25) do (
    set folderName=day%%x
    if not exist day%%x\ md "day%%x"

    if not exist day%%x\input.txt echo.>day%%x\input.txt
    if not exist day%%x\part1.cpp copy template.cpp day%%x\part1.cpp
    if not exist day%%x\part2.cpp copy template.cpp day%%x\part2.cpp
)