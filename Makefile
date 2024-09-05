
CC = gcc

all: test_output

customer_output: customer.c
	rm -f customer_output lib_myLibrary.a test_output
	$(CC) -c .\customer.c -o customer_output

lib_myLibrary.a: customer_output
	ar rcs lib_myLibrary.a .\customer_output

test_output: main.c lib_myLibrary.a
	$(CC) -o test_output main.c -L. .\lib_myLibrary.a

run: test_output
	.\test_output.exe
	
clean:
	rm -f customer_output lib_myLibrary.a test_output