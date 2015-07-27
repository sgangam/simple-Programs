/*
 * Copyright (c) 2015. Sriharsha Gangam <sriharsha.gangam@gmail.com>
 */

import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.atomic.AtomicInteger;

/**
 *
 *
 * @author Sriharsha Gangam
 */



class ParallelMergeSort {

    private final AtomicInteger counter = new AtomicInteger();
    private final int maxThreads;

    public ParallelMergeSort(int maxThreads) {
        this.maxThreads = maxThreads;
    }

    private class SortThread extends Thread {

        private final int start;
        private final int[] input;
        private final int end;

        SortThread(int[] input, int start, int end) {
            this.input = input;
            this.start = start;
            this.end = end;
        }

        @Override
        public void run() {
            boolean useThreads = false;
            if (counter.get() < maxThreads) {
                useThreads = true;
            }
            try {
                sort(input, start, end, useThreads);
            } catch (InterruptedException e) {
                this.interrupt();
            }

        }
    };


    public int[] sort(int[] input, boolean useThreads) throws InterruptedException {
        int[] output = Arrays.copyOf(input, input.length);
        if (input.length < 2) {
            return output;
        }

        sort(output, 0, input.length - 1, useThreads);
        return output;
    }

    private void sort(int[] arr, int start, int end, boolean useThreads) throws InterruptedException {
        if (start == end) {
            return;
        }
        int mid = (start + end) / 2;

        if (useThreads) {
            SortThread t1 = new SortThread(arr, start, mid);
            SortThread t2 = new SortThread(arr, mid + 1, end);

            t1.start(); counter.incrementAndGet();
            t2.start(); counter.incrementAndGet();
            t1.join(); counter.decrementAndGet();
            t2.join(); counter.decrementAndGet();
            
        } else {
            sort(arr, start, mid, useThreads);
            sort(arr, mid + 1, end, useThreads);
        }

        merge(arr, start, mid, end);
    }

    private void merge(int[] arr, int start, int mid, int end) {
        int head1 = start;
        int head2 = mid+1;

        int[] tmp = new int[end - start + 1];
        int ind = 0;
        while(head1 <= mid && head2 <= end) {
            if (arr[head1] > arr[head2]) {
                tmp[ind] = arr[head2];
                head2++;ind++;

            } else {
                tmp[ind] = arr[head1];
                head1++;ind++;
            }
        }

        while(head2 <= end) {
            tmp[ind] = arr[head2];
            head2++;ind++;
        }

        while(head1 <= mid ) {
            tmp[ind] = arr[head1];
            head1++;ind++;
        }

        for(int i = 0; i < end - start + 1; i++) {
            arr[i+start] = tmp[i];
        }

    }

    private void mergeInefficient(int[] arr, int start, int mid, int end) {
        int head1 = start;
        int head2 = mid+1;

        int[] tmp = new int[end - start + 1];
        int ind = 0;
        while(head1 <= mid && head2 <= end) {
            if (arr[head1] > arr[head2]) {
                tmp[ind] = arr[head2];
                head2++;ind++;

            } else {
                tmp[ind] = arr[head1];
                head1++;ind++;
            }
        }

        while(head2 <= end) {
            tmp[ind] = arr[head2];
            head2++;ind++;
        }

        while(head1 <= mid ) {
            tmp[ind] = arr[head1];
            head1++;ind++;
        }

        for(int i = 0; i < end - start + 1; i++) {
            arr[i+start] = tmp[i];
        }

    }



    public static void main(String[] args) throws InterruptedException {

        runCorrectnessTests();
        runBenchMark();
    }

    private static void runCorrectnessTests() throws InterruptedException {
        ParallelMergeSort psort = new ParallelMergeSort(10);

        int[][] inputs = new int[][]{   {}, {1}, {1,2}, {1,2}, {1,1}
                ,{2,1}, {1,2,1}, {3,2,1}, {1,2,3}, {2,3,1},
                {3,5,6,1,2,9,8,4,7,3,6,2,1}};

        for(int[] input: inputs) {
            int[] sorted = psort.sort(input, false);

            int[] expected = Arrays.copyOf(input, input.length);
            Arrays.sort(expected);

            System.out.println("output:" + Arrays.toString(sorted) + " expected:" + Arrays.toString(expected));
            assert Arrays.equals(sorted, expected);
        }

    }

    private static void runBenchMark() throws InterruptedException {
        int size = 50000000;
        int maxThreads = 10;
        int[] input = getRandomInput(size);
        int[] expected = Arrays.copyOf(input, input.length);
        Arrays.sort(expected);
        for(int tcount = 1; tcount <= maxThreads; tcount++) {

            long tstart = System.nanoTime();
            ParallelMergeSort psort = new ParallelMergeSort(tcount);
            long tend = System.nanoTime();
            int[] sorted = psort.sort(input, true);
            assert Arrays.equals(sorted, expected);
            System.out.println("Threads: " + tcount + " Time (ms):" + (tend - tstart));
        }

    }

    private static int[] getRandomInput(int size) {
        int[] retVal =  new int[size];
        long seed = System.currentTimeMillis();
        Random rand = new Random(seed);
        for (int i = 0; i < size; i++) {
           retVal[i] = rand.nextInt();
        }
        return retVal;
    }
}
