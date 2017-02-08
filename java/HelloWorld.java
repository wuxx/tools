import java.lang.reflect.Constructor;
import java.lang.reflect.Type;

public class HelloWorld
{
    public static void main0(String args[])
    {
        System.out.println("Hello World!");
    }

    public static void main1(String[] args) throws Exception{
        /**第一个例子了解Class类型的定义*/
        String str1 = "abc";//字符串1
        String str2 = "abcd";//字符串2
        //三种方式获取Class类型
        Class cls1 = str1.getClass();
        Class cls2 = str2.getClass();
        Class cls3 = String.class;
        Class cls4 = Class.forName("java.lang.String");
        System.out.println(cls1);//打印字符串1类型
        System.out.println(cls2);//打印字符串2类型
        System.out.println(cls3);
        System.out.println(cls4);
        System.out.println(cls1 == cls2);//字符串1和字符串2的类型是否相等
        System.out.println(cls1 == cls3);

        //总之只要在源程序中出现的类型，都有各自的Class实例对象
        System.out.println(cls1.isPrimitive());//是不是原始类型(同样也有类似的方法判断是不是枚举，数组等类型)
        System.out.println(int.class.isPrimitive());
        System.out.println(int.class == Integer.class);//int类型和Integer类型是不一样的，一个是基本类型，一个是对象类型
        System.out.println(int.class == Integer.TYPE);//8中数据基本类型都对应与其对象类型中的TYPE字段
        System.out.println(int[].class.isPrimitive());//数组类型不是原始类型，数组是一个对象类型即int[]是一个Object
    }

    public static void main(String args[]) throws Exception{
        /**获取String对象指定的构造方法(通过方法的参数类型,传递参数的Class对象)*/
        Constructor constructor = String.class.getConstructor(StringBuffer.class);//得到String对象的一个参数是StringBuffer的构造方法
        String str = (String) constructor.newInstance(new StringBuffer("abc"));//生成对象String，当然要传递一个StringBuffer参数
        System.out.println(str);//打印值
        /**总结:这种方法是要传递参数类型和参数的值，getConstructor(...)方法的参数是一个可变参数，因为构造方法可能有多个参数*/

        /**获取String默认的构造方法生成String对象*/
        String str1 = String.class.newInstance();

        /**获取String对象的所有构造方法,并将构造方法的参数类型打印出来*/
        Constructor[] constructors = Class.forName("java.lang.String").getConstructors();
        for(int i=0;i<constructors.length;i++){
            Type[] type = constructors[i].getGenericParameterTypes();
            for(int j=0;j<type.length;j++)
                System.out.print(type[j]+",");
            System.out.println();
        }
    }
}
