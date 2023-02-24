using System.Runtime.InteropServices.JavaScript;

namespace CsharpUse;

public class RefTest
{
    public class Data
    {
        public int id;
        public string name;
        public List<int> data = new();

        public Data(int id, string name)
        {
            this.id = id;
            this.name = name;
        }

        public override string ToString()
        {
            var str_data = data.Select(e => e.ToString()).ToList();
            return $"id is {id}, name is {name}, data is {String.Join(',', str_data)}";
        }
    }

    public static void ChangeVal(Data data)
    {
        data.id += 1;
        data.name += "post";
    }

    public static void SetList(List<int> data)
    {
        data.Add(1);
        data.Add(2);
        var stub = new List<int>();
        data = stub;
        data.Add(3);
        Console.WriteLine($"now data is { String.Join(',', data.Select(e => e.ToString()).ToList())}");
    }

    public static void Show(Dictionary<int, Data> dict)
    {
        foreach (var item in dict)
        {
            Console.WriteLine($"key is {item.Key}, and val is {item.Value}");
        }
    }
    
    public static void Main()
    {
        var dict = new Dictionary<int, Data>(){{1, new Data(1, "test1")}, {2, new Data(2, "test2")}};

        foreach (var item in dict)
        {
            item.Value.name += "***";
        }

        Show(dict);
        
        foreach (var item in dict)
        {
            ChangeVal(item.Value);
        }
        
        var data = dict[1].data;
        SetList(data);
        Show(dict);
    }
}
