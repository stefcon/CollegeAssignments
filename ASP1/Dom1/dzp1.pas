program dzp1;
const
  MAX_1 = 100;
  MAX_2 = 5050;
type
  niz = array [1..MAX_2] of integer;
var
  i, n, len: integer;
  foo : real;
  lin_matrica : niz;
  flag : boolean;

function Inicijalizacija(var lin_matrica: niz) : integer;
var
  n, i, j, ind: integer;
begin
  write('Unesite dimenziju kvadratne matrice( max = ', MAX_1, ' ): ');
  repeat
  readln(n);
  if (n <= 0) or (n > MAX_1) then writeln('Unesite ispravan podatak!');
  until (n >= 1) and (n < MAX_1);
  writeln('Unesite elemente donje trougaone matrice: ');
  ind := 0;
  for i := 1 to n do begin
    for j:= 1 to n do begin
      if (i >= j) then begin
        ind := ind + 1;
        write( i, ', ', j, '? ');
        readln(lin_matrica[ind]);
      end;
    end;
  end;
  Inicijalizacija := n;
end;

function Adresna( i, j : integer) : integer;
var
  tmp : integer;
begin
  if (i < j) then begin
    tmp := i;
    i := j;
    j := tmp;
  end;
  Adresna := (i * ( i - 1)) div 2 + j - 1;
end;

function Dohvati(lin_matrica : niz; n : integer) : integer;
var
  i, j: integer;
begin
  repeat
  readln(i, j);
  if (i < 0) or (i > n ) or (j < 0) or (j > n) then writeln('Pokusajte ponovo');
  until (i > 0) and (i <= n) and (j > 0) and (i <= n);
  Dohvati := lin_matrica[1 + Adresna(i,j)];
end;

procedure Postavi(var lin_matrica: niz; n: integer);
var
  i, j, elem: integer ;
begin
  writeln('Unesite vrednost elementa i njegovu zeljenu poziciju');
  repeat
  readln(elem, i, j);
  if (i < 0) or (i > n ) or (j < 0) or (j > n) then writeln('Pokusajte ponovo');
  until (i > 0) and (i <= n) and (j > 0) and (i <= n);
  lin_matrica[1 + Adresna(i, j)] := elem;
end;
procedure Ispis( lin_matrica: niz; n: integer);
var
  i,j, ind: integer;
begin
  for i:= 1 to n do begin
    ind := 0;
    for j := 1 to n do begin
      ind := ind + 1;
      write(lin_matrica[1 + Adresna(i, j)]);
      if ind = n then writeln() else write(' ');
    end
  end
end;
begin
  flag := false;
  repeat
  writeln('------ Meni ------');
  writeln(' 1. Stvaranje Matrice');
  writeln(' 2. Pristup odredjenom elementu');
  writeln(' 3. Postavljanje nove vrednosti zadatom elementu');
  writeln(' 4. Dohvatanje broja nepodrazumevanih elemenata');
  writeln(' 5. Ispis matrice(zajedno sa podrazumevanim elementima)');
  writeln(' 6. Racunanje ostvarene ustede');
  writeln(' 7. Brisanje matrice');
  writeln(' 0. Izadji');
  writeln('------------------');

  readln(i);

  case i of
  1: begin flag:= true; n := Inicijalizacija(lin_matrica); len := (n * (n+1)) div 2 end;
  2: begin if flag then writeln('Vrednost trazenog elementa je ', Dohvati( lin_matrica, n))
     else writeln('Morate prvo da inicajlizujete matricu!') end ;
  3: begin if flag then begin Postavi(lin_matrica, n) end else writeln('Morate prvo da inicajlizujete matricu!') end;
  4: if flag then writeln('Broj nepodrazumevanih elemenate je ', len) else writeln('Morate prvo da inicajlizujete matricu!');
  5: begin if flag then begin Ispis(lin_matrica, n) end else writeln('Morate prvo da inicajlizujete matricu!') end;
  6: if flag then begin foo := (n*n - len)/(n*n)* 100; writeln('Ostvarena usteda iznosi ', foo:0:2, '%')end
     else writeln('Morate prvo da inicajlizujete matricu!') ;
  7: begin flag := false; writeln('Matrica je obrisana')end;
  0: writeln('Pozdrav!');
  end;

  until  i = 0;
  readln;
end.

