CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = store_app
OBJS = main.o address.o credit_card.o person.o product.o transaction.o store.o
HDRS = address.h credit_card.h person.h product.h transaction.h store.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
