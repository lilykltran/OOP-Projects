//Lily Tran. 989558404. CS202 Prog 5.

public class Wheel extends Feature
{
    public Wheel() { super(); } //invoke base constructor


    protected String name()
    {
        return "Wheel";
    }


    public boolean match(String compare) //compare passed in feature to wheel feature
    {
        return name().equals(compare);
    }
}
