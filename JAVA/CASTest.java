package practise;

import java.util.concurrent.atomic.AtomicReference;

class Spinlock {
    private final AtomicReference<Thread> cas;

    Spinlock(AtomicReference<Thread> cas) {
        this.cas = cas;
    }

    public void lock() {
        Thread current = Thread.currentThread();
        // 利用CAS
        while (!cas.compareAndSet(null, current)) {
            // DO nothing
            System.out.println("I am spinning");
        }
    }

    public void unlock() {
        Thread current = Thread.currentThread();
        cas.compareAndSet(current, null);
    }
}

class Task implements Runnable {
    private final AtomicReference<Thread> cas;
    private final Spinlock slock;

    Task(AtomicReference<Thread> cas) {
        this.cas = cas;
        this.slock = new Spinlock(cas);
    }

    @Override
    public void run() {
        slock.lock(); //上锁
        for (int i = 0; i < 10; i++) {
            System.out.println(i);
        }
        slock.unlock();
    }
}

public class CASTest {
    public static void main(String[] args) {
        AtomicReference<Thread> cas = new AtomicReference<>();
        Thread thread1 = new Thread(new Task(cas));
        Thread thread2 = new Thread(new Task(cas));
        thread1.start();
        thread2.start();
    }
}
