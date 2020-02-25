//Lily Tran. 989558404. CS202 Prog 4.

public class Engine extends Feature
{
    public Engine() { super(); } //invoke base constructor


    protected String name()
    {
        return "Engine";
    }


    public boolean match(String compare) //compare passed in feature to Engine feature
    {
        return name().equals(compare);
    }
}
