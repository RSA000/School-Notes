### Rustic Rewards + Admin README

#### Video Demo: https://www.youtube.com/watch?v=C7YBOz5r3tA

#### Inspiration/tutorial videos I used
    * https://www.youtube.com/watch?v=6b2WAePdiqA - Firebase auth and Firestore tutorial
    * https://www.youtube.com/watch?v=-cYLkXKNDJA&t=493s - Firebase auth and Firestore tutorial with storyboard
    * https://www.youtube.com/watch?v=l7obVQObdRM&t=225s - Another login tutorial and how I learned to make background with shapes.
    * https://firebase.google.com/docs/ - Firebase docs
    

##### About

Rustic Rewards and Rustic Admin is my CS50 final project and hopefully one day, a real app! 

I currently work at a Pizzeria called The Rustic Crust and thought it would be a fun final project to make a rewards points system that I could one day deploy for real. Currently, my apps has these features:

#### For The User App
    * A functioning login/database using Firebase. Both apps access information from the same database and use Firebase auth and Firestore to do so.

    * A points systems. Users can show a QR code to the cashier and redeem/earn points depending on their purchase. Redemptions can only occur if user has enough points.

    * A history system. Users can view all their current available points, total points earned, and total points redeemed.

    * A logout button

    * RegisterView for registering. User is redirected to login when registration works

    
#### For The Admin/Employee Side

    * The ability to add or remove points from a user by scanning a QR code.

    * App can differentiate normal users from employees

    * Can determine if scanned QR code is a real user or not


#### Running

The apps can be run by using Xcode. Open Xcode and select rusti_rewards_4.xcodeproj or rustic_admin.xcodeproj to open Rustic Rewards or Rustic Admin.

Firebase auth and Firebase Firestore are both required to be able to run these.

For user login - auth
For database - Firestore

By default the database has three tables, User_Pizza_Data, users, and employees

If you would like to use your own database you could sign up with firebase and follow the instructions to creating a project and replace the GoogleServive-info file in both apps.


## Specifics
-----

#### Rustic Rewards -


##### Content View
* ContentView is the first screen the user sees. It is the login/signup screen. If the user inputs the correct credentials, they will be logged in. The user can also  go to the signup RegisterView by pressing on the signup button.
* Var body checks if admin is logged in and will bring the user to pizzaview if they are.
* If the user is not logged in, content is loaded which is the sign in screen.
* User email is stored in USER_ID if signed in.

##### RegisterView
* Allows user to sign up. Passwords must match for account to be created.

##### DataManager
* Deals with interacting with Firebase database. 
* FetchPizzas gets all the users pizza data and counts points
* Is used in ListView and PointsView

##### Pizza
* A struct used for getting pizza data from Firebase.

##### MainmenView
* MainmenView is the main navigation menu for the app
* The navigation view allows the user to go to ListView or Points View.
* Logout button logs user out and returns them to ContentView

##### PointsView
* Displays user QR code which is their email.
    * returnData is used for this. It grabs USER_ID and converts it to a qr uiimage
* Displays points earned, available points, and redeemed points using DataManager. 




#### Rustic Admin
 * The Rustic Admin app allows employees to scan users QR codes and add or remove points

##### ContentView
* The login function checks if the email provided is in the "employees" database and then check if login credentials are correct

##### pizzaView

* View allowing employee to add or remove points by scanning QR code.
* A counter is shown on screen. If gaining points, points are incremented in 1's
* If user is redeeming points it increments in 10's so 1 point would mean 10 points redeemed
* Counter cannot go below 0
* User cannot add or remove points unless a QR has been scanned

##### DataManager

* Differs from DataManager in Rustic Rewards, this datamanager grabs available points and has addPoints and redeemPoints functions which adds to the User_Pizza_Data.
---- 

## Databases

User_Pizza_Data - contains user email, points, redeemed, and date.

employees - Contains employee emails

users - contains user emails. Used for checking if user exists when scanning QR code
