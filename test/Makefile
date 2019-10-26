TARGET = parec.out
PKG_CONFIG = `pkg-config libpulse-simple --cflags --libs`
SRC = parec.c

.PHONY: all clean

all: $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(PRG_CONFIG)

clean:
	rm -f $(TARGET)
