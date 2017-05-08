program main(input, output);
	procedure prant(a: integer);
	begin
		write(a)
	end;
	function addOne(n1: integer): integer;
	begin
		addOne := n1 + 1
	end;
	function subOne(n2: integer): integer;
	begin
		subOne := n2 - 1
	end;
	procedure prant7;
	begin
		write(7)
	end;
begin
	prant(7);
	prant(addOne(addOne(5)));
	prant7;
	prant(subOne(addOne(1)))
end.
