// Important notices for the A2 template:
//A. The group will need to use this template to work on the Assignment 2 (A2)
//B. Not allowed to change the overall structure of the template including adding additional functions or remove any existing functions
//C. Except - adding new funtions are allowed only if it is for decorations or input validation purposes;
//D. Need to fill in the codes including the parts indicated with numbers and its descriptions
//E. Extra decorations can be included without interfering the provided structure
//F. You will need to define and use the parameters accordingly (including its datatype) as described below:
//   P1 = two dimensional array (n rows and 4 columns) to store user details (user_details)
//	 P2 = two dimensional array (n rows and 6 columns) to store favourite(s) list
//   P3 = two dimensional array (n rows and 3 columns) to store merchandise details
//   P4 = parameter to store number of registered user(s) (num_users)
//   P5 = parameter to store number of favourite(s) in the list
//   P6 = parameter to store total credit in the account
//   P7 = parameter to store number of merchandise
//   *Hint: P1, P2 and P3 can be string
//G. Please rename the parameters properly instead of using P1, P2, P3......
//   Else, marks will be deducted.
//H. The programme is designed with three sections and each section can be executed separately without affected
//   by other sections.Comment out other sections if it is not related while working individually.
//I. At the end, COMPULSORY to combine all the sections together as a complete executable program before submission.
//J. TIPS: Make use of getline() and also cin.ignore/infile.ignore()

//Only these libraries (or mentioned in the lecture slides or practical) are allowed to be defined and used
//Libraries such as #include <array>, #include <vector>, function enum, pointer (*) or others are not allowed
//Please refer to the A2.doc for further descriptions
//EXCEPTION: However, libraries for decoration purposes (e.g., #include <ctime>) are allowed.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

// libraries for decoration and input validation purposes
#include <cctype>

using namespace std;

#define SIZE 100 //global definition to determine the size of all the array in A2
string currentUser = "Sunny Ling Ling Ling"; //global definition with default value to determine the current user

//1. Define the FUNCTION PROTOTYPE for all the listed functions

// functions for decoration or input validation purposes

int cinInt() {
	string output;
	while (true) {
		int non_digit_count = 0;
		cin >> output;
		for(int i = 0; i<output.length(); i++){
			if(!isdigit(output[i])){
				non_digit_count++;
			}
		}
		if(non_digit_count == 0){
			return stoi(output);
		}
		cout << "Please enter an integer value.";
	}
	
}
double cinDouble() {
	string output;
	while (true) {
		int non_digit_count = 0, decimal_count = 0;
		cin >> output;
		for(int i = 0; i<output.length(); i++){
			if(!isdigit(output[i])){
				if(output[i] == '.' && decimal_count == 0){
					decimal_count++;
					continue;
				}
				non_digit_count++;
			}
		}
		if(non_digit_count == 0){
			return stoi(output);
		}
		cout << "Please enter an integer value.";
	}
}
string cinString() {

}

int loadUserInfo(string[][4]);
void registerNewUser(string[][4], int);
int login(string[][4], int);

void loadPurchaseInfo(string[][3], double&, int&);

