//Lily Tran. 989558404. CS202 Prog 4.

public abstract class Feature
{
    protected LLL options; //class Feature contains a LLL of options

    public Feature() //constructor
    {
        options = new LLL();
    }


    public void add_option(String to_add)
    {
        options.add_string(to_add);
    }


    public void display()
    {
        System.out.print(name());
        System.out.println(": "); //dynamic binding
        options.display();
        System.out.println(" ");
    }


    public void display_match(String feature)
    {
        if (match(feature))
        {
            System.out.print(name());
            System.out.println(": "); //dynamic binding
            options.display(); //call display function
            System.out.println(" ");
        }

    }


    public void display_features() //just displays the feature names
    {
        System.out.print(name());
        System.out.println();
    }


    protected abstract String name(); //used in extended classes


    public abstract boolean match(String compare); //implemented in extended classes
}
