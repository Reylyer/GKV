file = lengan_full
ext = cpp

lo = truk_wawowalam

love:
	cl /Wall /Fo..\obj\  /Fe..\bin\ src\$(lo).$(ext)
	..\bin\$(lo).exe


create_dir:
	@if not exist bin mkdir bin
	@if not exist obj mkdir obj

# 
a:
	cl /Wall /Fo..\obj\  /Fe..\bin\ src\$(file).$(ext)
	..\bin\$(file).exe

init: create_dir a