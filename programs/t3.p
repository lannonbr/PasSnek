{* A much larger program which includes assignments, writing, and conditionals *}
program main(input, output);
    var x : integer;
begin
    x := 2; { Gen an assign }
    if x = 4 then { Gen another assign }
    begin
        x := 10; { assign }
        x := 20; { assign }
        x := 30; { assign }
        write(40); { proc call with expr list of len 1 }
        write(x) { proc call with expr list of len 1 }
    end
    else
        x := 7; { assign }
    write(x)
end.
