public class Day10 {
    public static void main(String[] args) {
        System.out.println("=== Day 10: Elves Look, Elves Say - Java ===");

        String input = "1321131112";
        int iterations = 50;

        double lambdaConway = 1.303577269034269;
        int startLength = input.length();


        if(iterations>40){
        for (int i = 0; i <= iterations; i++) {
            double estimatedLength = startLength * Math.pow(lambdaConway, i);
            System.out.printf("Estimated length after %2d Iterations: %,.0f%n", i, estimatedLength);
        }
        }else{
        for (int iter = 0; iter < iterations; iter++) {
            String newInput = "";
            int numberOfSameValues = 1;

            char currentChar = input.charAt(0);

            for (int i = 1; i < input.length(); i++) {
                if (input.charAt(i) == currentChar) {
                    numberOfSameValues++;
                } else {
                    newInput = newInput + numberOfSameValues + currentChar;
                    currentChar = input.charAt(i);
                    numberOfSameValues = 1;
                }
            }

            newInput = newInput + numberOfSameValues + currentChar;
            input = newInput;

            if ((iter + 1) % 2 == 0) {
                System.out.println("Iteration " + (iter + 1) + ": Length = " + input.length());
            }
        }
        System.out.println("Length: " + input.length());
        }
    }
}
