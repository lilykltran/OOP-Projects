//Lily Tran. 989558404. CS202 HW5.

public class CarBST //class carBst contains a carnode root pointer
{
    protected CarNode root;

    public CarBST()
    {
        this.root =null;
    }

    public void add_car(String add) //wrapper for add car
    {
        this.root = add_car(root, add);
    }

    protected CarNode add_car(CarNode root, String add) //recursive add car function
    {
        if ( root == null)
        {
            root = new CarNode(add); //new node
            return root;
        }
        if ( add.compareTo(root.get_data())< 0) //if data being added is less than root, add to left
            root.set_left(add_car(root.go_left(), add));
        else
            root.set_right(add_car(root.go_right(), add)); //else, add to right
        return root;
    }

    public void display() //wrapper display
    {
        display(root);
    }

    protected void display(CarNode root) //recursive display
    {
        if (root == null) return;

        display(root.go_left());
        System.out.println(root.get_data());
        display(root.go_right());
    }
}
