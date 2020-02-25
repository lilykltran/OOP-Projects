//Lily Tran. 989558404. CS202 HW5.

public class CarLots //car lots contains a string, which is name of the car lot, and a binary search tree of cars
{
    protected CarBST cars;
    protected String name;

    public CarLots(String name)
    {
      cars = new CarBST();
        this.name = name;
    }
    public CarLots( String name, CarBST cars) {
        this.name = name;
        this.cars = cars;
    }
    public String get_name(){ return name; }

    public void set_name ( String data ) {
        this.name = data;

    }
}