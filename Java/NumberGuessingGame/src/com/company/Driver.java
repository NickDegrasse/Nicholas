/*
Number guessing game
Nicholas deGrasse
Version 1
10/22/2018
 */
package com.company;

import java.util.Random;
import java.util.Scanner;

public class Driver {
    public static int userPoints = 25;
    public static int allowedAttempts = 5;


    public static void main(String[] args) {

        while (true) {
            System.out.println("Enter choice (h)elp, (p)lay, (c)onfigure, (r)eport, (q)uit" );
            Scanner reader = new Scanner(System.in);                                         //Take in user input
            char choice = reader.next().charAt(0);                                           //Checks for character
            switch (choice) {
                case 'h':
                    helpMenu(); //Displays help menu
                    break;

                case 'c':
                    allowedAttempts = configure(reader);    //Adjusts how many attempts are allowed
                    break;

                case 'p':
                    play(reader);   //Starts the game
                    break;

                case 'r':
                    report();   //Reports total score
                    break;

                case 'q':
                    quit(); //exits the game
                    break;

                default:
                    invalidInput();  //Handles extraneous cases
                    break;
            }

        }
    }
    /*
    Configure will adjust the number of possible attempts based on a random passphrase that is entered. It will allow
    between 3 and 7 attempts based on the ascii conversion of the passphrase the user chooses
     */
    public static int configure(Scanner reader) {
        System.out.println("Please enter a passphrase");
        String passphrase = reader.next();

        int denominator = 0;
        int sum = 0;
        int ascii = 0;

        for(int i = 0; i < passphrase.length(); i++) {
            denominator++;

            ascii = (int)passphrase.charAt(i);

            sum = sum + ascii;
        }

        int average = sum / denominator;

        int remainder = average % 5;

        return remainder + 3;




    }
    public static void play(Scanner reader) {
        do {
            int computerChosenNumber = chooseRandomNumber();
            /*
             * For testing purposes:
             * System.out.println("Computer chose " + computerChosenNumber + " you have " + allowedAttempts + " guesses");
            */
            int attempts = playSession(reader, computerChosenNumber, allowedAttempts);
            int pointsScored = pointsScored(attempts, allowedAttempts);
            if (pointsScored < 0) {
                attempts--;
            }
            System.out.println("Allowed attempts: " + allowedAttempts + " Attempts taken: " + attempts + " Old Score: " + userPoints + " Points earned = " + pointsScored + " New Score: " + (userPoints + pointsScored));
            userPoints += pointsScored;
        } while (playAgain(reader) == true);

        System.out.println("Thank you for playing");

    }
    public static void helpMenu() {
        System.out.println("******************************************************************************");
        System.out.println("Welcome to UW CSS 142 Point Machine.");
        System.out.println("This machine choses a number between 1-100 at random. You need to guess the number");
        System.out.println("You (i.e the user) will have fixed number of attempts to guess the number.");
        System.out.println("f you guess it correct, you will earn points based on the number of attempts taken.");
        System.out.println("If you cannot guess it, you will lose points");
        System.out.println("To proceed, please select one of the choice from ");
        System.out.println("(h)elp , (p)lay, (c)onfigure, (r)eport, (q)uit)");
        System.out.println("******************************************************************************");
    }
    public static void report() {
        System.out.println("Your current score is " + userPoints + " points");

    }
    public static void quit() {
        System.out.println("Thank you for checking out our game, we hope you liked it. Please provide us with feedback");
        System.exit(0);


    }
    public static void invalidInput() {
        System.out.println("Invalid choice. Accepted values are (h)elp , (p)lay, (c)onfigure, (r)eport, (q)uit");

    }
    public static int chooseRandomNumber() {
        Random r = new Random();
        int computerChosenNumber = r.nextInt(100);
        return computerChosenNumber;

    }
    /*
    This is the gameplay session. It will take in user guesses, then output messages letting the user know if their
    tens or ones place number guess is too large or too small
     */
    public static int playSession(Scanner reader, int computerChosenNumber, int allowedAttempts) {
        int attempts = 0;
        int userGuess;


        do {
            System.out.println("Guess a number");
            userGuess = reader.nextInt();
            int userOnes = userGuess % 10;
            int userTens = userGuess / 10;
            int compOnes = computerChosenNumber % 10;
            int compTens = computerChosenNumber / 10;

            if (userGuess == computerChosenNumber) {
                attempts++;
                System.out.println("Correct!");
                break;
            }
            else {
                attempts++;
            }
            if (userOnes > compOnes) {
                System.out.println("Your units guess is too high");
            }
            else if (userOnes < compOnes) {
                System.out.println("Your units guess is too low");
            }
            else if (userOnes == compOnes) {
                System.out.println("Your units guess of " + userOnes + " is correct");
            }
            if (userTens > compTens) {
                System.out.println("Your tens guess is too high");
            }
            else if (userTens < compTens) {
                System.out.println("Your tens guess is too low");
            }
            else if (userTens == compTens) {
                System.out.println("Your tens guess of " + userTens + " is correct");
            }


        } while (userGuess != computerChosenNumber && allowedAttempts > attempts);
        //This if statement makes sure there isn't an issue when the user guesses wrong. Otherwise attempts == allowedAttempts
        //whether they guess right on their last attempt or not, and messes up pointsScored() method
        if (userGuess != computerChosenNumber) {
            attempts++;
        }

        return attempts;

    }
    public static int pointsScored(int attempts, int allowedAttempts) {
        int pointsScored;
        if (allowedAttempts >= attempts) {
            pointsScored = 7 + (7 - allowedAttempts) - attempts + 1;
            return pointsScored;
        }
        else {
            pointsScored = -1 - ((7 - allowedAttempts) * 2);
            return pointsScored;
        }

    }
    public static boolean playAgain(Scanner reader) {
        boolean x = true;
        if (userPoints > 0) {
            System.out.println("Your current score is " + userPoints + " points. Would you like to play again? (y)es or (n)o");
            String response = reader.next();
            switch(response.toUpperCase().charAt(0)) {
                case 'Y': x = true;
                        break;

                case 'N': x = false;
                        break;

                default: System.out.println("Please select (y)es or (n)o");
                    playAgain(reader);
            }

        }


        else if (userPoints <= 0){
            System.out.println("Your points have fallen to zero, Thank you for playing!");
            quit();
        }
        return x;
    }
}
