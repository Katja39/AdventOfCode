import java.util.*;

public class Day13 {
    public static void main(String[] args) {
        System.out.println("=== Day 13: Knights of the Dinner Table - Java ===");

        //find optimal seating arrangement
        //circular table
        //Alice would gain 54 happiness units by sitting next to Bob.
        //hamiltonian path

        List<String> lines = FileUtils.readInputFile("./files/fileDay13.txt");

        System.out.println("Part 1 and 2");

        //save
        int sum = Integer.MIN_VALUE;
        int maxSum = 0;
        Map<String, Map<String, Integer>> happiness = new HashMap<>();
        Set<String> people = new HashSet<>();

        for (String line : lines) {
            parseLine(line, happiness, people);
        }

        //---------Part 2
        String me = "Me";
        for (String person : people) {
            happiness
                    .computeIfAbsent(me, key -> new HashMap<>())
                    .put(person, 0);

            happiness
                    .computeIfAbsent(person, key -> new HashMap<>())
                    .put(me, 0);
        }
        people.add(me);
        //---------

        System.out.println(happiness);

        List<String> names = new ArrayList<>(people);

        //one person is always first
        String fixedPerson = names.get(0);
        names.remove(fixedPerson);

        List<String> currentSeating = new ArrayList<>();
        currentSeating.add(fixedPerson);
        currentSeating.addAll(names);

        List<List<String>> allSeatings = new ArrayList<>();

        permute(currentSeating, 1, allSeatings);

        for (List<String> seating : allSeatings) {
            sum = 0;

            for (int i = 0; i < seating.size(); i++) {
                String personA = seating.get(i);
                String personB = seating.get((i + 1) % seating.size());

                sum += happiness.get(personA).get(personB);
                sum += happiness.get(personB).get(personA);
            }

            if (sum > maxSum) {
                maxSum = sum;
            }
        }

        System.out.println("Last round: " +currentSeating
                +"\nSum: " + sum
                +"\nMax sum:"+ maxSum);
    }

    static void parseLine(
            String line,
            Map<String, Map<String, Integer>> happiness,
            Set<String> people
    ) {
        String[] parts = line.split(" ");

        String personA = parts[0];
        String gainOrLose = parts[2];
        int value = Integer.parseInt(parts[3]);

        String personB = parts[10].replace(".", "");

        if (gainOrLose.equals("lose")) {
            value *= -1;
        }

        happiness
                .computeIfAbsent(personA, key -> new HashMap<>())
                .put(personB, value);

        people.add(personA);
        people.add(personB);
    }

    static void permute(
            List<String> currentSeating,
            int index,
            List<List<String>> allSeatings
    ) {
        if (index == currentSeating.size()) {
            allSeatings.add(new ArrayList<>(currentSeating));
            return;
        }

        for (int i = index; i < currentSeating.size(); i++) {
            Collections.swap(currentSeating, index, i);

            permute(currentSeating, index + 1, allSeatings);

            Collections.swap(currentSeating, index, i);
        }
    }
}


