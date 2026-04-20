// ============================================================
//                     NEXTFLIP - Group 16
// C++ application that allows users to:
//   1. Register / Login
//   2. Manage a personal Favourite Drama/Movie list
//   3. Purchase merchandise using stored credit
// Data is stored in text files:
//   - userInfo.txt          : all registered users
//   - <user> MDInfo.txt     : favourites for each user
//   - <user> PurInfo.txt    : credit + merchandise for each user
//   - <user> Receipt.txt    : generated payment receipt
// ============================================================

// Libraries required for the program
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

// Libraries for decoration and input validation purposes
#include <cctype>
#include <ctime>
#include <sstream>

using namespace std;

#define SIZE 100 // Global definition to determine the size of all the array
string currentUser = "Sunny Ling Ling Ling"; // Global definition with default value to determine the current user

// Functions for decoration or input validation purposes
string formatCurrency(double); // Formats a double to a "X.XX" string (e.g. 12.5 -> "12.50")
int cinInt(string); // Prompts user for input and validate it as a whole integer
string cinPrice(string); // Prompts user for input and validate it as a price (up to 2 d.p.)
void printBanner(string); // Prints header banner with timestamp

// FUNCTION PROTOTYPES

// Member 1:
int loadUserInfo(string[][4]); // Reads all users from userInfo.txt into a two-dimensional array
void registerNewUser(string[][4], int); // Collects new user details and appends to "userInfo.txt"
int login(string[][4], int); // User logins... returns row index on success or negative error code

// Member 2:
int loadFavInfo(string[][6], int&); // Reads current user's favourites from "<user> MDInfo.txt"
void addFavList(string[][6], int&); // Appends a new favourite entry to the file
void displayFavList(string[][6], int&); // Prints all favourite entries
void deleteFavList(string[][6], int&); // Removes a chosen entry and rewrites the file

// Member 3:
void loadPurchaseInfo(string[][3], double&, int&); // Reads credit balance and merchandise from "<user> PurInfo.txt"
void addItem(string[][3], double&, int&); // Top up credit or add a merchandise item
void payment(string[][3], double&, int&); // Makes payment that deducts total merchandise cost from credit balance
void printReceipt(string[][3], double&, int&); // Writes a formatted receipt to "<user> Receipt.txt"

