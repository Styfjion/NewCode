public class ClasurePractise
{
    public Func<int>[] CreateCounters(int init)
    {
        int curValue = init;
        var add = () => ++curValue;
        var dec = () => --curValue;
        var reset = () => curValue = init;
        return new []{add, dec, reset};
    }

    public static void Main()
    {
        var sol = new ClasurePractise();
        var counters = sol.CreateCounters(5);
        Console.WriteLine(counters[0]());
        Console.WriteLine(counters[2]());
        Console.WriteLine(counters[1]());
    }
}
// 6
// 5
// 4
