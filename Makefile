build = bin
src = src
obj = $(build)/obj

exec = fchangedir
fcd = fcd
fcdDIR = ~/.fcd

source = $(shell find $(src) -name *.c)
objects = $(patsubst $(src)/%.c, $(obj)/%.o, $(source))

cflags =
lflags = -lncurses 

install: $(build)/$(exec)
	mkdir -p $(fcdDIR) 
	cp $(build)/$(exec) $(fcdDIR) 
	chmod +x $(fcdDIR)/$(exec)
	cp $(fcd) $(fcdDIR)/

uninstall:
	rm -rf $(fcdDIR)

$(build)/$(exec): $(objects)
	gcc -o $@ $^ $(lflags)

$(obj)/%.o: $(src)/%.c mkdirs
	gcc -c $(cflags) -o $@ $<

mkdirs:
	-mkdir -p $(build)
	-mkdir -p $(obj)

clean:
	rm -rf $(build)

