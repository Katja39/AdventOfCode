public class Runner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("No Java day specified.");
            return;
        }

        switch (args[0]) {
            case "Day8":
                Day8.main(new String[0]);
                break;

            case "Day9":
                Day9.main(new String[0]);
                break;

            case "Day10":
                Day10.main(new String[0]);
                break;

            case "Day11":
                Day11.main(new String[0]);
                break;

            case "Day12":
                Day12.main(new String[0]);
                break;

            case "Day13":
                Day13.main(new String[0]);
                break;

            default:
                System.err.println("Unknown Java day: " + args[0]);
                break;
        }
    }
}