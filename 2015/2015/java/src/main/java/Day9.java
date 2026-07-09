import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;

class Edge {
    String from;
    String to;
    int distance;

    Edge(String from, String to, int distance) {
        this.from = from;
        this.to = to;
        this.distance = distance;
    }
}

public class Day9 {
    // Traveling salesman problem (TSP)
    //elves have provided him the distances between every pair of locations. He can start and end at any two (different) locations he wants, but he must visit each location exactly once.
    //Part One: Shortest distance
    //Part Two: Longest distance

    public static void main(String[] args) {
        System.out.println("=== Day 9: All in a Single Night - Java ===");

        List<String> lines = readInputFile("./files/fileDay9.txt");
        List<Edge> edges = new ArrayList<>();

        // Put data in edges
        for (String line : lines) {
            if (line.trim().isEmpty()) continue;

            String[] parts = line.split(" = ");
            String distanceStr = parts[1];
            String[] cities = parts[0].split(" to ");

            String from = cities[0];
            String to = cities[1];
            int distance = Integer.parseInt(distanceStr);

            edges.add(new Edge(from, to, distance));
        }

        // Get all Cities
        List<String> allCities = new ArrayList<>();
        for (Edge edge : edges) {
            if (!allCities.contains(edge.from)) allCities.add(edge.from);
            if (!allCities.contains(edge.to)) allCities.add(edge.to);
        }

        // Distance map
        Map<String, Map<String, Integer>> distances = new HashMap<>();
        for (Edge edge : edges) {
            distances.computeIfAbsent(edge.from, k -> new HashMap<>())
                    .put(edge.to, edge.distance);
            distances.computeIfAbsent(edge.to, k -> new HashMap<>())
                    .put(edge.from, edge.distance);
        }

        // Generate permutation
        List<List<String>> allRoutes = generatePermutations(allCities);

        System.out.println("Number of all possible routes: " + allRoutes.size());
        //System.out.println(allRoutes.get(0));

        // Calculate distance
        // Store distance if smaller than last time
        int minDistance = Integer.MAX_VALUE;
        int maxDistance = 0;
        List<String> fastestRoute = new ArrayList<>();
        List<String> shortestRoute = new ArrayList<>();

        for (List<String> route : allRoutes) {
            int routeDistance = 0;

            // Calculate distance between consecutive cities
            for (int i = 0; i < route.size() - 1; i++) {
                String currentCity = route.get(i);
                String nextCity = route.get(i + 1);
                int segmentDistance = distances.get(currentCity).get(nextCity);
                routeDistance += segmentDistance;
            }

            // Return to start city
           //routeDistance += distances.get(route.get(route.size() - 1)).get(route.get(0));

            if (routeDistance < minDistance) {
                minDistance = routeDistance;
                fastestRoute = new ArrayList<>(route); // Copy the route
                System.out.println("New shortest route found: " + route + " with distance: " + minDistance);
            }

            if(routeDistance > maxDistance) {
                maxDistance = routeDistance;
                shortestRoute = new ArrayList<>(route);
                System.out.println("New longest route found: " + route + " with distance: " + minDistance);
            }
        }
        System.out.println("===============");
        System.out.println("Part One: The shortest route is: " + fastestRoute + " with total distance: " + minDistance);
        System.out.println("Part Two: The longest route is: " + shortestRoute + " with total distance: " + maxDistance);
    }

    private static List<List<String>> generatePermutations(List<String> cities) {
        List<List<String>> result = new ArrayList<>();
        backtrack(cities, new ArrayList<>(), new boolean[cities.size()], result);
        return result;
    }

    private static void backtrack(List<String> cities, List<String> current, boolean[] used, List<List<String>> result) {
        if (current.size() == cities.size()) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int i = 0; i < cities.size(); i++) {
            if (!used[i]) {
                used[i] = true;
                current.add(cities.get(i));
                backtrack(cities, current, used, result);
                current.remove(current.size() - 1);
                used[i] = false;
            }
        }
    }

    private static List<String> readInputFile(String filename) {
        try {
            return Files.readAllLines(Paths.get(filename));
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            return List.of();
        }
    }
}