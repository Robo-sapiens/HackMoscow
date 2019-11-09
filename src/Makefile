TARGET = parec.out
SRC = parec.cpp \
    arduino_serial.cpp

.PHONY: all clean

all: $(SRC)
	g++ -o $(TARGET) $(SRC) `pkg-config libpulse-simple fftw3 --cflags --libs` -pthread

clean:
	rm -f $(TARGET)
