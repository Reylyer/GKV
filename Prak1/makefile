file = asd1
ext = cpp
filename = asd.cpp

create_dir:
	@if not exist bin mkdir bin
	@if not exist obj mkdir obj

# 
a:
	cl /Wall /Fo..\obj\  /Fe..\bin\ src\$(file).$(ext)

main:
	cl /Fo..\obj\  /Fe..\bin\ src\main.cpp

asd2:
	cl /Fo..\obj\  /Fe..\bin\ src\asd2.cpp
	..\bin\asd2.exe

wasd1:
	cl /Fo..\obj\  /Fe..\bin\ src\wasd1.cpp

asd3:
	cl /Fo..\obj\  /Fe..\bin\ src\asd3.cpp
	.,\bin\asd3.exe

init: create_dir build