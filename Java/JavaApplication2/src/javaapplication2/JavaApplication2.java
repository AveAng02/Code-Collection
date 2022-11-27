/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package javaapplication2;

import java.io.*;
import java.util.*;

/**
 *
 * @author AYAN ACHARYA
 */
public class JavaApplication2 {

    static boolean createBabyNameFile() throws IOException
    {
        java.io.File file = new java.io.File("babyNameFile.txt");
        if(!file.exists())
        {
            file.createNewFile();
        }
        
        return true;
    }
    
    static int nameAndGenderMatch(String str, String matchTo, String gender)
    {
        int rank = 0;
        String name1, name2;
        
        for(int i = 0; i < str.length(); i++)
        {
            if((int)str.charAt(i) - 48 < 10 && (int)str.charAt(i) - 48 > -1)
            {
                rank = (rank * 10) + ((int)str.charAt(i) - 48);
            }
            else
            {
                break;
            }
        }
        
        return rank;
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        int rank = -1;
        int year = 0;
        String gender;
        boolean flag = false;
        String str;
        
        
        Scanner inp = new Scanner(System.in);
        
        System.out.print("Enter the Year : ");
        year = inp.nextInt();
        inp.nextLine();
        System.out.print("Enter the Gender : ");
        gender = inp.nextLine();
        System.out.print("Enter the search Name : ");
        String name = inp.nextLine();
        
        
        try {
            if(createBabyNameFile())
            {
                System.out.println("File Created!");
            }
        } catch (IOException ex) {
            System.out.println("File creation failed");
        }
        
        java.io.File MyFile = new java.io.File("babyNameFile.txt");
        
        System.out.println(MyFile.canRead());
        
        try {
            Scanner sc = new Scanner(MyFile);
            
            while(sc.hasNextLine())
            {
                str = sc.nextLine();
                rank = nameAndGenderMatch(str, name, gender);
                
                if(rank > 0)
                {
                    System.out.println(name + " is ranked " + rank + " on the list.");
                    flag = true;
                    break;
                }
            }
            
            if(flag == false)
            {
                System.out.println("Name Not Found!");
            }
        } catch (FileNotFoundException ex) {
            System.out.println("Fine Not Found");
        }
        
        
    }
    
}


