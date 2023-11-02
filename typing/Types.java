public class Types
{
  public static void main(String [] args) {
    int x;
    double y;
    char c;
    
    System.out.println(1+1.0);

    x = 7;
    y = x;
    System.out.println(y);

    // type narrowing requires explicit cast
    y = 1.5;
    x = (int)y;
    System.out.println(x);

    x = 65;
    c = (char)x;
    System.out.println(c);

    System.out.println("1" + 1);
  }
}