$data1 = Get-Date
$graf = "", "", ""
$czas = ""

write-host "-------------------------- C -----------------------------"

For ($i=0; $i -lt 5; $i++)
{
	write-host "Pomiar " ($i+1)
	For ($j=1; $j -lt 4; $j++)
	{
		$ile = $j*100
		$czas = .\dijkstra.exe $ile
		$graf[$j-1]+= $czas
		$graf[$j-1] += "`r`n"
		
		write-host "  Graf:" $ile "Czas:" $czas"ms"
	}
	write-host ""	
}

$data1.ToUniversalTime() >> output.log
"------------------------------------------- C --------------------------------------------" >> output.log
"Graf 100" >> output.log
$graf[0]  >> output.log
"Graf 200" >> output.log
$graf[1] >> output.log
"Graf 300" >> output.log
$graf[2]  >> output.log



If($args[0] -ne "all") {
	write-host "Press any key to continue..."
	[void][System.Console]::ReadKey($true)
}



