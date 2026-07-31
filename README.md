# 💳 Credit Card Validator (C++)

A console-based Credit Card Validator written in C++ that validates card numbers using the **Luhn Algorithm**, detects card type, masks sensitive information, generates random valid Visa card numbers, and stores validation history.

---

## Features

- Luhn Algorithm Validation
- Detects Card Type
  - Visa
  - Mastercard
  - American Express
  - Discover
- Generates Random Valid Visa Cards
- Card Number Masking
- Validation History
- Clear History
- Input Validation
- Colored Console Output

---

## Technologies Used

- C++
- STL
- File Handling
- Random Number Generation

---

## Project Structure

```
Credit-Card-Validator
│
├── src
│   └── main.cpp
├── README.md
├── LICENSE
├── .gitignore
└── CONTRIBUTING.md
```

---

## How to Compile

### Windows

```bash
g++ src/main.cpp -o validator.exe
validator.exe
```

### Linux / macOS

```bash
g++ src/main.cpp -o validator
./validator
```

---

## Menu

```
1. Validate Credit Card
2. Generate Random Valid Card
3. View History
4. Clear History
5. Exit
```

---

## Sample Output

```
Enter credit card number:

4111111111111111

Masked Card : ************1111
Card Type   : Visa
Status      : Valid Credit Card
```

---

## Concepts Used

- Luhn Algorithm
- String Manipulation
- File Handling
- Functions
- Loops
- Conditionals
- Input Validation
- Random Number Generation

---

## Future Improvements

- GUI Version
- Database Support
- Export History to CSV
- Batch Validation
- Expiry Date Validation
- CVV Validation
- More Card Types
- REST API Version

---

## Author

Your Name
