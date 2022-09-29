#Makefile中本身是没有 all 指令的，这里只不过是一种约定，认为目标 all 可以同时做很多事儿，也就能能同时生成多个目标
#我们知道，一个Makefile中只有一个最终目标，就是第一个目标，下面的代码中，显然就是 other，
#那么other的依赖元素有2个，分别为myapp和clean，而make具有自动推导，make在生成other的时候，自然要自动推导出myapp和clean，这样我们就能通过一个Makefile生成了2个目标，分别是myapp和clean，而这两个都是可执行程序，很巧妙的用法。
#all:  myapp clean
# $? 当前目标所依赖的文件列表中比当前目标文件还要新的文件
# $@ 当前目标的名字
# $< 当前依赖文件的名字
# $* 不包括后缀名的当前依赖文件的名字
# - 忽略make命令错误
# @ 执行某条命令钱不需要改命令显示在屏幕上
other: myapp
CC = g++
INCLUDE = .
#develop
CFLAGS = -g -Wall -ansi
#relase
#CFLAGS = -O -Wall -ansi
INSTDFIR = /usr/local/bin
clean:
	-rm -rf *.o
myapp: main.o 2.o 3.o
	${CC} -o myapp main.o 2.o 3.o
	@echo $@
# #main.o: main.c a.h 当目标main.o依赖 a.h时 当a.h发生变化时会重新编译main.o
# main.o: main.c a.h
# 	$(CC) -I$(INCLUDE) $(CFLAGS) -c main.c -o main.o
# #2.o: 2.c a.h b.h
# 2.o: 2.c
# 	$(CC) -I$(INCLUDE) $(CFLAGS) -c 2.c -o 2.o
# #3.o: 3.c b.h c.h
# 3.o: 3.c clean
# 	$(CC) -I$(INCLUDE) $(CFLAGS) -c 3.c -o 3.o
# #.<old_suffix>.<new_suffix>	增加新的后缀规则例如.c.o 告诉make 紧随其后的规则是将.c文件转换成.o文件	
# #将所有的.c文件转换成.o文件	
# .c.o: 
#	$(CC) -I$(INCLUDE) $(CFLAGS) -c $<
# %通配符规则
%.o: %.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $< -o $@
uninstall:
	rm -rf $(INSTDFIR)/myapp
install:
	@if [ -d ${INSTDFIR} ]; \
	then \
	cp myapp $(INSTDFIR); \
	chmod a+x $(INSTDFIR)/myapp; \
	chmod og-w $(INSTDFIR)/myapp; \
	echo "install myapp to $(INSTDFIR)";\
	else \
	echo "$(INSTDFIR) 不存在";\
	fi