int main() {

	// Define and initialise all the necessary variables
	int choice = 0, contRL = 1, sel = 0, cont1 = 1, sel1 = 0, cont2 = 1, cont = 1, result = 0, favExist;
	string choose;

	string user_details[SIZE][4]; // Two dimensional array to store user details 
	// row: [name, email, username, password]
	string favList[SIZE][6]; // Two dimensional array to store favourite(s) list 
	// row: [category, title, year, language, description, rating]
	string merch_details[SIZE][3]; // Two dimensional array to store merchandise details
	// row: [name, quantity, price]
	int num_users = 0; // Number of registered user(s)
	int numFav = 0; // Number of favourite(s) in the list
	double total_credit = 0.0; // Total credit in current user account
	int num_merch = 0; // Number of merchandise in current user account

	do { // Login / Register loop

		system("cls");

		num_users = loadUserInfo(user_details); // Reload user data at the start of each loop

		printBanner("User Login");

		while (true) { // While true loop for user to input valid choice (1, 2, or 3)
			choice = cinInt("\n----------------------------\n| > 1.   Register New User |\n| > 2.               Login |\n| > 3.                Quit |\n----------------------------\n\n[ Choice ]: ");

			if (choice >= 1 && choice <= 3) break;
			cout << "Please select an option (1, 2, 3)." << endl;
		}

		if (choice == 1) {
			// Function call registerNewUser to register new user
			registerNewUser(user_details, num_users);

			while (true) {
				contRL = cinInt("Do you want to continue register/login? (1-yes, 2-no): ");

				if (contRL == 1 || contRL == 2) break;
				cout << "Please select an option (1, 2)." << endl;
			}
		}
		else if (choice == 2) {
			// User login... result holds the user's row index or a negative error code
			result = login(user_details, num_users);
			switch (result) {
				case -1: // Incorrect password
					cout << "Username or Password incorrect!" << endl;
					break;
				case -2: // Invalid username
					cout << "Username or Password incorrect!" << endl;
					cout << "If you have not registered, please register first!" << endl;
					break;
				case -3: // Users that haven't registered into the system
					cout << "Username or Password incorrect!" << endl;
					cout << "If you have not registered, please register first!" << endl;
					break;
				default: // Successful login
					cout << "Successfully logged in!" << endl;
					currentUser = user_details[result][2]; // Store the matched username globally
					contRL = 2; // For loop breaking purposes
			}
			system("PAUSE");
		}
		else if (choice == 3) return 0; // User chooses to quit at the login screen 

	} while (contRL == 1);

	do { // Selection menu looping after successful login
		while (true) {

			// Indicate name if user able to login
			system("cls");
			printBanner(currentUser + " : Main Menu");

			//Menu to handle favourite list or purchase merchandise
			cout << "----------------------------" << endl;
			cout << "| A.        Favourite List |" << endl;
			cout << "| B.  Purchase Merchandise |" << endl;
			cout << "| C.                  Exit |" << endl;
			cout << "----------------------------" << endl << endl;
			cout << "[ Choice ]: ";

			getline(cin, choose);
			for (char& x : choose) x = tolower(x); // Change user's choice input to lowercase
			
			if (choose == "a" || choose == "b" || choose == "c") break;

			cout << " Please enter valid inputs (a, b, c)" << endl;
		}
		system("cls");

		// If user chooses favourite list
		if (choose == "a") {
			cont1 = 1;
			do {
				system("cls");
				printBanner(currentUser + " : Favourites");

				// Function call loadFavInfo to read favourite(s) from "XXX MDInfo.txt"
				favExist = loadFavInfo(favList, numFav);

				// Menu for user to select display, add or delete favourite
				while (true) {
					sel = cinInt("\n-------------------------------\n| > 1. Display Favourite List |\n| > 2. Add Favourite List     |\n| > 3. Delete Favourite List  |\n| > 4. Back                   |\n-------------------------------\n\n[ Choice ]: ");
					if (sel >= 1 && sel <= 4) break;
					cout << "Please select an available option (1, 2, 3, 4)." << endl;
				}
				// A message will pop out to remind user no favourite is in the list if 1 or 3 is selected
				if (favExist == 0 && (sel == 1 || sel == 3)) {
					cout << "No favourite list is found for " << currentUser << endl;
					system("PAUSE");
					continue; // Skip to next iteration and reload the menu
				}

				// Select the function according to the user input
				if (sel == 1)
					//Function call displayFavList to display all the favourite(s)
					displayFavList(favList, numFav);
				else if (sel == 2)
					//Function call addFavList to add favourite 
					addFavList(favList, numFav);
				else if (sel == 3)
					//Function call deleteFavList to delete favourite
					deleteFavList(favList, numFav);
				else cont1 = 0; //Break the loop

			} while (cont1 == 1);
		}

		// If user chooses to purchase merchandise
		else if (choose == "b") {
			system("cls");
			
			cont2 = 1;
			do {
				// Load merchandise details from "<user> PurInfo.txt"
				loadPurchaseInfo(merch_details, total_credit, num_merch);

				system("cls");
				printBanner(currentUser + " : Purchase");

				//Menu to choose add credit/merchandise or make payment
				while (true) {
					sel1 = cinInt("\n-------------------------------\n| > 1. Add Credit/Merchandise |\n| > 2. Make Payment           |\n| > 3. Back                   |\n-------------------------------\n\n[ Choice ]: ");
					if (sel1 >= 1 && sel1 <= 3) break;
					cout << "Please select an available option (1, 2, 3)." << endl;
				}
				
				if (sel1 == 1) // Selects the function according to the user input
					addItem(merch_details, total_credit, num_merch); // Add credit or merchandise to the account
				else if (sel1 == 2)
					payment(merch_details, total_credit, num_merch); // Make payment for the merchandise
				else
					cont2 = 2; // Break the loop
			} while (cont2 == 1);
		}
		else return 0; // Option "c": exit the purchase loop

	} while (cont == 1); // Loop until user chooses to exit

	return 0;
}

// Functions for decoration or error checking purposes:

// Converts a double to a "X.YY" string with exactly 2 decimal places, where X = the whole number, and Y = the cents
// Example: 12.5 -> "12.50"
string formatCurrency(double num) {
	int whole_num = static_cast<int>(num);
	int two_dp = static_cast<int>((num - whole_num) * 100);

	return (to_string(whole_num) + "." + (two_dp < 10 ? "0" : "") + to_string(two_dp));
}

// Prompts the user with 'message', reads user input
// Rejects it if any character is non-digit. 
int cinInt(string message) {
	string output;
	while (true) { // Loops until a valid whole number is entered.
		int non_digit_count = 0;
		cout << message;
		getline(cin, output);
		for (int i = 0; i < output.length(); i++) {
			if (!isdigit(output[i])) {
				non_digit_count++;
			}
		}
		if (non_digit_count == 0) {
			return stoi(output);
		}
		cout << "Please enter an integer value." << endl;
	}

}

// Prompts the user with 'message', reads user input as a monetary value
// Accepts digits and at most one decimal point with up to 2 decimal places.
// Returns the value formatted to 2 d.p. as a string (e.g. "9.90").
string cinPrice(string message) {
	string output;
	while (true) {
		int non_digit_count = 0, decimal_count = 0, decimal_place = 0;
		cout << message;
		getline (cin, output);
		for (int i = 0; i < output.length(); i++) {
			if (!isdigit(output[i])) {
				if (output[i] == '.' && decimal_count == 0) {
					decimal_count++;
					continue;
				}
				non_digit_count++; // Any other non-digit character makes the input invalid
			}
			else if (decimal_count == 1) {
				decimal_place++; // Count decimal places after the decimal point
			}
		}
		if (non_digit_count == 0 && decimal_place <= 2) {
			return formatCurrency(stod(output)); // Return as a standardised 2 d.p. string
		}
		cout << "Please enter a valid price range within 2 decimal places." << endl;
	}
}

// Load User Interface with timestamp with 'message' being the current menu the user is in
void printBanner(string message) {

	time_t now = std::time(nullptr);
	tm local_tm;
	localtime_s(&local_tm, &now); // to get timestamp
	tm* local = &local_tm;

	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "|                                                                              |" << endl;
	cout << "|                               N E X T F L I P                                |" << endl;
	cout << "|                                  Group 16                                    |" << endl;
	cout << "| "<< fixed << left << setw(50) << message << " Time: " << put_time(local, "%Y-%m-%d %H:%M:%S") << " |" << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;
}
// ============================================================
// MEMBER 1
// ============================================================
// Read all the registered users' details from "userInfo.txt"
int loadUserInfo(string user_details[][4]) {

	int count = 0;
	string line;

	ifstream userFile("userInfo.txt");
	if (userFile.is_open()) { 
		while (getline(userFile, line))
		{
			// Each user occupies 4 lines of credentials: name, email, username, and password
			// (count / 4) represents the user, (count % 4) represents the lines of credential
			user_details[count / 4][count % 4] = line;
			count++;
		}
		userFile.close();
	}
	else {
		ofstream userFile("userInfo.txt"); // Creates a new empty file 
		userFile.close();
	}

	return (count / 4); // Total registered users
}

