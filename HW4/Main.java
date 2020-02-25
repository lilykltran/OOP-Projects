//Lily Tran. 989558404. CS202 Prog 4. This is the main class, where all the function calls are made.

import java.io.*;
import java.util.Scanner;

public class Main {

    private static final String FILENAME = "src/features"; //set to file name
    private static Feature[]features = new Feature[3]; //create array of features

    public static void read()
    {
        features[0] = new Color(); //index 1 is color
        features[1] = new Engine(); //2 is engine
        features[2] = new Wheel(); //3 is wheel

        BufferedReader br = null;
        FileReader fr = null;

        try
        {
            fr = new FileReader(FILENAME); //open the file
            br = new BufferedReader(fr); //read in the file

            String sCurrentLine;

            for (int i = 0; i < 3; ++i)
            {
                sCurrentLine = br.readLine(); //read in each line. each line is a new feature

                if (sCurrentLine != null)
                {
                    String [] temp = sCurrentLine.split("[|]"); //the delimiter | is a new option
                    for(String item : temp)
                    {
                        features[i].add_option(item); //add options to the array
                    }
                }
            }
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
    }

    public static void main(String[] args) {

        read(); //call read function

        int ans = 0;

        Scanner input = null;
        input = new Scanner(System.in);

        do {

            System.out.print("Enter a command. 1.Display features available, 2.See a feature's options," +
                    " 3. Choose a feature option, 4.Quit");
            System.out.println();
            ans = input.nextInt();
            input.nextLine();

            if (ans == 1) {

                for (int i = 0; i < 3; ++ i)
                    features[i].display_features(); //call display features function
            }

            else if (ans == 2) {

                String tempFeature;
                System.out.print("Enter a feature.");
                tempFeature = input.nextLine();
                tempFeature = tempFeature.substring(0, 1).toUpperCase() + tempFeature.substring(1); //capitalize first letter

                for (Feature feature : features)
                    feature.display_match(tempFeature); //display options based on the feature
            }

            else if (ans == 3) {

                String [] car = new String[3]; //create an array to store the user's feature options
                System.out.println("Enter 3 options to add to your car starting with Color, Engine, and then Wheel.");

                for (int i = 0; i < 3; ++i)
                    car[i] = input.nextLine();

                System.out.println();
                System.out.println("Your car currently has: ");
                for (int i = 0 ; i< 3; ++i)
                    System.out.println(car[i]);


                System.out.println();
                System.out.println("Stay tuned! Your car will be built soon..."); //prog 5 will compare these options to real cars!
            }

        } while (ans != 4);
    }
}