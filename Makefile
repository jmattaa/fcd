build = bin
src = src
obj = $(build)/obj

exec = $(build)/fcd

source = $(shell find $(src) -name *.c)
objects = $(patsubst $(src)/%.c, $(obj)/%.o, $(source))

cflags = 
lflags =

$(exec): $(objects)
	gcc -o $(lflags) $@ $^

$(obj)/%.o: $(src)/%.c mkdirs
	gcc -c $(cflags) -o $@ $<

mkdirs:
	-mkdir -p $(build)
	-mkdir -p $(obj)

clean:
	rm -rf $(build)

