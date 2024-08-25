# Nome do executável
TARGET = main

# Diretórios de origem e inclusão
INCLUDE_DIR = src/Include
LIB_DIR = src/lib

# Arquivos fonte
SRCS = \
    main.cpp \
    components/base.cpp \
    components/bullet.cpp \
    components/player.cpp \
    entities/ammo_box.cpp \
    entities/slow_enemy.cpp \
    entities/shooter_enemy.cpp \
    entities/agressive_enemy.cpp \
    entities/explosive_enemy.cpp \
    components/game.cpp \
    components/menu.cpp

# Arquivos objeto
OBJS = $(SRCS:.cpp=.o)

# Compilador e flags
CXX = g++
CXXFLAGS = -g -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Regra padrão
all: $(TARGET)
	./$(TARGET)
	$(MAKE) clean_objects

# Regra para construir o executável
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Regra para criar arquivos objeto a partir de arquivos fonte
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos objeto
clean_objects:
	rm -f $(OBJS)

# Regra para limpar todos os arquivos gerados, incluindo o executável
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean clean_objects
