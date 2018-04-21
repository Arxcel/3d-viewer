CC = clang++

NAME = 3d_viewer

FLAGS = -std=c++17 -pthread #-Wall -Wextra -Werror

I_DIR = ./inc

S_DIR = ./src

O_DIR = obj

SDL2_F		= -framework SDL2 -F ./frameworks/

SDL2_P		= -rpath @loader_path/frameworks/

EXTENSIONS = $(addprefix $(I_DIR)/,$(EXT))

EXT =   Display.hpp \
        Vertex.hpp \
        Mesh.hpp \
        Shader.hpp \
        Transform.hpp \
        Camera.hpp \
        FileLoader.hpp

LIBGLEW = libGlew

HEADERS = -I$(I_DIR) \
          -I./glm \
          -I ./libGlew/inc \
          -I./frameworks/SDL2.framework/Headers \

SOURCES =   main.cpp \
            Display.cpp \
            Mesh.cpp \
            Shader.cpp \
            FileLoader.cpp

SRCS = $(addprefix $(S_DIR)/,$(SOURCES))

OBJS = $(addprefix $(O_DIR)/,$(SOURCES:.cpp=.o))

all: obj $(NAME)

$(NAME): $(OBJS) $(EXTENSIONS)
				make libs
				$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(HEADERS) -L $(LIBGLEW) -lglew $(SDL2_P) $(SDL2_F) -framework OpenGl

libs:
	make -C $(LIBGLEW)

obj:
	mkdir -p obj

$(O_DIR)/%.o: $(S_DIR)/%.cpp $(DEPS) $(EXTENSIONS)
		$(CC) -c -o $@ $< $(FLAGS) $(HEADERS)

clean:
		rm -f $(OBJS)
		make clean -C $(LIBGLEW)
		rm -rf $(O_DIR)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIBGLEW)

re: fclean all

.PHONY: all, obj, clean, fclean, re
.NOTPARALLEL:  all, obj, clean, fclean, re
#.SILENT:
