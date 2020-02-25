//Lily Tran. 989558404. CS202 HW5.

public class CarNode //carnode contains a string, which is the car name
{
    protected CarNode left;
    protected CarNode right;
    protected String data;

    public CarNode(String data)
    {
        this.data = data;
        left = null;
        right = null;
    }

    public CarNode go_left(){ return left; }

    public CarNode go_right(){ return right; }

    public String get_data(){ return data;}

    //public String get_name() { return data.get_name(); }

    public int set_left(CarNode to_add) //set next reference to argument passed in
    {
        left = to_add;
        return 1;
    }

    public int set_right(CarNode to_add)
    {
        right = to_add;
        return 1;
    }
}