int main() {

	//2. Define and initialise all the necessary variables

	int choice, contRL, choose, sel, cont1, sel1, cont2, cont, result; // **added result
	string user_details[SIZE][4]; //p1
	string merch_details[SIZE][3]; //p3
	int num_users = 0; //p4

	//--------------------- Start of Member 1 --------------------------------
	//3. User Module to handle new registration and login
	do {
		//"cls" stand for clear screen which refreshes the screen, placing the cursor on original place
		//For more information, refer to https://www.quora.com/What-is-system-CLS-for-in-c++
		system("cls");

		//4. Function call loadUserInfo to read the registered users' details from "userInfo.txt"
		//The function return number of registered user(s) in the record
		num_users = loadUserInfo(user_details);

		//MAIN MENU: To ask whether user want to register or login
		cout << "1. Register New User" << endl;
		cout << "2. Login" << endl;
		cout << "3. Quit" << endl;
		cout << "Choice: ";

		//User will key in and select one of the functions available
		//However, current input is accepting random value from the user without evaluation 
		//An evaluation should be carried out to ensure user only able to select 1 or 2 or 3
		//Additional marks will be awarded to those who are able to check on the input other than numbers 
		//such as "abc" or "1abc"
		//Tips: isdigit and stoi can be used. If you are using stoi with dev c++, you may face c++ 11 problem 
		//and please refer to https://stackoverflow.com/questions/13613295/how-can-i-compile-c11-code-with-orwell-dev-c
		cin >> choice;
		cin.ignore();
	
		if (choice == 1) {
			//5. Function call registerNewUser to register new user
			registerNewUser(user_details, num_users);
				
			cout << "Do you want to continue register/login? (1-yes, 2-no): ";
			cin >> contRL;
	
			if (contRL == 2)
				return 0;
		}
		else if (choice == 2) {

			//6. Function call login by returning a value for the if...else statement to handle possible conditions:
			//a. if username and password are correct
			//b. if username is correct but password is not correct
			//c. if username is not correct but password is correct
			//d. if username and password are not correct
			//Prompt back to the "MAIN MENU" if meet with condition b, c and d
			//Proceed to next stage (favourite or merchandise) if succefully login
			//NOTE: set the global variable "currentUser" to the username that successfully login 
			result = login(user_details, num_users);
			switch(result){
				case -1: // wrong password
					cout << "Username or Password incorrect!" << endl;
					break;
				case -2: // wrong username
					cout << "Username or Password incorrect!" << endl;
					cout << "If you have not registered, please register first!" << endl;
					break;
				case -3: // both wrong
					cout << "If you have not registered, please register first!" << endl;
					break;
				default: // successfully logged in
					currentUser = user_details[result][2];
			}
		}
		else return 0;
		
	} while (contRL == 1);

	cout << "END";
	//--------------------- End of Member 1 --------------------------------
	/*
	//--------------------- Start of Member 2 or Member 3 --------------------------------
	do {//do...while iteration is implemented to repeat the selection menu as below
		system("cls");

		//7. Indicate name if user able to login
		cout << "Name: " <<  << endl;

		//Menu to handle favourite list or purchase merchandise
		cout << "~~Welcome to NextFlip~~" << endl;
		cout << "A. Favourite List" << endl;
		cout << "B. Purchase Merchandise" << endl;
		cout << "C. Exit" << endl;
		cout << "Choice: ";
		cin >> choose;
		system("cls");

		//--------------------- Start of Member 2 --------------------------------
		//8. if user choose favourite list
		if () {
			do {
				system("cls");

				//9. Function call loadFavInfo to read favourite(s) from "XXX MDInfo.txt"
				//   XXX is refer to the name of current user
				//   The function will return a value indicating whether any favorites exist in the file (empty)


				//Menu for user to select display, add or delete favourite
				cout << "1. Display Favourite List" << endl;
				cout << "2. Add Favourite List" << endl;
				cout << "3. Delete Favourite List" << endl;
				cout << "4. Back" << endl;
				cout << "Select: ";
				cin >> sel;

				//cin.ignore() is to ignore or clear one or more characters from the input buffer
				//For more information, refer to https://www.tutorialspoint.com/what-is-the-use-of-cin-ignore-in-cplusplus
				cin.ignore();

				//10. A message will pop out to remind user no favourite in the list if 1 or 3 is selected
				

				//11. if...else is implemented to select the function according to the user input
				if (sel == 1)
					//Function call displayFavList to display all the favourite(s)

				else if (sel == 2)
					//Function call addFavList to add favourite 

				else if (sel == 3)
					//Function call deleteFavList to delete favourite
					
				else break; //Break the loop
				
			}while (cont1 == 1);
		}
		//--------------------- End of Member 2 --------------------------------
		//--------------------- Start of Member 3 --------------------------------
		//12. if user choose purchase merchandise
		else if () {
			system("cls");

			do {
				//13. Function call loadPurchaseInfo to load merchandise details from "XXX PurInfo.txt"
				//    XXX is refer to the name of current user


				system("cls");

				//Menu to choose add credit/merchandise or make payment
				cout << "1. Add Credit/Merchandise" << endl;
				cout << "2. Make Payment" << endl;
				cout << "3. Back" << endl;
				cout << "Choice: ";
				cin >> sel1;

				//14. if...else is implemented to select the function according to the user input
				if (sel1 == 1) 
					//Function call addItem to add credit or merchandise to the account

				else if (sel1 == 2)
					//Function call payment to make payment for the merchandise

				else 
					//Break the loop
				
			} while (cont2 == 1);
		}
		//--------------------- End of Member 3 --------------------------------
		else return 0;

	} while (cont == 1);
	//--------------------- End of Member 2 or Member 3 --------------------------------*/
	return 0;
}

//--------------------- Start of Member 1 --------------------------------
//15. Function loadUserInfo --> read all the registered users' details from "userInfo.txt"
//    and store the data into the respective parameters
//    Hint:
//    1) P1 is a two dimensional array with row and column ([][4])
//    2) Row is depends on the number of users
//    3) Columns is to store name, email, username and password
//    4) The function will return the total number of registered user in the file
//    5) Create "userInfo.txt" if it doesn't exist yet
int loadUserInfo(string user_details[][4]) {

	int count = 0;
	string line;
	
	ifstream userFile("userinfo.txt");
	if (userFile.is_open()){
		while ( getline(userFile,line) ) 
		{ 
			user_details[count/4][count%4] = line;
			count++;
		} 
		userFile.close();
	} else {
		ofstream userFile("userInfo.txt");
		userFile.close();
	}
	
	return ((count/4)+1);
}

