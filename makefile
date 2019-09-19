cc=gcc
target=demo
obj=main.o fun.o console.o start_mplayer.o

$(target):$(obj)
	$(cc) $^ -o $@ 

%.o:%.c
	$(cc) -c $< -o $@ 
	
clean:
	rm $(target) $(obj)