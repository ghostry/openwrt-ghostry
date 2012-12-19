INSTDIR   = $(prefix)/usr/bin
INSTMODE  = 0755
INSTOWNER = root
INSTGROUP = root


all: car-server car-test car-autorun

car-server: car-test car-autorun
	$(CC) $(CFLAGS)  -o car-server car-server.c

car-test:
	$(CC) $(CFLAGS)  -o car-test car-test.c

car-autorun:
	$(CC) $(CFLAGS)  -o car-autorun car-autorun.c

install: all
	$(INSTALL) -d $(INSTDIR)
	$(INSTALL) -m $(INSTMODE) -o $(INSTOWNER) -g $(INSTGROUP) car-server $(INSTDIR)
	$(INSTALL) -m $(INSTMODE) -o $(INSTOWNER) -g $(INSTGROUP) car-test $(INSTDIR)
	$(INSTALL) -m $(INSTMODE) -o $(INSTOWNER) -g $(INSTGROUP) car-autorun $(INSTDIR)


clean:
	rm -f  *.o
	rm -r car-server car-test car-autorun