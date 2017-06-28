import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.lang.reflect.Type;

public class Chord_God
{
/*
    1   C       1
    2   D_flat      b9
    3   D           9
    4   D_sharp     #9
    5   E       3
    6   F           11
    7   F_sharp     #11
    8   G       5
    9   A_flat      b13
    10  A           13
    11  B_flat  b7
    12  B       7

   bG bA bB bC bD bE  F bG
   bD bE  F bG bA bB  C bD
   bA bB  C bD bE  F  G bA
   bE  F  G bA bB  C  D bE
   bB  C  D bE  F  G  A bB
    F  G  A bB  C  D  E  F

    C  D  E  F  G  A  B  C
    G  A  B  C  D  E #F  G
    D  E #F  G  A  B #C  D
    A  B #C  D  E #F #G  A
    E #F #G  A  B #C #D  E
    B #C #D  E #F #G #A  B

*/

    public static void main(String args[])
    {
        HashMap map = new HashMap();
        map.put("1-3-5",        "");
        map.put("1-3-#5",       "aug");
        map.put("1-b3-5",       "min");
        map.put("1-b3-b5",      "dim");
        map.put("1-4-5",        "sus4");
        map.put("1-2-5",        "sus2");

        map.put("1-3-5-9",      "add9");
        map.put("1-3-5-11",     "add11");
        map.put("1-3-5-13",     "maj6");
        map.put("1-b3-5-13",    "min6");

        map.put("1-3-5-7",      "maj7");
        map.put("1-b3-5-b7",    "min7");
        map.put("1-3-#5-7",     "aug(maj7)");
        map.put("1-b3-b5-b7",   "min7b5");
        map.put("1-b3-5-7",     "cm(maj7)");
        map.put("1-3-5-b7",     "dom7");
        map.put("1-4-5-b7",     "dom7(sus4)");
        map.put("1-3-#5-b7",    "aug7");
        map.put("1-b3-b5-6",    "dim7");

        Set set = map.entrySet();

        for(Iterator iter = set.iterator(); iter.hasNext();)
        {
            Map.Entry entry = (Map.Entry)iter.next();

            String key = (String)entry.getKey();
            String value = (String)entry.getValue();
            System.out.println(key + " : " + value);
        }

        System.out.println("Hello World!");
    }

    public static void Get_Notes(byte[] Fretboard)
    {

    }

}
