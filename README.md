# OOP-Based Banking System

## Overview

This is an Object-Oriented Programming (OOP) based banking system developed in C++ that manages clients and their banking operations. It includes various banking features such as managing clients, handling transactions, user management, login tracking, currency exchange, and security measures for login attempts.

## Features

### Clients Management
- **Clients List**: View a list of all clients.
- **Add New Client**: Create a new client account.
- **Delete Client**: Remove an existing client from the system.
- **Update Client**: Modify the details of an existing client.
- **Find Client**: Search for a client by name or ID.

### Transactions
- **Deposit**: Add funds to a client’s account.
- **Withdraw**: Deduct funds from a client’s account.
- **Total Bank Balance**: Display the total balance across all accounts in the bank.
- **Transfer Between Accounts**: Transfer funds from one client’s account to another.
- **View Transfer Logs**: Access a history of all money transfers within the bank.

### Manage Users
- **List Users**: View all users with access to the system.
- **Add User**: Create new user accounts for accessing the system.
- **Delete User**: Remove a user from the system.
- **Update User**: Modify existing user details.
- **Find User**: Search for users by name or ID.

### Login Registers
- **Track User Logins**: Save and record the date and time when a user logs in.

### Currency Exchange
- **List Currencies**: View a list of supported currencies and their rates.
- **Find Currency**: Search for specific currencies.
- **Update Exchange Rates**: Modify exchange rates for currencies.
- **Currency Calculator**: Calculate conversions between different currencies.

### Security & Authentication
- **Login System**: Users must log in with valid credentials to access the system.
- **Login Attempts**: The system is secured with a three-attempt limit for login. After three failed attempts, the program will close to prevent unauthorized access.
- **Logout**: Users can securely log out of the system when finished.

## Technologies Used
- **Programming Language**: C++
- **Database**: File-based DBMS (used to store clients, users, and transaction logs)
- **Object-Oriented Programming (OOP)**: Designed using OOP principles like classes, inheritance, and encapsulation.
