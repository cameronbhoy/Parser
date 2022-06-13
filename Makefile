main:
	g++ -o parser.out main.cpp Scanner.cpp Parser.cpp AST.cpp
run:
	./parser.out example.txt
	./parser.out example.txt > out.txt
	./parser.out out.txt