// Collects all 4 credentials from the user and validates each of them and then appends to "userInfo.txt"
// Sets the global currentUser to the new username to allow newly registered user to be logged in
void registerNewUser(string user_details[][4], int num_users) {
	string name, email, username, password;
	bool exist;
	int cont = 2;
	do {
		while (true) {

			cout << "\nName: ";
			getline(cin, name);
				
			while (true) {
				cout << "Email: ";
				getline(cin, email);

				if (email.find('@') != string::npos) // Checks if email contains '@'
					break;
				cout << "Please key in the correct email!" << endl;
			}

			cout << "Username: ";
			getline(cin, username);
			exist = false;
			// Checks uniqueness for all 4 credentials
			for (int i = 0; i < num_users; i++) {
				if (user_details[i][0] == name) {
					cout << "Please enter a different name." << endl;
					exist = true; break;
				}
				else if (user_details[i][1] == email) {
					cout << "Please enter a different email." << endl;
					exist = true; break;
				}
				else if (user_details[i][2] == username) {
					cout << "Please enter a different username." << endl;
					exist = true; break;
				}
			}
			if (!exist) break; // All credentials are unique
		}
		
		// Password must be >= 8 characters and contain at least 1 digit, 1 symbol, and 1 uppercase letter
		while (true) {
			cout << "Password (At least 8 characters (1 symbol, 1 uppercase letter, 1 number)): ";
			getline(cin, password);
			if (password.length() < 8) {
				cout << "Password must be at least 8 characters!" << endl;
			}
			else {
				int symbol_count = 0, uppercase_count = 0, number_count = 0;
				for (char c : password) {
					if (isdigit(c)) number_count++;
					
					else if (ispunct(c)) symbol_count++;
					
					else if (isupper(c)) uppercase_count++;
				}
				if (symbol_count == 0 || uppercase_count == 0 || number_count == 0) {
					cout << "Password must have at least 1 symbol, 1 uppercase letter, and 1 number.";
				}
				else break;
			}
		}
		while (true) {
			cont = cinInt("\nConfirm registration? (1-yes, 2-no): ");

			if (cont == 1 || cont == 2) break;
			cout << "Please enter a valid option (1 for yes, 2 for no)." << endl;
		}

		if (cont == 1) {
			// Append validated new user's details into "userInfo.txt"
			ofstream userFile;
			userFile.open("userInfo.txt", ios_base::app);
			userFile << name << "\n" << email << "\n" << username << "\n" << password << "\n";
			userFile.close();
		}
	} while (cont != 1); // Restart when user chooses not to confirm registration

	currentUser = username; // Update the global session variable so newly registered user can directly log in
}

// Searches user_details for a matching username + password pair.
int login(string user_details[][4], int num_users) {
	string username, password;
	
	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);
	
	// Look for matching username
	for (int i = 0; i < num_users; i++) {
		if (user_details[i][2] == username) {
			if (user_details[i][3] == password) return i;// Return index if both correct
			else return -1; // Incorrect password
		}
	}
	// Look for duplicate password
	for (int j = 0; j < num_users; j++) {
		if (user_details[j][3] == password) {
			return -2; // Invalid username
		}
	}

	return -3; // No match at all
}

// ============================================================
// MEMBER 2
// ============================================================
// Reads "<currentUser> MDInfo.txt" line-by-line into favList[][6].
int loadFavInfo(string favList[][6], int& numFav) {

	int count = 0;
	string line;

	ifstream favFile(currentUser + " MDInfo.txt");
	if (favFile.is_open()) {
		while (getline(favFile, line))
		{
			// Each entry occupies 6 lines: category, title, year, language, description, rating.
			// (count / 6) represents the favourite's number, (count % 6) represents the lines of entry
			favList[count / 6][count % 6] = line;
			count++;
		}
		favFile.close();
		if (count == 0) return 0; // File exists but has no content
	}
	else {
		ofstream favFile(currentUser + " MDInfo.txt"); // Creates an empty text file
		favFile.close();
	}
	numFav = (count / 6);
	return (numFav == 0 ? 0 : 1); // Returns 1 if at least one entry exists, 0 if the file is empty or missing.
}

