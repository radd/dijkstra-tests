$size = $args[0]
$from = $args[1]
$to = $args[2]
$wyniki = ""

If($size -is [int] -and $from -is [int] -and $to -is [int])
{
cd .\c\
write-host "-------------------------- C -----------------------------"
.\dijkstra.exe $size -r $from $to
write-host ""
cd ..

cd .\cpp\
write-host "------------------------- C++ ----------------------------"
.\dijkstra.exe $size -r $from $to
write-host ""
cd ..

cd .\cs\
write-host "------------------------- C# -----------------------------"
.\dijkstra.exe $size -r $from $to
write-host ""
cd ..

cd .\java\
write-host "------------------------ JAVA ----------------------------"
java -jar .\dijkstra.jar $size -r $from $to
write-host ""
cd ..

cd .\js\
write-host "--------------------- JavaScript -------------------------"
node .\dijkstra.js $size -r $from $to
write-host ""
cd ..

cd .\python\
write-host "----------------------- Python ---------------------------"
pypy3 .\dijkstra.pyc $size -r $from $to
write-host ""
cd ..

}
ELSE {
	write-host "Podaj porawne wartosci"
}





