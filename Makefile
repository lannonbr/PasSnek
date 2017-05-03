psc: pascal.tab.o lex.yy.o tree.o node.o symtable.o statement.o stmtstack.o util.o gencode.o regstack.o
	clang -g -o psc pascal.tab.o lex.yy.o tree.o node.o symtable.o statement.o util.o stmtstack.o gencode.o regstack.o -lfl -ly

tree.o: tree.c
	clang -g -c tree.c

gencode.o: gencode.c
	clang -g -c gencode.c

regstack.o: regstack.c
	clang -g -c regstack.c

util.o: util.c
	clang -g -c util.c

symtable.o: symtable.c
	clang -g -c symtable.c
	
node.o: node.c
	clang -g -c node.c

statement.o: statement.c
	clang -g -c statement.c

stmtstack.o: stmtstack.c
	clang -g -c stmtstack.c

pascal.tab.o: pascal.tab.c
	clang -g -c pascal.tab.c

pascal.tab.c: pascal.y
	bison -dv pascal.y

lex.yy.o: lex.yy.c
	clang -g -c lex.yy.c

lex.yy.c: pascal.l
	flex -l pascal.l

clean:
	rm -rf lex.yy.* pascal.tab.* *.o psc
