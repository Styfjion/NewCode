package JAVA;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Lee717 {
    public boolean isOneBitCharacter(int[] bits) {
        if (bits[bits.length - 1] != 0) {
            return false;
        }
        List<Integer> bitsList = Arrays.stream(bits).boxed().collect(Collectors.toList());
        bitsList.remove(bitsList.size() - 1);
        var iter = bitsList.iterator();
        while (iter.hasNext()) {
            if (iter.next() == 1) {
                iter.remove();
                if (!iter.hasNext()) {
                    return false;
                }
                iter.next();
                iter.remove();
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Lee717 sol = new Lee717();
        int[] bits = {1, 0, 0};
        System.out.println(sol.isOneBitCharacter(bits));
    }
}
