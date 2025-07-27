CC = clang
BUILDDIR = ./build
SRCDIR = ./src
OBJFILES = \
	$(BUILDDIR)/main.o \
	$(BUILDDIR)/db.o \
	$(BUILDDIR)/buf.o

$(BUILDDIR)/phonebook: $(OBJFILES)
	$(CC) -o $(BUILDDIR)/phonebook $(OBJFILES)

$(BUILDDIR)/main.o: $(SRCDIR)/main.c
	$(CC) -c $(SRCDIR)/main.c -o $(BUILDDIR)/main.o

$(BUILDDIR)/db.o: $(SRCDIR)/app/db.c
	$(CC) -c $(SRCDIR)/app/db.c -o $(BUILDDIR)/db.o

$(BUILDDIR)/buf.o: $(SRCDIR)/utils/buf.c
	$(CC) -c $(SRCDIR)/utils/buf.c -o $(BUILDDIR)/buf.o

clean:
	rm $(BUILDDIR)/phonebook $(BUILDDIR)/*.csv $(BUILDDIR)/*.o
