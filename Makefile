all: keyGenerator.exe e3rsa.exe
	del tool.o

e3rsa.exe: e3rsa.c tool.o
	gcc e3rsa.c rsa.c tool.o -o e3rsa.exe

keyGenerator.exe: keyGenerator.c tool.o
	gcc keyGenerator.c tool.o -o keyGenerator.exe

tool.o: tool.c
	gcc -c tool.c -o tool.o

clean:
	del e3rsa.exe
	del keyGenerator.exe
	del p.txt
	del q.txt
	del n.txt
	del e.txt
	del d.txt