//16. Function registerNewUser --> To register new user and save it to "userInfo.txt"
//    *P4 should be a reference parameter
//    Things to do:
//    1) Check whether the format of email is correct or not; E.g. @ must exists in the email
//    2) Check whether the password is at least 8 characters (1 symbol, 1 uppercase letter, 1 number)
//    3) Check whether the name, email or username exist in the list. 
//       E.g., "Sunny Ling Ling Ling" is already exist in the list, hence new user is not allowed to register
//       using the same name.
void registerNewUser(string user_details[][4], int num_users) {
	string name, email, username, password;
	int cont = 2;
	do {
		cout << "Name: ";
		getline(cin, name);
		while(true){
			cout << "Email: ";
			cin >> email;
			if(email.find('@') != string::npos)
				break;
			cout << "Please key in the correct email!";
		}

		cout << "Username: ";
		getline(cin, username);
		while (true) {
			cout << "Password (At least 8 characters (1 symbol, 1 uppercase letter, 1 number)): ";
			getline(cin, password);
			if (password.length() < 8) {
				cout << "Password must be at least 8 characters!" << endl;
			} else {
				int symbol_count = 0, uppercase_count = 0, number_count = 0;
								for(char c : password){
					if(isdigit(c)){
						number_count++;
					} else if (ispunct(c)){
						symbol_count++;
					} else if (isupper(c)){
						uppercase_count++;
					}
				}
				if(symbol_count == 0 || uppercase_count == 0 || number_count == 0){
					cout << "Password must have at least 1[] symbol, 1 uppercase letter, and 1 number.";
				} else {
					break;
				}
			}
		}

		cout << "Confirm registration? (1-yes, 2-no): ";
		cin >> cont;
		if(cont == 1){
			ofstream userFile;
			userFile.open("userInfo.txt", ios_base::app);
			userFile << name << "\n" << email << "\n" << username << "\n" << password << "\n";
			userFile.close();
		}
	} while (cont != 1);
	
	return;
}

//17. Function login --> For user to login with the registered username and password
//    Hint:
//    The function will return a value to indicate login success or login fail   
int login(string user_details[][4], int num_users) {
	string username, password;

	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);

	for(int i=0; i<num_users; i++) {
		if(user_details[i][2] == username) {
			if(user_details[i][3] == password) return i; // return the index if both correct
			else return -1; // incorrect password
		}
	}

	for(int j=0; j<num_users; j++) {
		if(user_details[j][3] == password) {
			return -2; // incorrect username
		}
	}

	return -3; // both not found
}

//--------------------- End of Member 1 --------------------------------

//--------------------- Start of Member 2 --------------------------------
//18. Function loadFavInfo --> read the favourites saved in "XXX MDInfo.txt"
//    Hints:
//    1) P2 is two dimensional array with rows and columns ([][6])
//    2) Row is depends on the number of users
//    3) Columns is to store category, title, year, language, description and rating
//    4) P5 is a reference parameter
//    5) The function will check whether any favorites exist in the file (it can be empty)
//       Return a value to indicate whether it is empty
//    6) Create a new text file (using ofstream) for current login user if the text file does not exist
//       E.g., you will need to create a text file named "John Lee Wei Kok MDInfo.txt" for John Lee Wei Kok 
//       since the text file does not exist. It might be the user register but did not add favourite or the user is 
//       a new user without any record
//    7) A global variable named "currentUser" is defined before function prototype
//       "currentUser" stores the username that successfully login and can be used to create the new text file 
//    8) If the text file exists, read the records. E.g., "Sunny Ling Ling Ling MDInfo.txt" is available and 
//       the details are read and load into the respective parameters
int loadFavInfo(P2, P5){

}

//19. Function addFavList --> add favourite to the list
//    Hints:
//    1) P5 is a reference parameter
//    2) Update the text file ("XXX MDInfo.txt") after add favourite
void addFavList(P2, P5){

}

//20. Function displayFavList --> display all the favourites store in the text file ("XXX MDInfo.txt")
//    Hints: A message pop out when there is no favourite in the list
void displayFavList(P2, P5) {

}

//21. Function deleteFavList --> delete selected favourite in the list
//    Hints: 
//    1) P5 is a reference parameter
//    2) Update the text file ("XXX MDInfo.txt") after delete favourite 
void deleteFavList(P2, P5) {

}

//--------------------- End of Member 2 --------------------------------