// Prompts the user to enter details for a new favourite entry, year and rating has to be validated
// Append all 6 details of favourites to "<currentUser> MDInfo.txt" after validation
void addFavList(string favList[][6], int& numFav) {
	string category, title, language, description, year, rating;
	int confirmation;
	bool valid_year;


	cout << "\nAdd New Favourite Drama or Movie:" << endl;
	cout << "Category: ";
	getline(cin, category);
	cout << "Title: ";
	getline(cin, title);
	while(true){
		cout << "Year: ";
		getline(cin, year);

		// Validate year (digits only, 1-4 characters, and value between 1-2026)
		if (year.length() <= 4 && year.length() >= 1) {
			valid_year = true;
			for (char c : year) {
				if (!isdigit(c)) {
					valid_year = false;
					break;
				}
			}
			if (valid_year)
				if (stoi(year) > 0 && stoi(year) <= 2026) break;
		}
		cout << "Please enter a valid year (between Year 0 and Year 2026)." << endl;
	}
	cout << "Language: ";
	getline(cin, language);
	cout << "Description: ";
	getline(cin, description);

	// Validate rating (numeric, up to 2 d.p., and value between 0 and 10)
	while (true) {
		cout << "Rating: ";
		getline(cin, rating);

		int decimal_count = 0, non_digit_count = 0, decimal_place = 0;
		for (int i = 0; i < rating.length(); i++) {
			if (!isdigit(rating[i])) {
				if (rating[i] == '.' && decimal_count == 0) {
					decimal_count++;
					continue;
				}
				non_digit_count++;
			}
			else if (decimal_count == 1) {
				decimal_place++;
			}
		}
		if (non_digit_count == 0 && decimal_place <= 2) {
			if (stod(rating) > 0 && stod(rating) <= 10) break;
		}
		cout << "Please enter a valid decimal rating between 0 and 10 (up to 2 decimal places)." << endl;
	}

	while (true) {
		confirmation = cinInt("Confirm add? (1-yes, 2-no): ");

		if (confirmation == 1 || confirmation == 2) break;
		cout << "Please select an option (1, 2)." << endl;
	}

	if (confirmation == 1) { // Appends the details
		ofstream favFile(currentUser + " MDInfo.txt", ios_base::app);
		favFile << category << "\n" << title << '\n' << year << '\n' << language << '\n' << description << '\n' << rating << "\n";
		favFile.close();

		numFav++;
	}
}

// Prints all favourite entries for the current user
void displayFavList(string favList[][6], int& numFav) {
	cout << "========================================" << endl;
	cout << "    " << currentUser << "'s Favourites" << endl;
	cout << "========================================" << endl;

	for (int i = 0; i < numFav; i++) {
		cout << "\n----------------------------------------" << endl;
		cout << "    Entry " << (i + 1) << endl;
		cout << "----------------------------------------" << endl;
		cout << "Category:" << favList[i][0] << endl;
		cout << "Title:" << favList[i][1] << endl;
		cout << "Year:" << favList[i][2] << endl;
		cout << "Language:" << favList[i][3] << endl;
		cout << "Description:" << favList[i][4] << endl;
		cout << "Rating:" << favList[i][5] << endl;
	}
	system("PAUSE");
}

