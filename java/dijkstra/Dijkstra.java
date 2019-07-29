package dijkstra;

import org.json.JSONArray;
import org.json.JSONException;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Dijkstra {

	public static void main(String[] args) {
		
		int size = 10;

		if (args.length != 0)
        {				
			switch(args[0]) {
				case "10": size=10; break;
				case "100": size=100; break;
				case "200": size=200; break;
				case "300": size=300; break;
			}
		}
		String name= size + "";
		String path = "../_grafy/" + name + "/graf_" + name + ".json";
		
		JSONArray jsonArray = new JSONArray();
		try {
			 jsonArray = parseJSONFile(path);
		} catch (IOException | JSONException e) {
			e.printStackTrace();
		}
			
		int len = jsonArray.length();
		int[][] graf = new int[len][len];
		
		try {
			for(int i = 0; i < len; ++i) {
				JSONArray row = jsonArray.getJSONArray(i);
				for(int j = 0; j < len; ++j) {
					graf[i][j] = row.getInt(j);
				}
			}		
		} catch (JSONException e) {
			e.printStackTrace();
		}
		
	/*	for(int i = 0; i < len; ++i) {
			for(int j = 0; j < len; ++j) {
				System.out.println(graf[i][j] + ", ");
			}
			System.out.println("");
		} */	
			
		int[][] wynik = algorytm(graf); 	
		
		if (args.length > 1 && args[1].equals("-r")) {
			int from = -1, to = -1;
			
			if(args.length > 2)
				from = Integer.parseInt(args[2]);

			if(args.length > 3)
				to = Integer.parseInt(args[3]);

			if(from < 0 || from >= size)
				from = 0;
			
			if(to < 0 || to >= size)
				to = 1;
			
			System.out.println("Wynik (od " + from + " do " + to + "): " + wynik[from][to]);
			System.out.println();
		}
			
			
		
	}
	
	static JSONArray parseJSONFile(String filename) throws  IOException, JSONException {
        String content = new String(Files.readAllBytes(Paths.get(filename)));
        return new JSONArray(content);
    }
	
	static int[][] algorytm(int[][] graf)
	{

		long startTime = System.currentTimeMillis();
		int wielkosc = graf.length;

		int[] dystans = new int[wielkosc]; 
		int[] tab_wizytacji = new int[wielkosc]; 
		
		int[][] wynik = new int[wielkosc][wielkosc]; 

		for (int g = 0; g<wielkosc; ++g) {
			for (int k = 0; k<wielkosc; ++k) {
				wynik[k][g] = 0;
			}
		}
		
		int max = 99999;
		for(int i = 0; i < wielkosc; ++i){

	        for(int j = 0; j < wielkosc; ++j)
	        {
	            if(graf[i][j] == 0){
	                graf[i][j] = max;
	            }
	        } 
	    }
		
		int punkt_start = 0;
		int punkt_koniec = 0;
	
		for (int g = 0; g<wielkosc; ++g) {
			punkt_start = g;
			for (int k = 0; k<wielkosc; ++k) {
				punkt_koniec = k;
		
				for(int i = 0; i < wielkosc; ++i) {
				    dystans[i] = max;
				}
				
				dystans[punkt_start] = 0;
				
				for(int i = 0; i < wielkosc; ++i) {
				    tab_wizytacji[i] = 0;
				}

				for(int i = 0; i < wielkosc; ++i){
			        int aktualny = -1;
			        for(int j = 0; j < wielkosc; ++j){
			            if(tab_wizytacji[j] == 1)
			            {
			                continue;
			            }
			            if(aktualny == -1 || dystans[j] < dystans[aktualny])
			            {
			                aktualny = j;
			            }
			        }
			        
			        tab_wizytacji[aktualny] = 1;
		
			        for(int j = 0; j < wielkosc; ++j)
			        {
			            int droga = dystans[aktualny] + graf[aktualny][j];
			            if(droga < dystans[j]){
			                dystans[j] = droga;
			            }
			        }  
			    }
				
				wynik[k][g] = dystans[k];
				wynik[g][k] = dystans[k];
		
			}
	}


		long estimatedTime = System.currentTimeMillis() - startTime;
		System.out.println("" + estimatedTime + "");  

		return wynik;
		
	}

}
