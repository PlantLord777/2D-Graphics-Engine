using System;
using System.Runtime.InteropServices;
using System.Threading;



class MAIN
{


  
    
    


    static void Main(string[] args)
    {
        
        Console.WriteLine("rats");
        

        var autoEvent = new AutoResetEvent(false);

        //makes gameloop run every .1s
        var stateTimer = new Timer(LOOP.GameLoop, autoEvent, 100, 100);
        
        autoEvent.WaitOne();
        
    }


    


        //important function
        public string say()
	{
		return "Say";
	}
}

class LOOP
{
    //Function imports from graphics
    public static bool first=true;
    [DllImport("graphics.dll", CallingConvention = CallingConvention.Cdecl)]
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

    public static void GameLoop(Object stateInfo)
    {
        if (first)
        {
            Console.WriteLine("");
            first = !first;
            //initializes the canvas
            //TODO rename this
            rat();
        }
        

        //Gets keyboard input as a string from rat graphics
        string s = GetInput();
        s= s.Trim();
        string[] ss = s.Split(' ');
        if (s.Split(' ')[0]=="65")
        {
            Console.WriteLine("AAAAAA");
            drawSquare( 0 , 0 ,.1f , 1,0,0);
            drawSquare(.5f,.5f,.1f , 0,1,0);
            drawSquare(.6f, .6f, .1f, 0, 1, 1);
            drawSquare(.7f,.7f,.1f , 0,0,1);
            //drawSquare(5, 5);
        }
        if (s != "none")
        {
            Console.WriteLine(s);
            //stops repreated reading of same input
            ResetInput();
        }
        

        //buffers graphics
        Buffer();
    }
}

