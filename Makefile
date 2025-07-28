CC = clang
CFLAGS = -g
BUILDDIR = ./build
SRCDIR = ./src
OBJFILES = \
	$(BUILDDIR)/main.o \
	$(BUILDDIR)/buf.o \
	$(BUILDDIR)/db.o \
	$(BUILDDIR)/input.o \
	$(BUILDDIR)/menu.o \
	$(BUILDDIR)/entry.o \
	$(BUILDDIR)/file.o \
	$(BUILDDIR)/csv.o

$(BUILDDIR)/phonebook: $(OBJFILES)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/phonebook $(OBJFILES)

$(BUILDDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(BUILDDIR)/main.o

$(BUILDDIR)/buf.o: $(SRCDIR)/utils/buf.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/utils/buf.c -o $(BUILDDIR)/buf.o

$(BUILDDIR)/db.o: $(SRCDIR)/app/db.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/app/db.c -o $(BUILDDIR)/db.o

$(BUILDDIR)/input.o: $(SRCDIR)/core/input.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/core/input.c -o $(BUILDDIR)/input.o

$(BUILDDIR)/menu.o: $(SRCDIR)/app/menu.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/app/menu.c -o $(BUILDDIR)/menu.o

$(BUILDDIR)/entry.o: $(SRCDIR)/core/entry.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/core/entry.c -o $(BUILDDIR)/entry.o

$(BUILDDIR)/file.o: $(SRCDIR)/core/file.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/core/file.c -o $(BUILDDIR)/file.o

$(BUILDDIR)/csv.o: $(SRCDIR)/utils/csv.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/utils/csv.c -o $(BUILDDIR)/csv.o

clean:
	rm $(BUILDDIR)/phonebook $(BUILDDIR)/*.o
