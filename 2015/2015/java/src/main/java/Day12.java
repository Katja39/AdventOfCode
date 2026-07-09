import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

//https://regexr.com/
//https://github.com/google/gson

public class Day12 {
    public static void main(String[] args) {
        System.out.println("=== Day 12: JSAbacusFramework.io - Java ===");

        List<String> lines = FileUtils.readInputFile("./files/fileDay12.txt");

        System.out.println("Part 1");

        int sum = 0;

        Pattern pattern = Pattern.compile("-?\\d+"); //-?\d+

        for (String line : lines) {
            Matcher matcher = pattern.matcher(line);

            while (matcher.find()) {
                int number = Integer.parseInt(matcher.group());
                sum += number;
            }
        }

        System.out.println("Sum of all numbers: " + sum);

        //----------------------------------------;

        System.out.println("Part 2");

        int sum2 = 0;

        for (String line: lines){
            JsonElement jsonElement = JsonParser.parseString(line);
            sum2 += sum(jsonElement);
        }

        System.out.println("Sum of all numbers without red: " + sum2);

    }
    public static int sum(JsonElement element)
    {
        // element is number
        if (element.isJsonPrimitive() && element.getAsJsonPrimitive().isNumber()) {
            return element.getAsInt();
        }

        // element is array
        if (element.isJsonArray()) {
            int summe = 0;
            JsonArray array = element.getAsJsonArray();

            for (JsonElement child : array) {
                summe += sum(child);
            }
            return summe;
        }

        // element is object
        if (element.isJsonObject()) {
            JsonObject obj = element.getAsJsonObject();

            //check if object contains "red"
            for (Map.Entry<String, JsonElement> entry : obj.entrySet())
            {
                if (entry.getValue().isJsonPrimitive()&&entry.getValue().getAsJsonPrimitive().isString()&&entry.getValue().getAsString().equals("red"))
                {
                    return 0;
                }
            }

            // if "red" wasn't found, sum all
            int sum2 = 0;
            for (Map.Entry<String, JsonElement> entry : obj.entrySet()) {
                sum2 += sum(entry.getValue());
            }
            return sum2;
        }

        return 0;
    }
}




