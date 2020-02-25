//Lily Tran. 989558404. CS202 Prog 5. This is the main class, where all the function calls are made.

import java.io.*;
import java.util.Scanner;

public class Main {

    private static final String FEATURES_FILE = "src/features"; //set to file name
    private static final String CARLOTS_FILE = "src/carlots"; //set to file name
    private static final String CARS_FILE = "src/cars"; //set to file name
    private static Feature[]features = new Feature[3]; //create array of features

    public static String[] read(String filename)
    {

        BufferedReader br = null;
        FileReader fr = null;

        try
        {
            fr = new FileReader(filename); //open the file
            br = new BufferedReader(fr); //read in the file

                return br.lines().toArray(String[]::new);
        }

        catch (IOException e) //catch if unsuccessful
        {
            e.printStackTrace();
        }

        finally
        {
            try
            {
                if (br != null) //close files
                    br.close();

                if (fr != null)
                    fr.close();
            }

            catch (IOException ex)
            {
                ex.printStackTrace();
            }
        }

        return null;
    }

    public static void main(String[] args) {

        features[0] = new Color(); //index 1 is color
        features[1] = new Engine(); //2 is engine
        features[2] = new Wheel(); //3 is wheel

            String sCurrentLine;
            String[]lines = read(FEATURES_FILE);

            for (int i = 0; i < 3; ++i)
            {
                sCurrentLine = lines[i]; //read in each line. each line is a new feature
                if (sCurrentLine != null)
                {
                    String [] temp = sCurrentLine.split("[|]"); //the delimiter | is a new option
                    for(String item : temp)
                    {
                        features[i].add_option(item); //add options to the array
                    }
                }
            }
        CarBST [] cars = new CarBST[3];
        lines = read(CARS_FILE);

        for (int i = 0; i < 3; ++i)
        {
            sCurrentLine = lines[i]; //read in each line. each line is a new feature
            if (sCurrentLine != null)
            {
                String [] temp = sCurrentLine.split("[|]"); //the delimiter | is a new option
                for(String item : temp)
                {
                    cars[i] = new CarBST();
                    cars[i].add_car(item); //add options to the array
                }
            }
        }
            CarLots [] carLots = new CarLots[3];
            CarLotBST bstdummy = new CarLotBST();

            lines = read(CARLOTS_FILE);

            for (int i = 0; i < 3; ++i)
            {
                sCurrentLine = lines[i]; //read in each line. each line is a new feature
                if (sCurrentLine != null)
                {
                        carLots[i] = new CarLots(lines[i], cars[i]);
                        bstdummy.add_carlot(carLots[i]);
                }
            }



        int ans = 0;
        Scanner input = null;
        input = new Scanner(System.in);

        do {

            System.out.print("Enter a command. 1.Display car lots, 2.Display cars," +
                    " 3. See feature options for the cars. 4. Choose a feature option, 5. Quit");
            System.out.println();
            ans = input.nextInt();
            input.nextLine();

            if (ans == 1) {

                bstdummy.display();
            }

            else if (ans == 2)
            {
                for (int i = 0; i < 3; ++i)
                    cars[i].display();
            }

            else if (ans == 3)
            {
                for (int i = 0; i < 3; ++ i)
                    features[i].display_features(); //call display features function

                String tempFeature;
                System.out.print("Enter a feature.");
                tempFeature = input.nextLine();
                tempFeature = tempFeature.substring(0, 1).toUpperCase() + tempFeature.substring(1); //capitalize first letter

                for (Feature feature : features)
                {
                    feature.display_match(tempFeature); //display options based on the feature
                }
            }

            else if (ans == 4) {

                String [] car = new String[3]; //create an array to store the user's feature options
                System.out.println("Enter 3 options to add to your car starting with Color, Engine, and then Wheel.");

                for (int i = 0; i < 3; ++i)
                    car[i] = input.nextLine();

                System.out.println();
                System.out.println("Your car currently has: ");
                for (int i = 0 ; i< 3; ++i)
                    System.out.println(car[i]);

                System.out.println();

                if (car[0].compareTo("black") == 0 || car[1].compareTo("combustion") ==0|| car[2].compareTo("51 Daytona") ==0)
                        System.out.println("Your car is a 1971 Ford Pinto.");

                else if (car[0].compareTo("yellow") == 0 || car[1].compareTo("straight") ==0|| car[2].compareTo("60 Smoothie") ==0)
                    System.out.println("Your car is a 2008 Jeep Wrangler.");

                else if (car[0].compareTo("green") == 0 || car[1].compareTo("vtype") ==0|| car[2].compareTo("80 White Spoke") ==0)
                    System.out.println("Your car is a 2009 Terminal Tractor.");

                else
                    System.out.println("The features you want don't match to a car.");

                System.out.println();

            }

        } while (ans != 5);
    }
}