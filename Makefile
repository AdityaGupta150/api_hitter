all: send.cpp
	g++ send.cpp -lpthread -o send

try: all
	./send localhost

clean:
	rm ./send
