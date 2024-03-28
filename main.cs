using System;
using System.Runtime.InteropServices;



class Class1
{
    [DllImport("ratgraphics.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int rat();

    static void Main(string[] args)
    {
        
        Console.WriteLine("rats");
        rat();

    }

    public string sayRat()
	{
		return "RATS ARE IN MY WALLS";
	}
}


