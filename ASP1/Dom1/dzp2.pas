program dzp2;
uses Sysutils;
type
  TNode = ^List;
  tablica = array ['A'..'Z'] of real;
  List = record
    info : record
      oznaka : char;
      vrednost : real;
    end;
    next : TNode;
  end;
 var
   stek : TNode;
   izraz : string;
   vrednosti : tablica;
   i: integer;
   rez : real;
   flag : boolean;
procedure UbaciVrednosti ( stek : TNode; vrednosti : tablica );
var
  tmp : TNode;
begin
  tmp := stek;
  while tmp <> nil do begin
      tmp^.info.vrednost := vrednosti[tmp^.info.oznaka];
      tmp := tmp^.next;
  end;
end;
procedure Push_2(var stek: TNode; x: char; vrednost :  real);
var
   pom : TNode;
begin
 new(pom);
 pom^.info.oznaka := x ;
 pom^.info.vrednost := vrednost;
 pom^.next := stek;
 stek := pom;
end;
function Pop_2(var stek: TNode; var oprnd : real): char;
var
   pom : TNode;
begin
     if stek = nil then begin
    flag := false;
    Pop_2 := ' ';
 end
 else begin
       pom := stek;
       stek := pom^.next;
       oprnd := pom^.info.vrednost;
       Pop_2 := pom^.info.oznaka;
       dispose(pom);
  end;
end;
procedure DestroyStack ( stek: TNode );
var
  tek : TNode;
begin
  while stek <> nil do begin
      tek := stek^.next;
      dispose(stek);
      stek := tek;
  end;
end;
function Pop(var stek: TNode; var flag : boolean): char;
var
   pom : TNode;
begin
 if stek = nil then begin
    flag := false;
    Pop := ' ';
 end
 else begin
       pom := stek;
       stek := pom^.next;
       Pop := pom^.info.oznaka;
       dispose(pom);
  end;
end;
procedure Push(var stek: TNode; x: char);
var
   pom : TNode;
begin
 new(pom);
 pom^.info.oznaka := x ;
 pom^.next := stek;
 stek := pom;
end;
function Eval_1( var vrednosti: tablica ): string ;
var
  flag : boolean;
  stek : TNode;
  c, oprnd : char;
  i : integer;
  operacije, oznake : set of char;
begin
  write('Unesite izraz u postfiksnoj formi: ');
  readln(izraz);

  oznake := ['A'..'Z'];
  stek := nil;
  flag := true;
  i := 1;
  operacije := [ '+', '-', '/', '*'];

  while i <= length(izraz) do begin
      c := izraz[i];
      if c in oznake then
         Push(stek, c)
      else if c in operacije then begin
        oprnd := Pop(stek, flag);
        oprnd := Pop(stek, flag);
        Push(stek, oprnd);
      end;
      if not flag then break;
      i := i + 1;
  end;
  oprnd := Pop(stek, flag);
  if (stek = nil) and flag then begin
    writeln('Izraz je ispravan, sada unesite vrednosti za date promenljive:');
    for i:= 1 to length(izraz) do begin
        c := izraz[i];
        if c in oznake then begin
          oznake := oznake - [c];
          write( c, '? ');
          readln(vrednosti[c]);
        end;
        Eval_1 := izraz;
    end;
  end else begin
      writeln('Vas izraz je neispravan!');
      DestroyStack( stek );
      Eval_1 := ''
  end;
end;
function Eval_2 ( izraz : string; vrednosti: tablica): real;
var
  flag : boolean;
  stek : TNode;
  c, o1, o2 : char;
  i : integer;
  oprnd1, oprnd2, rez : real;
  operacije, oznake : set of char;
begin
  stek := nil;
  i := 1;
  operacije := [ '+', '-', '/', '*'];
  oznake := ['A'..'Z'];

  UbaciVrednosti( stek, vrednosti );

  while i <= length(izraz) do begin
      c := izraz[i];
      if c in oznake then
         Push_2(stek, c, vrednosti[c] )
      else if c in operacije then begin
        o2 := Pop_2(stek, oprnd2);
        o1 := Pop_2(stek, oprnd1);
        case c of
        '+': rez := oprnd1 + oprnd2;
        '-': rez := oprnd1 - oprnd2;
        '*': rez := oprnd1 * oprnd2;
        '/': rez := oprnd1 / oprnd2;
        end;
        Push_2(stek, '@', rez );
      end;
      i := i + 1;
  end;
  Eval_2 := stek^.info.vrednost;
  dispose(stek);
end;
procedure Izmena( var vrednosti: tablica );
var
  ulaz : string;
begin
  write('Unesite oznake promenljivih koje zelite da promenite: ');
  readln(ulaz);
  for i := 1 to length( ulaz ) do begin
      if ( ulaz[i] >= 'A') and ( ulaz[i] <= 'Z') then begin
        write( ulaz[i], '? ');
        readln(vrednosti[ulaz[i]]);
      end;
  end;
end;

begin
  flag := false;
  izraz := '';

  repeat
  writeln('-------- Meni --------');
  writeln('1. Unesite postfiksni izraz uz inicijalizaciju vrednosti');
  writeln('2. Promena vrednosti tablice');
  writeln('3. Izracunavanje izraz');
  writeln('0. Izlaz');
  writeln('----------------------');

  readln(i);
  case i of
  1: begin izraz := Eval_1(vrednosti); if izraz <> '' then flag := true else flag := false end;
  2: Izmena(vrednosti);
  3: begin if flag then begin rez := Eval_2(izraz, vrednosti); writeln('Rezultat iznosi: ', rez:0:2) end else writeln('Prvo unesite korektan izraz!') end;
  0: writeln('Pozdrav!');
  end;
  until i = 0;
  readln;
end.