// Displays all entries, prompts the user to choose one by number
// After choosing, rewrites the file excluding the selected entry
void deleteFavList(string favList[][6], int& numFav) {
	cout << endl << currentUser << "'s Favourites" << endl;
	// Display all entries of favourites
	for (int i = 0; i < numFav; i++) {
		cout << "\n==================================" << endl;
		cout << "    Entry:" << (i + 1) << endl;
		cout << "==================================" << endl;
		cout << "Category:" << favList[i][0] << endl;
		cout << "Title:" << favList[i][1] << endl;
		cout << "Year:" << favList[i][2] << endl;
		cout << "Language:" << favList[i][3] << endl;
		cout << "Description:" << favList[i][4] << endl;
		cout << "Rating:" << favList[i][5] << endl;

	}

	int option, confirm;
	while (true) {
		option = cinInt("Enter the number of the favourite to delete (0 to cancel)");
		if (option == 0) {
			cout << "Delete cancelled" << endl;
			return;
		}
		if (option >= 1 && option <= numFav) break;
		cout << "Please enter a valid entry number (between 1 and " << numFav << ", or 0 to cancel)." << endl;
	}
	
	while (true) {
		confirm = cinInt("Are you sure you want to delete the favourite? (1 - yes, 2- no)");
		if (confirm == 1 || confirm == 2) break;
		cout << "Please enter a valid option (1 for yes, 2 for no)." << endl;
	}

	if (confirm == 1) {
		// Overwrite the file excluding the selected favourite to delete
		ofstream favFile(currentUser + " MDInfo.txt");
		for (int i = 0; i < numFav; i++) {
			if (i == (option - 1)) continue;
			favFile << favList[i][0] << "\n" << favList[i][1] << "\n" << favList[i][2] << "\n" << favList[i][3] << "\n" << favList[i][4] << "\n" << favList[i][5] << "\n";
		}
		favFile.close();
		numFav--;
		cout << "Favourite " << option << ". " << favList[option][1] << " deleted!" << endl;
		system("PAUSE");
	}
}

// ============================================================
// MEMBER 3
// ============================================================
// Reads "<currentUser> PurInfo.txt" 
void loadPurchaseInfo(string merch_details[][3], double& total_credit, int& num_merch) {
	string line;
	int count = -1; // Written as -1 so that the first line (index 0) is treated as the credit balance
	ifstream in_user_merch(currentUser + " PurInfo.txt");
	if (in_user_merch.is_open()) {
		while (getline(in_user_merch, line)) {

			if (count == -1) {
				total_credit = stod(line); // Holds the account's credit balance
			}
			else {
				// Each merch occupies 3 lines: name, quantity, and price
				// (count / 3) represents the merch number, (count % 3) represents the lines of merch details
				merch_details[count / 3][count % 3] = line;
			}
			count++;
		}
		in_user_merch.close();
	}
	else {
		ofstream out_user_merch(currentUser + " PurInfo.txt"); // Create empty text file if file is missing
		out_user_merch << "0" << endl; // First line is the initial credit of 0
		out_user_merch.close();
	}
	num_merch = count / 3;
}

