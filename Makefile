obj = main.o tab.o
opt = -g

tab: $(obj)
	gcc $(opt) -o tab $(obj)

main.o: tab.h main.c
	gcc $(opt) -c main.c
tab.o: tab.h tab.c
	gcc $(opt) -c tab.c

.PHONY: clean
clean:
	rm -rf $(obj)
