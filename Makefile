.PHONY: clean check

libks.so: src/ks.c src/p_smirnov.c
	$(CC) -fPIC -shared src/ks.c src/p_smirnov.c -Iinclude/ -o libks.so

check: tests/KsTest.cpp tests/TestingData.txt libks.so
	$(CXX) tests/KsTest.cpp ./libks.so -Iinclude/ -o tests/test
	./tests/test

clean:
	rm -f libks.so tests/test