// Secondary menu with two options:
// 1. Add Credit – validates a positive amount, then updates the balance in the file.
// 2. Add Merchandise – collects name, quantity, and price, then appends to the file.
void addItem(string merch_details[][3], double& total_credit, int& num_merch) {
	int choice, cont = 1, affirm = 2, confirm, quantity;
	string name, temp_credit, price;
	do {
		system("cls");
		printBanner(currentUser + " : Add Items");
		cout << fixed << setprecision(2);
		cout << "----------------------------------" << endl;
		cout << "| Current Credit: RM " << setw(12) << left << total_credit << "|" << endl;
		cout << "----------------------------------" << endl;
		cout << "| > 1.                Add Credit |" << endl;
		cout << "| > 2.           Add Merchandise |" << endl;
		cout << "| > 3.                      Back |" << endl;
		cout << "----------------------------------" << endl;
		cout << "[ Choice ]: ";
		cin >> choice;
		system("cls");

		switch (choice) {
		case 1: {
			printBanner(currentUser + " : Add Credit");
			cout << "Current Credit: RM " << total_credit << endl;
			// Ensure user enters a positive credit amount
			while (true) {
				temp_credit = cinPrice("Credit to Add: RM ");
				if (stod(temp_credit) > 0) break;
				cout << "Please enter a valid amount." << endl;
			}
			
			confirm = cinInt("Confirm? (1-yes, 2-no): ");
			if (confirm == 1) {
				total_credit += stod(temp_credit);
				cont = 1;

				// Rewrite the entire file change with the newly added credit amount
				ofstream userPurFile(currentUser + " PurInfo.txt");
				userPurFile << formatCurrency(total_credit) << endl;
				for (int i = 0; i < num_merch; i++) {
					userPurFile << merch_details[i][0] << "\n" << merch_details[i][1] << "\n" << merch_details[i][2] << endl;
				}
				userPurFile.close();
			}
			break;
		}
		case 2: {
			printBanner(currentUser + " : Add Merch");

			// Show existing to the user
			for (int i = 0; i < num_merch; i++) {
				cout << "~Item " << i + 1 << "~" << endl;
				cout << "Name: " << merch_details[i][0] << endl;
				cout << "Quantity: " << merch_details[i][1] << endl;
				cout << fixed << setprecision(2) << "Price (per piece): RM " << merch_details[i][2] << "\n" << endl;
			}
			do {
				cout << "~Add Merchandise~" << endl;
				cout << "Name: ";

				cin.ignore();
				getline(cin, name);

				quantity = cinInt("Quantity: ");
				price = cinPrice("Price (per piece): RM ");
				affirm = cinInt("Confirm? (1-yes, 2-no): ");

				if (affirm == 1) {
					// Store new item into merch_details array
					merch_details[num_merch][0] = name;
					merch_details[num_merch][1] = to_string(quantity);
					merch_details[num_merch][2] = price;
					num_merch++;

					// Append the new item's 3 lines to the file
					ofstream userPurFile(currentUser + " PurInfo.txt", ios_base::app);
					userPurFile << name << "\n" << quantity << "\n" << price << endl;
					userPurFile.close();
					break;
				}
			} while (affirm == 2);
			break;
		}
		case 3:
			return; // Go back to the purchase sub-menu
		default:
			cout << "Please enter a valid choice (1, 2, or 3)! " << endl;
		}
	} while (cont == 1);
}

// Displays all merchandise items and their combined total, asks for payment confirmation,
// then deducts the total from the user's credit balance.
// If credit is insufficient, the transaction is aborted.
// On success, the updated balance is saved and a receipt is generated.
void payment(string merch_details[][3], double& total_credit, int& num_merch) {
	double price = 0, conf = 2, remain;
	int count = 0;
	cout << "Current Credit: RM " << total_credit << endl;
	
	// Calculate the grand total across all merchandise items
	for (int i = 0; i < num_merch; i++) {
		cout << "~Item " << i + 1 << "~" << endl;
		cout << "Name: " << merch_details[i][0] << endl;
		cout << "Quantity: " << merch_details[i][1] << endl;
		cout << "Price (per piece): RM " << fixed << setprecision(2) << merch_details[i][2] << endl;
		price += stoi(merch_details[i][1]) * stod(merch_details[i][2]);
		count++;
		cout << "Total Price (All): " << endl;
	}
	// Print the expanded price breakdown (quantity * unit_price + ... = total)
	for (int j = 0; j < count; j++) {
		cout << fixed << setprecision(2) << "(" << merch_details[j][1] << " * RM " << stod(merch_details[j][2]) << ") " << (j < (count - 1) ? "+ " : "");
	}
	cout << fixed << setprecision(2) << "= RM " << price << endl;

	while (true) {
		conf = cinInt("Confirm payment? (1-yes, 2-no): ");
		if (conf == 1 || conf == 2) break;
		cout << "Please select an option (1, 2)." << endl;
	}

	if (conf == 2) return; // User cancel payment... no credit has been deducted

	remain = total_credit - price; // Calculate balance after payment

	if (total_credit < price) { // Insufficient credit
		cout << "Insufficient Credit! Please top up sufficient credit. " << endl;
		system("PAUSE");
		return;
	}
	else { 
		cout << fixed << setprecision(2);
		cout << "Available credit: " << total_credit << endl;
		cout << "Remaining credit: RM " << total_credit << " - RM " << price << " = RM " << remain << endl;

		// Clear all merch info, with the exception of the remaining credit balance after payment
		ofstream purchaseFile(currentUser + " PurInfo.txt");
		if (purchaseFile.is_open()) {
			purchaseFile << formatCurrency(remain) << endl;
			purchaseFile.close();
		}
		printReceipt(merch_details, total_credit, num_merch); // Generate receipt
		system("PAUSE");
	}
}

