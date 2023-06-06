package Example.Async;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class AsyncPractise {
    public final ExecutorService executorService = Executors.newCachedThreadPool(); //newCachedThreadPool自动分配线程个数

    private void g() {
        System.out.println("g 1");
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
            return;
        }
        System.out.println("g 2");
    }

    private void f() {
        var future = executorService.submit(this::g);
        try {
            Thread.sleep(1);
            System.out.println("f 1");
            future.get(); //阻塞等待
        } catch (InterruptedException | ExecutionException e) {
            System.out.println(e.getMessage());
            return;
        }
        System.out.println("f 2");
    }

    public static void main(String[] args) {
        var ins = new AsyncPractise();
        var f = ins.executorService.submit(ins::f);
        System.out.println("start");
        try {
            f.get();
        } catch (InterruptedException | ExecutionException e) {
            System.out.println(e.getMessage());
        }
        System.out.println("end");
        ins.executorService.shutdown(); //销毁线程池, 不然承程序不会结束
    }
}

// start
// g 1
// f 1
// g 2
// f 2
// end