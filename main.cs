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
        //65 is A
        if (s.Split(' ')[0]=="65"&&( s.Split(' ')[2] == "0" || s.Split(' ')[2] == "1"))
        {
            //keeps within bounds
            if (currentposx >1) {
                
                currentposx -= 1;
                
                MoveSnake(currentposx, currentposy);
            }
        }
        //68 is D
        if (s.Split(' ')[0] == "68" &&( s.Split(' ')[2] == "0" || s.Split(' ')[2] == "1"))
        {
            if (currentposx < 18)
            {
                
                currentposx += 1;
                
                MoveSnake(currentposx, currentposy);
            }
        }
        //83 is S
        if (s.Split(' ')[0] == "83" && (s.Split(' ')[2] == "0" || s.Split(' ')[2] == "1"))
        {
            if (currentposy >1)
            {
                
                currentposy -= 1;
                
                MoveSnake(currentposx, currentposy);
            }
        }
        //87 is W
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
            //commented out to keep snake moving
            //ResetInput();
        }

        //draw the map based on held value
        //1 = green(snake) 2 = red (apple) 3 = black(wall)
        for (int x = 0; x < 20; x++)
        {
            for (int y = 0; y < 20; y++)
            {
                if (map[x,y] == 1)
                    drawSquare((x-10) * .1f, (y-10) * .1f,.1f,0f, 1.0f, 0f);
                if (map[x,y]==2)
                    drawSquare((x-10) * .1f, (y-10) * .1f,.1f, 1f, 0f, 0f);
                if (map[x, y] == 3)
                    drawSquare((x-10) * .1f, (y-10) * .1f,.1f, 0f, 0f, 0f);
            }
        }
        //buffers graphics
        Buffer();
    }

    public static void createMap()
    {
        //init map to 0
        for(int x=0;x<20;x++)
        {
            for(int y =0; y< 20; y++)
            {
                map[x,y] = 0;
            }
        }

        //set snake start pos to 2,4
        MoveSnake(2, 4);
        //adds walls
        for (int x = 0; x < 20; x++)
        {
            map[x, 0] = 3;
            map[x, 19] = 3;
        }
        for(int y =0; y<20;y++)
        {
            map[0, y] = 3;
            map[19, y] = 3;
        }        
        //create first apple
        createApple();
    }

    public static void createApple()
    {
        var rand = new Random();
        int x = rand.Next(11)+1;
        int y = rand.Next(11)+1;
        //loop until empty space found
        while (map[x, y] != 0)
        {
             x = rand.Next(17) + 1;
             y = rand.Next(17) + 1;
        }
        map[x,y] = 2;
       
    }

    public static void MoveSnake(int x, int y)
    {
        //create new apple if on smae tile as apple
        if (map[x, y] == 2)
            eatApple();

        //clear array of snake
        foreach (string s in snakepos)
        {

            map[Int32.Parse(s.Split(' ')[0]), Int32.Parse(s.Split(' ')[1])] = 0;

        }
        //add new pos
        snakepos.Enqueue(x + " " + y);
        //delete old spaces
        while(snakepos.Count > snakelength)
        {
            snakepos.Dequeue();
        }
        //set position on map
        foreach(string s in snakepos)
        {

            map[Int32.Parse(s.Split(' ')[0]), Int32.Parse(s.Split(' ')[1])] = 1;
        
        }
    }

    public static void eatApple()
    {
        Console.WriteLine("Apple");
        snakelength++;
        createApple();
    }
}