//--------------------- Start of Member 3 --------------------------------
//18. Function loadPurchaseInfo --> read the credit and merchandises saved in "XXX PurInfo.txt"
//    Hints:
//    1) P3 is two dimensional array with rows and columns ([][3])
//    2) Row is depends on the number of users
//    3) Columns is to store name of merchandise, quantity and price (per piece)
//    4) P6 and P7 are reference parameters
//    5) Create a new text file (using ofstream) for current login user if the text file does not exist
//       E.g., you will need to create a text file named "John Lee Wei Kok PurInfo.txt" for John Lee Wei Kok 
//       since the text file does not exist. It might be the user register but did not add credit or add merchandise 
//       or the user is a new user without any record
//    6) If the text file is created for the first time, credit 0 might need to add into the text file (without the merchandise)
//    7) A global variable named "currentUser" is defined before function prototype
//       "currentUser" stores the username that successfully login and can be used to create the new text file 
//    8) If the text file exists, read the records. E.g., "Sunny Ling Ling Ling PurInfo.txt" is available and 
//       the details are read and load into the respective parameters
void loadPurchaseInfo(string merch_details[][3], double& total_credit, int& num_merch) {
	string line;
	int count = -1;
	ifstream in_user_merch(currentUser +" PurInfo.txt");
	if (in_user_merch.is_open()){
		while (getline(in_user_merch, line)){
			
			if (count == -1){
				total_credit = stod(line);
			}
			else{
				merch_details[count/3][count%3] = line;
			}
			count++;
		}
		in_user_merch.close();
	} else {
		ofstream out_user_merch(currentUser +" PurInfo.txt");
		out_user_merch << "0" << endl;
		out_user_merch.close();
	}
}

//19. Function addItem --> add credit or add merchandise and saved to "XXX PurInfo.txt"
//    Things to do:
//    1) A menu for user to choose whether to add credit or merchandise
//    2) Update the "XXX PurInfo.txt" after add credit 
//    3) Update the "XXX PurInfo.txt" after add merchandise
//    *P6 and P7 are reference parameters
//    *It will be better to display the credit value all the time on the screen when it is in add section
//    *It will be better to list out all merchandise when add merchandise
//    *Can refer to the example shown in the doc file
void addItem(string merch_details[][3], double& total_credit, int& num_merch) {
	int choice, cont1 = 1,cont2 = 1, confirm;
	double temp_credit;
	do {
		system("cls");
		cout << fixed << setprecision(2);
		cout << "Current Credit: RM " << total_credit << endl;
		cout << "1. Add Credit" << endl;
		cout << "2. Add Merchandise" << endl;
		cout << "3. Back" << endl;
		cout << "Choice: ";
		cin >> choice;
		system("cls");
		switch(choice){
			case 1:
				cout << "Current Credit: RM " << total_credit << endl;
				cout << "Credit to Add: RM " << endl;
				cin >> temp_credit;
				cout << "Confirm? (1-yes, 2-no): ";
				cin >> confirm;
				if (confirm == 1) {
					total_credit = temp_credit;
					cont1 = 1;
				}
				break;
			case 2:
				for (int i=0; i<SIZE; i++) {
					cout << "~Item " << i+1 << "~" << endl;
					cout << "Name: " << merch_details[i][0] << endl;
					cout << "Quantity: " << merch_details[i][1] << endl;
					cout << fixed << setprecision(2) << "Price (per piece): RM " << merch_details[i][2] << "\n" << endl;
				}
				do {
					cout << "~Add Merchandise~" << endl;
					cout << "Name: ";
				
					ofstream userPurFile(currentUser +" PurInfo.txt", ios_base::app);
						userPurFile << 
				} while (cont2 == 1);

			case 3:
				cont = 0;
				break;
			default:
				//error checking
		}

		
	} while (cont == 1);
}

//20. Function payment --> make payment for the merchandise
//    Things to do:
//    1) Show available credit and also all the merchandise in the list
//    2) Display the total price of the merchandise (sum of all merchandise)
//    3) If user confirm payment, it is required to check whether sufficient credit to pay
//    4) A message pop out to stop the payment if insufficient credit
//    5) Proceed if sufficient credit
//    6) Print a receipt for the payment (can refer to the sample receipt given)
//    7) Update the deducted credit in "XXX PurInfo.txt"
//    8) Merchandise list should be cleared in "XXX PurInfo.txt" if payment is successfully made
//    9) A message pop out if there is no merchandise in the list
//    *P6 and P7 are reference parameters
//    Tips: stoi and stod can be used. If you are using stoi with dev c++, you may face c++ 11 problem 
//    and please refer to https://stackoverflow.com/questions/13613295/how-can-i-compile-c11-code-with-orwell-dev-c
void payment(P3, P6, P7) {
	
}

//21. Function printReceipt --> print the receipt of purchase for the merchandise "XXX Receipt.txt"
//    A sample is given as reference; do feel free to design your own receipt
void printReceipt(P3, P6, P7) {

}

//--------------------- End of Member 3 --------------------------------
