program main(input, output);
    var res, n: integer;
begin
    read(n);
    res := 1;
    while(n > 0) do
    begin
        res := res * n;
        n := n - 1
    end;
    write(res)
end.
