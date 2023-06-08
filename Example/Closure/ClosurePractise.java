import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.Supplier;

public class ClosurePractise {

    private int curValue;
    public Supplier[] createCounter(int init) {
        this.curValue = init;
        AtomicInteger local = new AtomicInteger(init + 1);
        Supplier<int[]> add = () -> new int[]{++this.curValue, local.incrementAndGet()};
        Supplier<int[]> dec = () -> new int[]{--this.curValue, local.decrementAndGet()};
        Supplier<int[]> reset = () -> {
            this.curValue = init;
            local.set(init + 1);
            return new int[]{this.curValue, local.get()};
        };
        return new Supplier[] {add, dec, reset};
    }

    public static void main(String[] args) {
        var sol = new ClosurePractise();
        var counters = sol.createCounter(5);
        var res = new int[][] {(int [])counters[0].get(), (int [])counters[2].get(), (int [])counters[1].get()};
        for (var unit: res) {
            System.out.printf("%d %d\n", unit[0], unit[1]);
        }
    }
}
// 6 7
// 5 6
// 4 5
