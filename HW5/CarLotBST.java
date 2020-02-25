//Lily Tran. 989558404. CS202 HW5.

public class CarLotBST //class CarLotBst contains a carlotnode root pointer
{
    protected CarLotNode root;

    public CarLotBST() {root = null;} //constructor

    public void add_carlot(CarLots add) //wrapper add function
    {
        this.root = add_carlot(root, add);
    }

    protected CarLotNode add_carlot(CarLotNode root, CarLots add) //recurisve add car lot function to BST
    {
            if ( root == null)
            {
                root = new CarLotNode(add);
                return root;
            }
            if ( add.get_name().compareTo(root.get_name())< 0) //if data being added root data, add to left
                    root.set_left(add_carlot(root.go_left(), add));
            else
                root.set_right(add_carlot(root.go_right(), add)); //else, add to right
            return root;
    }

    public void display() //wrapper for display
    {
       display(root);
    }

    protected void display(CarLotNode root) //recursive display function
    {
        if (root == null) return;

        display(root.go_left());
        System.out.println(root.get_name());
        display(root.go_right());
    }
}
