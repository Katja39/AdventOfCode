public class Day11 {
    public static void main(String[] args) {

        // increment of old password

        //RULES
        //password 8 lowercase letters
        //at least increasing straight three letters - cde, xyz
        //no i, o or l letter
        // two different pairs of letters - bb, dd

        //example: abcdefgh -> abcdffaa

        String[] passwords = new String[] {"hxbxwxba", "", ""};

        for (int i = 0; i<passwords.length-1;i++){

        while (true) {
            passwords[i] = increment(passwords[i]);

            if (isValid(passwords[i])) {
                System.out.print("New password " + passwords[i] + "\n");
                passwords[i+1] = passwords[i];
                break;
            }
        }
    }
    }

    public static String increment(String s) {
        char[] chars = s.toCharArray();

        for (int i = chars.length - 1; i >= 0; i--) {
            if (chars[i] == 'z') {
                chars[i] = 'a';
            } else {
                chars[i]++;
                break;
            }
        }
        return new String(chars);
    }

    public static boolean isValid(String s) {
        // at least increasing straight three letters
        boolean hasStraight = false;
        for (int i = 0; i < s.length() - 2; i++) {
            if (s.charAt(i) + 1 == s.charAt(i + 1) &&
                    s.charAt(i) + 2 == s.charAt(i + 2)) {
                hasStraight = true;
                break;
            }
        }
        if (!hasStraight) return false;

        // no i, o or l letter
        if (s.contains("i") || s.contains("o") || s.contains("l")) {
            return false;
        }

        // two different pairs of letters
        int pairs = 0;
        for (int i = 0; i < s.length() - 1; i++) {
            if (s.charAt(i) == s.charAt(i + 1)) {
                pairs++;
                i++;
            }
        }
        return pairs >= 2;
    }
}
