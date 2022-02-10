package JAVA;

import java.util.ArrayList;
import java.util.List;

public class Lee1447 {
    public List<String> simplifiedFractions(int n) {
        List<String> result = new ArrayList<>();
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                if (gcd(i, j) == 1) {
                    result.add(i + "/" + j);
                }
            }
        }
        return result;
    }

    public int gcd(int a, int b) {
        return b != 0 ? gcd(b, a % b) : a;
    }
}
