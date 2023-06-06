namespace CsharpUse;

public class AsyncPractise
{
    static async Task g()
    {
        Console.WriteLine("g 1");
        await Task.Delay(1000);
        Console.WriteLine("g 2");
    }
    static async Task f()
    {
        var a = g();
        Console.WriteLine("f 1");
        await a;
        Console.WriteLine("f 2");
    }

    public static void Main()
    {
        f().GetAwaiter().GetResult();
    }
    
    // g 1
    // f 1
    // g 2
    // f 2
}