// Generates a formatted text receipt and saves it to "<currentUser> Receipt.txt". (Mostly decoration so there is out-of-topic functions)
void printReceipt(string merch_details[][3], double& total_credit, int& num_merch) {
	double total = 0;
	time_t now = std::time(nullptr); // Retrieves time as number of seconds passed since 1 January 1970
	tm local_tm; // Hold time information in a broken-down format
	localtime_s(&local_tm, &now); // Converts the now variable into local time
	tm* local = &local_tm; // Creates a pointer to local_tm structure

	ofstream receipt(currentUser + " Receipt.txt");
	receipt << fixed << setprecision(2);
	// Header
	receipt << "╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
	receipt << "║                               N E X T F L I P                                ║" << endl;
	receipt << "║                                  Group 16                                    ║" << endl;
	receipt << "╠══════════════════════════════════════════════════════════════════════════════╣" << endl;
	receipt << "║  Customer: " << left << setw(66) << currentUser << "║" << endl;
	receipt << "║  Timestamp: " << put_time(local, "%Y-%m-%d %H:%M:%S") << "                                              ║" << endl;
	receipt << "╠══════════════════════════════════════════════════════════════════════════════╣" << endl;
	receipt << "║                                                                              ║" << endl;
	receipt << "║  YOUR PURCHASE:                                                              ║" << endl;
	receipt << "║  ┌────────────────────────────────────────────────────────────────────────┐  ║" << endl;
	receipt << "║  │ QTY │ ITEM                                         │ PRICE   │ TOTAL   │  ║" << endl;
	receipt << "║  ├────────────────────────────────────────────────────────────────────────┤  ║" << endl;
	for (int i = 0; i < num_merch; i++) {

		total += stoi(merch_details[i][1]) * stod(merch_details[i][2]);

		// Allignment of merch details with the itemized purchase table
		receipt << "║  │" << right << setw(4) << merch_details[i][1] << " │ "
			<< left << setw(44) << merch_details[i][0].substr(0, 44) << " │ "
			<< left << setw(8) << merch_details[i][2] << "│ "
			<< left << setw(8) << fixed << setprecision(2) << (stoi(merch_details[i][1]) * stod(merch_details[i][2])) << "│  ║" << endl;

		// If the item name exceeds 44 characters, wrap the overflow onto additional rows
		if (merch_details[i][0].length() > 44) {
			for (int j = 1; j <= merch_details[i][0].length() / 44; j++) {
				receipt << "║  │     │ " << left << setw(44) << merch_details[i][0].substr((j * 44), 44) << " │         │         │  ║" << endl;
			}
		}
	}
	receipt << "║  └────────────────────────────────────────────────────────────────────────┘  ║" << endl;
	receipt << "║                                                                              ║" << endl;
	receipt << "║  PAYMENT SUMMARY:                                                            ║" << endl;
	receipt << "║  ┌────────────────────────────────────────────────────────────────────────┐  ║" << endl;
	receipt << "║  │ Total Price: RM " << right << setw(53) << fixed << setprecision(2) << total << "  │  ║" << endl;
	receipt << "║  │ Available Credit: RM " << right << setw(48) << fixed << setprecision(2) << total_credit << "  │  ║" << endl;
	receipt << "║  │ Remaining Credit: RM " << right << setw(48) << fixed << setprecision(2) << (total_credit - total) << "  │  ║" << endl;
	receipt << "║  └────────────────────────────────────────────────────────────────────────┘  ║" << endl;
	receipt << "║                                                                              ║" << endl;
	receipt << "║  THANK YOU FOR SHOPPING WITH NEXTFLIP! :D <3                                 ║" << endl;
	receipt << "╚══════════════════════════════════════════════════════════════════════════════╝" << endl;
}