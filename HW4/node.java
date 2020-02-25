//Lily Tran. 989558404. CS202 Prog 4.

public class node //Class node contains a string, which is read in from text file
{
    protected node next;
    protected String data;

    public node(String data) //constructor with arguments
    {
        this.data = data;
        next = null;
    }


    public node() //default constructor
    {
        next = null;
        this.data = null;
    }


    public node go_next()
    {
        return next;
    } //return next


    public String get_data()
    {
        return data;
    } //return data


    public int display() //displays the node data
    {
        if (data == null)
        {
            return 0;
        }

        System.out.println(data);
        return 1;
    }


    public int set_next(node to_add) //set next reference to argument passed in
    {
        next = to_add;
        return 1;
    }
}
