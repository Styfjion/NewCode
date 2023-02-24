/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2023. All rights reserved.
 */

package reftest;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class RefTest {
    static class Data
    {
        public int id;
        public String name;
        public List<Integer> data;

        public Data(int id, String name)
        {
            this.id = id;
            this.name = name;
            data = new ArrayList<>();
        }

        @Override
        public String toString() {
            return "Data{" + "id=" + id + ", name='" + name + '\'' + ", data=" + data + '}';
        }
    }

    public static void ChangeVal(Data data)
    {
        data.id += 1;
        data.name += "post";
    }

    public static void SetList(List<Integer> data)
    {
        data.add(1);
        data.add(2);
        data = new ArrayList<>();
        data.add(3);
        System.out.println("now data is " + data);
    }

    public static void Show(HashMap<Integer, Data> dict)
    {
        for(var item : dict.entrySet())
        {
            System.out.println(item.getKey().toString() + ':' + item.getValue());
        }
    }

    public static void main(String[] args)
    {
        var dict = new HashMap<Integer, Data>(){{
            put(1, new Data(1, "test1"));
            put(2, new Data(2, "test2"));}};

        for (var item : dict.entrySet())
        {
            item.getValue().name += "***";
        }

        Show(dict);

        for (var item : dict.entrySet())
        {
            ChangeVal(item.getValue());
        }

        var data = dict.get(1).data;
        SetList(data);
        Show(dict);
    }
}
