import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public final class FileUtils {
    private FileUtils() {}

    public static List<String> readInputFile(String filename) {
        try {
            return Files.readAllLines(Paths.get(filename));
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            return List.of();
        }
    }
}
