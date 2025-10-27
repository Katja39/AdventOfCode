import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class Day8 {
    public static void main(String[] args) {
        System.out.println("=== Day 8: Matchsticks ===");

        List<String> lines = readInputFile("files/fileDay8.txt");

        int totalCodeLength = 0;
        int totalStringLength = 0;

        for (String line : lines) {
            if (line.trim().isEmpty()) continue;

            totalCodeLength += line.length();
            totalStringLength += calculateMemoryLength(line);
        }

        int result = totalCodeLength - totalStringLength;
        System.out.println("Code length - Memory length = " + result);
    }

    private static List<String> readInputFile(String filename) {
        try {
            return Files.readAllLines(Paths.get(filename));
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            return List.of();
        }
    }

    private static int calculateMemoryLength(String str) {
        // Remove quotes
        String content = str.substring(1, str.length() - 1);

        // Replace escape
        content = content.replace("\\\\", "X");
        content = content.replace("\\\"", "X");
        content = content.replaceAll("\\\\x[0-9a-f]{2}", "X");

        return content.length();
    }
}