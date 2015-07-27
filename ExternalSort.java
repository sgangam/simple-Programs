//package externalSort;

import java.io.*;
import java.util.*;

/**
 *
 * @author Sriharsha Gangam
 */
public class ExternalSort {
    private static final String INPUT = "input.txt";
    private static final String OUTPUT = "output.txt";
    private static final String SIMPLE_OUTPUT = "simple_output.txt";
    private static final String ENV_PATH = "/Users/sgangam/IdeaProjects/temp/externalSort";
    private static final long COUNT = 10000000;
    private static final boolean CREATE_INPUT = false;
    private static final long BATCH = 1000000; // a batch of input
    private static final String PARTS = "parts";
    private static final String PREFIX = "file";
    private static final int FILE_MERGE_LIMIT = 30;

    private final String envPath;
    private final long count;

    private final String simpleOutputPath;

    private String inputPath;
    private String outputPath;
    private String partsPath;

    public ExternalSort(String envPath, long count) {
        this.envPath = envPath;
        this.count = count;
        this.partsPath = this.envPath + File.separator + PARTS;
        this.inputPath = this.envPath + File.separator + INPUT;
        this.simpleOutputPath = this.envPath + File.separator + SIMPLE_OUTPUT;
        this.outputPath = this.envPath + File.separator + OUTPUT;
    }

    public static void main(String[] args) throws IOException {

        ExternalSort externalSort = new ExternalSort(ENV_PATH, COUNT);
        externalSort.createFolderEnv();
        if (CREATE_INPUT) {
            externalSort.createInputFile();
        }
        //externalSort.sortSimple();
        externalSort.sortExternal();

    }

    private void sortExternal() throws IOException {
        createPartFiles();
        mergePartFiles(this.partsPath, this.outputPath);
    }

    private void mergePartFiles(String partsPath, String outputPath) throws IOException {
        File partsDir = new File(partsPath);
        File[] files = partsDir.listFiles();
        List<BufferedReader> readerList = getBufferedReaders(files);
        List<BufferedReader> currentList = new ArrayList<BufferedReader>(readerList);

        File outFile = new File(outputPath);
        FileOutputStream fos = new FileOutputStream(outFile);
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(fos));


        Map<BufferedReader, List<Long>> map = new HashMap<BufferedReader, List<Long>>();
        for (BufferedReader br : readerList) {
            map.put(br, new LinkedList<Long>());
        }

        int batchPerFile = (int) (BATCH / files.length);

        while (!currentList.isEmpty()) {
            List<BufferedReader> completedList = new ArrayList<BufferedReader>();


            for (BufferedReader br : currentList) {
                List<Long> prevContent = map.get(br);
                int newContentSize = batchPerFile - prevContent.size();
                List<Long> newContent = readListFromBufferedReader(br, newContentSize);
                prevContent.addAll(newContent);
                if (newContent.size() < newContentSize) {//EOF
                    completedList.add(br);
                }
            }

            List<Long> sortedList = getSortedListByMerge(new LinkedList<List<Long>> (map.values()));
            writeListToBufferedWriter(sortedList, writer);
            currentList.removeAll(completedList);
        }

        List<Long> sortedList = new LinkedList<Long>();
        for(List<Long> list : map.values()) {
            sortedList.addAll(list);
        }
        Collections.sort(sortedList);
        writeListToBufferedWriter(sortedList, writer);

        writer.close();
        for (BufferedReader br : readerList) {
            br.close();
        }
    }

    /**
     * Merges the individual lists. Removes the chosen smallest element.
     *
     * @param allLists
     * @return
     */
    private List<Long> getSortedListByMerge(List<List<Long>> allLists) {
        List<Long> merged = new LinkedList<Long>();

        while (true) {

            List<Long> smallest = allLists.get(0);
            if (smallest.isEmpty()) {
                return merged;
            }
            for (List<Long> list : allLists) {
                if (list.isEmpty()) {
                    return merged;
                }
                if (list.get(0) < smallest.get(0)) {
                    smallest = list;
                }
            }
            long val = smallest.get(0);
            merged.add(val);
            smallest.remove(0);
        }
    }

    private void writeListToBufferedWriter(List<Long> list, BufferedWriter bw) throws IOException {
        for (Long val : list) {
            bw.write(String.valueOf(val));
            bw.newLine();
        }
    }

    private List<BufferedReader> getBufferedReaders(File[] files) throws FileNotFoundException {
        BufferedReader[] readers = new BufferedReader[files.length];
        for (int i = 0; i < files.length; i++) {
            FileInputStream fis = new FileInputStream(files[i]);
            readers[i] = new BufferedReader(new InputStreamReader(fis));
        }
        return Arrays.asList(readers);
    }

    private void createPartFiles() throws IOException {

        File inputFile = new File(this.inputPath);
        FileInputStream fis = new FileInputStream(inputFile);
        BufferedReader br = new BufferedReader(new InputStreamReader(fis));
        long total = this.count;
        int id = 0;
        while(total > 0) {
            long batch = total > BATCH ? BATCH : total;
            List<Long> list = readListFromBufferedReader(br, batch);
            Collections.sort(list);
            writeListTofile(list, getPartFileName(id));
            total -= batch;
            id++;
        }
        br.close();
    }

    private String getPartFileName(int id) {
        return ENV_PATH + File.separator + PARTS + File.separator + PREFIX + id;
    }

    private void createFolderEnv() throws IOException {

        File dir = new File(this.partsPath);
        if (!dir.exists()) {
            dir.mkdirs();
            return;
        } 
        for (File file : dir.listFiles()) {
            if (file.getName().contains(PREFIX)) {
                file.delete();
            }
        }
    }


    private void createInputFile() throws IOException {

        File inputFile = new File(this.inputPath);
        FileOutputStream fos = new FileOutputStream(inputFile);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));

        for (long i = 0; i < this.count; i++) {
            Random rand = new Random();
            bw.write(String.valueOf(rand.nextLong()));
            bw.newLine();
        }
        bw.close();
    }

    private List<Long> readListFromFile(String fileName) throws IOException {

        File inputFile = new File(fileName);
        FileInputStream fis = new FileInputStream(inputFile);
        BufferedReader br = new BufferedReader(new InputStreamReader(fis));
        List<Long> list = readListFromBufferedReader(br, this.count);
        br.close();
        return list;
    }

    private List<Long> readListFromBufferedReader(BufferedReader br, long count) throws IOException {

        List<Long> list = new LinkedList<Long>();
        for (long i = 0; i < count; i++) {
            String line = br.readLine();
            if (line == null) {//EOF
                return list;
            }
            long val = Long.parseLong(line);
            list.add(val);
        }
        return list;
    }

    private void writeListTofile(List<Long> list, String outPath) throws IOException {

        File outFile = new File(outPath);
        FileOutputStream fos = new FileOutputStream(outFile);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));
        writeListToBufferedWriter(list, bw);
        bw.close();
    }

    private void sortSimple() throws IOException {
        List<Long> list = readListFromFile(this.inputPath);
        Collections.sort(list);
        writeListTofile(list, this.simpleOutputPath);
    }

}
