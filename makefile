# 第一层：显示规则
# 目标文件：依赖文件
# 【TAB】指令
# 第一个目标文件是我们要的最终目标
# example:
# life:main.o life_game.o draw.o
# 	g++  main.o life_game.o draw.o -o life -lGL -lGLU -lglut
# life_game.o:life_game.cpp
# 	g++ -c life_game.cpp
# draw.o:draw.cpp
# 	g++ -c draw.cpp
# main.o:main.cpp
# 	g++ -c main.cpp
# clean:
# 	rm *.o life

# 第二层：变量 = （替换） += （追加） ：=（常量）
# 使用变量 $(变量名) 替换
# example:
# TAR = life
# OBJ = main.o life_game.o draw.o
# CC := g++
# LIB = -lGL -lGLU -lglut

# $(TAR):$(OBJ)
# 	$(CC)  $(OBJ) -o $(TAR) $(LIB)
# life_game.o:life_game.cpp
# 	$(CC) -c life_game.cpp
# draw.o:draw.cpp
# 	$(CC) -c draw.cpp
# main.o:main.cpp
# 	$(CC) -c main.cpp
# clean:
# 	rm $(OBJ) life


# 第三层：隐含规则 %.c %.o r任意的.c 或者.o   *.c *.o 所有的.c .o
# example:
# TAR = life
# OBJ = main.o life_game.o draw.o
# CC := g++
# LIB = -lGL -lGLU -lglut

# $(TAR):$(OBJ)
# 	$(CC)  $(OBJ) -o $(TAR) $(LIB)

# %.o:%.c
# 	$(CC) -c %.c -o %.o

# clean:
# 	rm $(OBJ) life

# 第四层：通配符 $^ 所有的依赖文件  $@ 所有的目标文件 $< 所有的依赖文件的第一个文件
# example:
TAR = life
OBJ = main.o life_game.o draw.o
CC := g++
LIB = -lGL -lGLU -lglut

$(TAR):$(OBJ)
	$(CC)  $^ -o $@ $(LIB)

%.o:%.c
	$(CC) -c $^ -o $@

clean:
	rm $(OBJ) life
