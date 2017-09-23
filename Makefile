all: release debug

debug: *.cpp *.h
	g++ *.c *.cpp -o bin/debug/pool.exe -Wfatal-errors -DDEBUG -g -Iinclude -Llib -lglfw3 -lgdi32 -lopengl32 -lwinmm
release: *.cpp *.h
	g++ *.c *.cpp -o bin/release/pool.exe -Wfatal-errors -O3 -Iinclude -Llib -lglfw3 -lgdi32 -lopengl32 -lwinmm -mwindows

.PHONY: clean
clean:
	rm -f bin/debug/*.exe
	rm -f bin/release/*.exe
