using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Diagnostics;
using System.IO;


namespace ConsoleApp1
{
    class Dijkstra
    {

        static void Main(string[] args)
        {
            int size = 10;

            if (args.Length!= 0)
            {
                switch (args[0])
                {
                    case "10": size = 10; break;
                    case "100": size = 100; break;
                    case "200": size = 200; break;
                    case "300": size = 300; break;
                }
            }
            //Console.WriteLine(size);
            String name = size + "";
            String path = "../_grafy/" + name + "/graf_" + name + ".json";

            int[,] graf = new int[size, size];

            using (StreamReader r = new StreamReader(path))
            {
                string json = r.ReadToEnd();
                JArray array = JArray.Parse(json);

                for (int i =0; i < array.Count; i++)
                {
                    for (int j = 0; j < array.Count; j++)
                    {
                        graf[i, j] = (int) array[i][j];
                    }
                }
            }

            

            //for (int i = 0; i < graf.GetLength(0); i++)
            //{
            //    for (int j = 0; j < graf.GetLength(1); j++)
            //    {
            //        Console.Write(graf[i, j] + ", ");
            //    }
            //    Console.WriteLine();
            //}


            int[,] wynik = algorytm(graf);
			
			if (args.Length > 1 && args[1].Equals("-r")) {
				int from = -1, to = -1;
				
				if(args.Length > 2)
					from = Int32.Parse(args[2]);

				if(args.Length > 3)
					to = Int32.Parse(args[3]);

				if(from < 0 || from >= size)
					from = 0;
				
				if(to < 0 || to >= size)
					to = 1;
				
				Console.WriteLine();
				Console.WriteLine("Wynik (od " + from + " do " + to + "): " + wynik[from, to]);
				Console.WriteLine();
			}
			
            //Console.ReadKey();
        }

        static int[,] algorytm(int[,] graf)
        {
            var stopwatch = new Stopwatch();
            stopwatch.Start();

            int wielkosc = graf.GetLength(0);

            int[] dystans = new int[wielkosc];
            int[] tab_wizytacji = new int[wielkosc];

            int[,] wynik = new int[wielkosc, wielkosc];

            for (int g = 0; g < wielkosc; ++g)
            {
                for (int k = 0; k < wielkosc; ++k)
                {
                    wynik[k, g] = 0;
                }
            }

            int max = 99999;
            for (int i = 0; i < wielkosc; ++i)
            {

                for (int j = 0; j < wielkosc; ++j)
                {
                    if (graf[i, j] == 0)
                    {
                        graf[i, j] = max;
                    }
                }
            }
			
			int punkt_start = 0;
			int punkt_koniec = 0;
			
            for (int g = 0; g < wielkosc; ++g)
            {
                punkt_start = g;
                for (int k = 0; k < wielkosc; ++k)
                {
                    punkt_koniec = k;

					for (int i = 0; i < wielkosc; ++i)
                    {
                        dystans[i] = max;
                    }
					dystans[punkt_start] = 0;
                  
                    for (int i = 0; i < wielkosc; ++i)
                    {
                        tab_wizytacji[i] = 0;
                    }

                    for (int i = 0; i < wielkosc; ++i)
                    {
                        int aktualny = -1;
                        for (int j = 0; j < wielkosc; ++j)
                        {
                            if (tab_wizytacji[j] == 1)
                            {
                                continue;
                            }
                            if (aktualny == -1 || dystans[j] < dystans[aktualny])
                            {
                                aktualny = j;
                            }
                        }

                        tab_wizytacji[aktualny] = 1;

                        for (int j = 0; j < wielkosc; ++j)
                        {
                            int droga = dystans[aktualny] + graf[aktualny, j];
                            if (droga < dystans[j])
                            {
                                dystans[j] = droga;
                            }
                        }
                    }

                    wynik[k, g] = dystans[k];
                    wynik[g, k] = dystans[k];


                }
            }

            stopwatch.Stop();
            Console.Write(stopwatch.ElapsedMilliseconds);

            return wynik;
        }
    }
}
