//Lily Tran. 989558404. CS202 HW5.

public class Car //class car contains a linear linked list of features and a name, which is name of car
{
    protected LLL features;
    String name;

    Car(String name)
    {
        features = new LLL();
        this.name = name;
    }
    public void add_feature(String add)
    {
        features.add_string(add);
    }
}
