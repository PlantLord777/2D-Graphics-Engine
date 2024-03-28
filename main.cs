using System;
using System.Runtime.InteropServices;



class Class1
{
    [DllImport("ratgraphics.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int rat();
    [DllImport("ratgraphics.dll", CallingConvention = CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.BStr)]
    public static extern string GetInput();

    static void Main(string[] args)
    {
        
        Console.WriteLine("rats");
        rat();

        while(true)
        {
            
            Console.WriteLine(GetInput());
        }

    }

    public string sayRat()
	{
		return "RATS ARE IN MY WALLS";
	}
}


