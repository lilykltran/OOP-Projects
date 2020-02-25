//Lily Tran. 989558404. CS202 Prog 4.

public class LLL //class LLL contains a head and tail pointer to class node
{
    protected node head;
    protected node tail;

    public LLL() //constructor
    {
        head = null;
        tail = null;
    }


    public LLL(final LLL to_copy) //copy constructor
    {
        copy(head, to_copy.head); //call copy function
    }


    protected int copy(node dest, node source) //recursive copy function
    {
        if (source == null)
        {
            dest = null;
            return 0;
        }

        dest = new node(source.get_data());
        return copy(dest.go_next(), source.go_next());
    }


    public int add_string(String options) //adds a feature option to the LLL
    {
        if (options == null)
            return 0;

        node temp = new node(options);

        if (head == null) //Adds at head if list empty
        {
            head = tail = temp;
            tail.set_next(null);
            return 1;
        }

        else //if list is not empty
        {
            tail.set_next(temp);
            tail = tail.go_next();
            tail.set_next(null);
            return 1;
        }
    }


    public int display()  //displays list
    {

        if (head == null)
            return 0;

        node current = head;

        while (current != null) {

            current.display();

            current = current.go_next();
        }
        return 1;
    }
}
