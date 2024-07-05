## Bank Management System

### Overview

The Bank Management System is a console-based application designed to manage and automate various banking operations. This system allows users to perform essential banking functions such as creating accounts, depositing and withdrawing money, transferring funds between accounts, and managing account details. The system also includes an administrative interface for monitoring the overall state of the bank, including total funds and the number of users.

### Features

1. **Account Creation:**
   - Allows users to create new bank accounts with unique user codes and names.
   - Ensures no duplicate user codes are created to maintain data integrity.

2. **Account Inquiry:**
   - Provides detailed information about user accounts, including the account holder's name, user code, and current balance.
   
3. **Cash Deposit:**
   - Enables users to deposit money into their accounts.
   - Updates the account balance both in the system and in the associated file.

4. **Cash Withdrawal:**
   - Allows users to withdraw money from their accounts.
   - Ensures the account has sufficient funds before completing the transaction.

5. **Cash Transfer:**
   - Facilitates transferring money between different user accounts within the bank.
   - Ensures funds are transferred only to valid, existing accounts.

6. **Account Deletion:**
   - Provides functionality for users to delete their accounts.
   - Ensures accounts with a positive balance cannot be deleted until funds are either withdrawn or transferred.

7. **Account Edit:**
   - Allows users to edit their account details, such as changing their account name.

8. **Administrative Interface:**
   - An exclusive admin interface for bank administrators to view overall bank statistics.
   - Displays total money in the bank and the number of registered users.
   - Allows administrators to view detailed information about all user accounts.

9. **Data Persistence:**
   - Utilizes file handling to read and write user data, ensuring data persistence between program runs.

### Technical Details

- **Programming Language:** C++
- **Libraries Used:**
  - `<iostream>` for standard input and output.
  - `<fstream>` for file handling.
  - `<vector>` for managing dynamic arrays of users.
  - `<string>` for handling text data.
  - `<cctype>` for character handling.
  - `<cstdlib>` for utility functions.

- **Design Pattern:** Single Inheritance and Friend Functions
  - **Base Class:** `Bank`
  - **Derived Class:** `User`
  - The `User` class inherits from the `Bank` class, leveraging the features and functionalities of the base class.

### Usage

1. **Starting the Application:**
   - On launching the application, users are prompted to enter their user code.
   - Admin users can access the admin interface by entering the code "admin".

2. **Navigating the Menu:**
   - The main menu provides options to perform various banking operations.
   - Users can select options by entering the corresponding number.

3. **Admin Access:**
   - The admin interface provides a summary of the bank's status and allows detailed viewing of all accounts.

### Conclusion

The Bank Management System offers a comprehensive solution for managing basic banking operations. Its user-friendly interface, robust functionality, and data persistence capabilities make it an effective tool for both users and administrators. Whether it's creating a new account, checking balance, depositing or withdrawing money, or managing accounts, this system streamlines and simplifies the banking experience.
