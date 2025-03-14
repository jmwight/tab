obj = main.o tab.o

tab: $(obj)
	gcc -o tab $(obj)

main.o: tab.h
tab.o: tab.h

.PHONY: clean
clean:
	rm -rf $(obj)
