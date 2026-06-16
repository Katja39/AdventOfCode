import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

//https://regexr.com/

public class Day12 {
    public static void main(String[] args) {
        System.out.println("=== Day 12: JSAbacusFramework.io - Java ===");

        List<String> lines = FileUtils.readInputFile("./files/fileDay12.txt");

        int sum = 0;

        Pattern pattern = Pattern.compile("-?\\d+[^^]"); //-?\d+

        for (String line : lines) {
            Matcher matcher = pattern.matcher(line);

            while (matcher.find()) {
                int number = Integer.parseInt(matcher.group());
                sum += number;
            }
        }

        System.out.println("Sum of all numbers: " + sum);
    }
}


