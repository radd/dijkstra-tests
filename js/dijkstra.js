function dijkstra(graf)
{
	var t0 = new Date();

	var wielkosc = graf.length;
	var dystans = new Array(wielkosc); 
	var tab_wizytacji = new Array(wielkosc); 
	
	var wynik = new Array(wielkosc);
	for (var g = 0; g<wielkosc; ++g) {
		wynik[g] = new Array(wielkosc);
	}
	
	for (g = 0; g<wielkosc; ++g) {
		for (k = 0; k<wielkosc; ++k) {
			wynik[k][g] = 0;
		}
	}
	
	var max = 99999;
	
	for(i = 0; i < wielkosc; ++i){

        for(j = 0; j < wielkosc; ++j)
        {
            if(graf[i][j] == 0){
                graf[i][j] = max;
            }
        } 
    }
	
	punkt_start = 0;
	punkt_koniec = 0;
	
	for (g = 0; g<wielkosc; ++g) {
		punkt_start = g;
		for (k = 0; k<wielkosc; ++k) {
			punkt_koniec = k;

			for(var i = 0; i < wielkosc; ++i) {
				dystans[i] = max;
			}
			dystans[punkt_start] = 0;

			for(var i = 0; i < wielkosc; ++i) {
				tab_wizytacji[i] = 0;
			}

			for(i = 0; i < wielkosc; ++i){
				var aktualny = -1;
				for(j = 0; j < wielkosc; ++j){
					if(tab_wizytacji[j] === 1)
					{
						continue;
					}
					if(aktualny == -1 || dystans[j] < dystans[aktualny])
					{
						aktualny = j
					}
				}
				
				tab_wizytacji[aktualny] = 1;

				for(j = 0; j < wielkosc; ++j)
				{
				
					droga = dystans[aktualny] + graf[aktualny][j];
					if(droga < dystans[j]){
						dystans[j] = droga;
					}
				}  
			}
			
			wynik[k][g] = dystans[k];
			wynik[g][k] = dystans[k];
		}
	}

	var t1 = new Date();
	console.log("" + (t1 - t0) + "")

	return wynik;	
}



function loadJSON(path, success, error)
{
	/// przegladarka
    // var xhr = new XMLHttpRequest();
    // xhr.onreadystatechange = function()
    // {
        // if (xhr.readyState === XMLHttpRequest.DONE) {
            // if (xhr.status === 200) {
                // if (success)
                    // success(JSON.parse(xhr.responseText));
            // } else {
                // if (error)
                    // error(xhr);
            // }
        // }
    // };
    // xhr.open("GET", path, true);
    // xhr.send();
	
	
	/// node
	var fs = require("fs");
	var contents = fs.readFileSync(path);
	success(JSON.parse(contents));
}


var graf;

const args = process.argv;
//console.log(args[2]);

var size = 10;

switch(args[2]) {
	case "10": size=10; break;
	case "100": size=100; break;
	case "200": size=200; break;
	case "300": size=300; break;
}

var name= size + "";
var path = "../_grafy/" + name + "/graf_" + name + ".json";

loadJSON(path,
	function(data) { 
		graf = data; 
		
		var wynik = dijkstra(graf); 

		if (args.length > 3 && args[3] === "-r") {
			var from = -1, to = -1;
			
			if(args.length > 4)
				from = parseInt(args[4]);

			if(args.length > 5)
				to = parseInt(args[5]);

			if(from < 0 || from >= size)
				from = 0;
			
			if(to < 0 || to >= size)
				to = 1;
			
			console.log("Wynik (od " + from + " do " + to + "): " + wynik[from][to]);
			console.log();
		}
		
	},
    function(xhr) { console.error(xhr); }
);



