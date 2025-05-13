# ======================
# Configuration
# ======================
CC      = gcc
INCLUDE = -Iinclude
CFLAGS  = $(INCLUDE) 
LDFLAGS =

SRC     = $(wildcard src/*.c)
OBJ     = $(patsubst src/%.c, build/%.o, $(SRC))
EXEC    = carcassonne

.PHONY: all debug run-debug clean fclean re generate_code

# ======================
# Compilation
# ======================
all: $(EXEC)

debug: all

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

# ======================
# GDB
# ======================
run-debug: debug
	@echo "=== Lancement de GDB ==="
	gdb ./$(EXEC)

# ======================
# Nettoyage
# ======================
clean:
	rm -f build/*.o $(EXEC)
	@if [ -d build ]; then rmdir --ignore-fail-on-non-empty build; fi

fclean: clean

re: fclean all

