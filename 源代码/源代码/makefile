# 编译器设置
CC = g++
CFLAGS = -Wall -O2 -std=c++11

# 目标文件 - 程序入口是SAT.cpp
TARGET = SAT

# 源文件和对象文件
SRCS = cnfparser.cpp display.cpp SAT.cpp solver.cpp X-Sudoku.cpp
OBJS = $(SRCS:.cpp=.o)

# 默认目标
all: $(TARGET)

# 链接规则
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译规则
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# 显式依赖关系
cnfparser.o: cnfparser.cpp SAT.hpp
display.o: display.cpp SAT.hpp
SAT.o: SAT.cpp SAT.hpp
solver.o: solver.cpp SAT.hpp
X-Sudoku.o: X-Sudoku.cpp SAT.hpp

# 清理规则
clean:
	rm -f $(OBJS) $(TARGET)

# Windows清理规则
clean-win:
	del /Q $(OBJS) $(TARGET).exe

# 伪目标声明
.PHONY: all clean clean-win