using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;



class MAIN
{


  
    
    


    static void Main(string[] args)
    {
        
        Console.WriteLine("rats");
        

        var autoEvent = new AutoResetEvent(false);

        //makes gameloop run every .1s
        var stateTimer = new Timer(LOOP.GameLoop, autoEvent, 50, 50);
        
        autoEvent.WaitOne();
        
    }


    


        //important function
        public string sayRat()
	{
		return "RATS ARE IN MY WALLS";
	}
}

class LOOP
{
    //Function imports from ratgraphics
    public static bool first=true;
    [DllImport("ratgraphics.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int rat();
    [DllImport("ratgraphics.dll", CallingConvention = CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.BStr)]
    public static extern string GetInput();
    [DllImport("ratgraphics.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void ResetInput();
    [DllImport("ratgraphics.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Buffer();
    [DllImport("ratgraphics.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void drawSquare(float x, float y, float sidelength, float r, float g, float b);

    static int[,] map = new int[20,20];
    static int currentposx = 2;
    static int currentposy = 4;
    static Queue<string> snakepos = new Queue<string>();
    static int snakelength = 1;

    public static void GameLoop(Object stateInfo)
    {
        if (first)
        {
            Console.WriteLine("");
            first = !first;
            //initializes the canvas
            //TODO rename this
            rat();
            createMap();
        }
        

        //Gets keyboard input as a string from rat graphics
        string s = GetInput();
        s= s.Trim();
        string[] ss = s.Split(' ');
        if (s.Split(' ')[0]=="65"&&( s.Split(' ')[2] == "0" || s.Split(' ')[2] == "1"))
        {
            if (currentposx >1) {
                
                currentposx -= 1;
                
                MoveSnake(currentposx, currentposy);
            }
        }
        if (s.Split(' ')[0] == "68" &&( s.Split(' ')[2] == "0" || s.Split(' ')[2] == "1"))
        {
            if (currentposx < 18)
            {
                
                currentposx += 1;
                
                MoveSnake(currentposx, currentposy);
            }
        }
        if (s.Split(' ')[0] == "83" && (s.Split(' ')[2] == "0" || s.Split(' ')[2] == "1"))
        {
            if (currentposy >1)
            {
                
                currentposy -= 1;
                
                MoveSnake(currentposx, currentposy);
            }
        }
        if (s.Split(' ')[0] == "87" && (s.Split(' ')[2] == "0" || s.Split(' ')[2] == "1"))
        {
            if (currentposy < 18)
            {
                
                currentposy += 1;
                
                MoveSnake(currentposx, currentposy);
            }

        }
        if (s != "none")
        {
            Console.WriteLine(s);
            //stops repreated reading of same input
            //ResetInput();
        }

        for (int r = 0; r < 20; r++)
        {
            for (int c = 0; c < 20; c++)
            {
                if (map[r,c] == 1)
                    drawSquare((r-10) * .1f, (c-10) * .1f,.1f,0f, 1.0f, 0f);
                if (map[r,c]==2)
                    drawSquare((r-10) * .1f, (c-10) * .1f,.1f, 1f, 0f, 0f);
                if (map[r, c] == 3)
                    drawSquare((r-10) * .1f, (c-10) * .1f,.1f, 0f, 0f, 0f);
            }
        }
        //buffers graphics
        Buffer();
    }

    public static void createMap()
    {
        
        for(int r=0;r<20;r++)
        {
            for(int c =0; c< 20; c++)
            {
                map[r,c] = 0;
            }
        }


        MoveSnake(2, 4);

        for (int r = 0; r < 20; r++)
        {
            map[r, 0] = 3;
            map[r, 19] = 3;
        }
        for(int c =0; c<20;c++)
        {
            map[0, c] = 3;
            map[19, c] = 3;
        }        createApple();
    }

    public static void createApple()
    {
        var rand = new Random();
        int r = rand.Next(11)+1;
        int c = rand.Next(11)+1;
        while (map[r, c] != 0)
        {
             r = rand.Next(17) + 1;
             c = rand.Next(17) + 1;
        }
        map[r,c] = 2;
        snakelength++;
    }

    public static void MoveSnake(int x, int y)
    {
        if (map[x, y] == 2)
            eatApple();

        foreach (string s in snakepos)
        {

            map[Int32.Parse(s.Split(' ')[0]), Int32.Parse(s.Split(' ')[1])] = 0;

        }
        snakepos.Enqueue(x + " " + y);
        while(snakepos.Count > snakelength)
        {
            snakepos.Dequeue();
        }
        foreach(string s in snakepos)
        {

            map[Int32.Parse(s.Split(' ')[0]), Int32.Parse(s.Split(' ')[1])] = 1;
        
        }
    }

    public static void eatApple()
    {
        Console.WriteLine("Apple");
        createApple();
    }
}

