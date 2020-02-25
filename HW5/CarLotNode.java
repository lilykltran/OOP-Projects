public class CarLotNode
{
    protected CarLotNode left;
    protected CarLotNode right;
    protected CarLots data;

    public CarLotNode(CarLots data)
    {
        this.data = data;
        left = null;
        right = null;
    }

    public CarLotNode go_left(){ return left; }

    public CarLotNode go_right(){ return right; }

    public CarLots get_data(){ return data; }

    public String get_name() { return data.get_name(); }

    public int set_left(CarLotNode to_add) //set next reference to argument passed in
    {
        left = to_add;
        return 1;
    }

    public int set_right(CarLotNode to_add)
    {
        right = to_add;
        return 1;
    }
}
