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
        int totalEncodedLength = 0;

        for (String line : lines) {
            if (line.trim().isEmpty()) continue;

            totalCodeLength += line.length();
            totalStringLength += calculateMemoryLength(line);
            totalEncodedLength += calculateEncodedLength(line);
        }

        int resultPart1 = totalCodeLength - totalStringLength;
        int resultPart2 = totalEncodedLength - totalCodeLength;

        System.out.println("Part 1 - Code length - Memory length = " + resultPart1);
        System.out.println("Part 2 - Encoded length - Code length = " + resultPart2);
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

        // Replace escape sequences
        content = content.replace("\\\\", "X");
        content = content.replace("\\\"", "X");
        content = content.replaceAll("\\\\x[0-9a-f]{2}", "X");

        return content.length();
    }

    private static int calculateEncodedLength(String str) {
        // Surrounding quotes
        int length = 2;

        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);

            if (c == '\\' || c == '"') {
                // Backslash and quotes need to be escaped
                length += 2;
            } else {
                // Normal character
                length += 1;
            }
        }

        return length;
    }
}