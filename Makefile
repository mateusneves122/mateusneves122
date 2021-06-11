
srcfiles 	:= $(wildcard *.cpp) $(wildcard src/*.cpp)


objects		:= $(patsubst %.cpp, %.o, $(srcfiles))


CC=g++
 

CC_FLAGS= -I./include  


RM = rm -rf

target     := ./main.exe
 

all: $(target)


$(notdir $(target)): $(objects)
		@echo "Linking "$@"..."
		@$(CC) $(objects) -o $@
 
%.o: %.cpp
	@echo "Compiling C "$<"..."
	@$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(objects) $(target)