CC=gcc
SRCDIR=./src
INCDIR=./inc

# Source files
SRCFILES=main.c $(SRCDIR)/admin.c $(SRCDIR)/user.c

# Header files
HEADERS= $(INCDIR)/STD_TYPES.h $(INCDIR)/dataType.h $(INCDIR)/admin.h $(INCDIR)/user.h  

TARGET=main

$(TARGET): $(SRCFILES) $(HEADERS)
	$(CC)  -I$(INCDIR) -o $(TARGET) $(SRCFILES)

clean:
	rm -f $(TARGET)