program main(input, output);
	var i: integer;
begin
	read(i);
	{ Testing equality }
	if i = 0 then
		write(i)
	else
		write(7);
	{ Testing inequality }
	if i <> 10 then
		write(20)
	else
	begin
	end;
	{ Testing less than }
	if i < 10 then
		write(9)
	else
	begin
	end;
	{ Testing less than or equal to }
	if i <= 10 then
		write(10)
	else
	begin
	end;
	{ Testing greater than }
	if i > 10 then
		write(11)
	else
	begin
	end;
	{ Testing greater than or equal to }
	if i >= 10 then
		write(10)
	else
	begin
	end
end.
