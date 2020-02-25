//Lily Tran. 989558404. CS202 Prog 4.

public class Color extends Feature {

    public Color() { super(); } //invoke base constructor


    protected String name()
    {
        return "Color";
    }


    public boolean match(String compare) //compare passed in feature to Color feature
    {
        return name().equals(compare);
    }

}
