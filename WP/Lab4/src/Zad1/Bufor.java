package Zad1;

import java.util.Random;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Bufor {
    static volatile String[] bufor = new String[10];
    static ReentrantLock lock = new ReentrantLock();
    static Condition empty = lock.newCondition();
    static Condition full = lock.newCondition();
}