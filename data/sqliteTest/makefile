CC = g++ -std=c++17 -Wall
#SRC = src/*.cpp src/*.h
SRC = src/*.cpp
EXE = "sqltest"
DB = "test.db"
#SCANDIR = "/home/g7/source/psv2"

build:
	@echo "building..."
	@$(CC) $(SRC) -l sqlite3 -o $(EXE)
	@echo "build complete!"
clean:
	@rm $(EXE)
	@rm $(DB)
	@echo "all clean"
run:
	@$(CC) $(SRC) -l sqlite3 -o $(EXE)
	#@./$(EXE) $(SCANDIR)
	@./$(EXE)
	@rm $(EXE)
	#@rm $(DB)
