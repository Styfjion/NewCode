package JAVA;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Lee599 {
    public String[] findRestaurant(String[] list1, String[] list2) {
        Map<String, Integer> records = new HashMap<>();

        for(int i = 0; i < list1.length; i++) {
            records.put(list1[i], i);
        }

        List<String> resultList = new ArrayList<>();
        int minSum = list1.length + list2.length;
        for (int i = 0; i < list2.length; i++) {
            if (!records.containsKey(list2[i])) {
                continue;
            }
            int curSum = i + records.get(list2[i]);
            if (curSum > minSum) {
                continue;
            }
            if (curSum < minSum) {
                resultList.clear();
                minSum = curSum;
            }
            resultList.add(list2[i]);
        }
        return resultList.toArray(new String[0]);
    }
}
