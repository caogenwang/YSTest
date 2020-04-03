import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;
 
public class brother_word
{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNext())
        {
            int total = scanner.nextInt();
            String[] words = new String[total];
            for (int i = 0; i < total; i++)
                words[i] = scanner.next();
            String target = scanner.next();
            int outIndex = scanner.nextInt();
 
            int count = 0;
            ArrayList<String> list = new ArrayList<>();
            for (int i = 0; i < total; i++)
            {
                if (isNeighbor(words[i], target))
                {
                    count++;
                    list.add(words[i]);
                }
            }
                System.out.println(count);
            if (count >= outIndex)
            {
                Collections.sort(list);
                System.out.println(list.get(outIndex - 1));
            }
        }
    }
 
    public static boolean isNeighbor(String str1, String str2)
    {
        if (str1.equals(str2) || str1.length() != str2.length())
            return false;
        char[] arr1 = str1.toCharArray();
        Arrays.sort(arr1);
        char[] arr2 = str2.toCharArray();
        Arrays.sort(arr2);
        if (!(String.valueOf(arr1).equals(String.valueOf(arr2))))
            return false;
        return true;
    }
}