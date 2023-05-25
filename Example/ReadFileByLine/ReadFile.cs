namespace CsharpUse;

public class ReadFile
{
    public static void Main()
    {
        const string fileName = @"test.env";
        var lines = File.ReadLines(fileName);
        var newlines = lines.Select(line => line.Split("=")[0]).ToList();
        Console.WriteLine(string.Join(',', newlines));
    }
}
