#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <ctime>
#include <random>
#include <limits>
using namespace std;
 
const string RESET  = "\033[0m";
const string RED    = "\033[31m";
const string GREEN  = "\033[32m";
const string CYAN   = "\033[36m";
const string YELLOW = "\033[33m";
const string BOLD   = "\033[1m";
 
const string HISTORY_FILE = "history.txt";

string removeSpaces(string cardNumber)
{
    cardNumber.erase(remove(cardNumber.begin(), cardNumber.end(), ' '), cardNumber.end());
    return cardNumber;
}
 
bool isDigitsOnly(const string& cardNumber)
{
    for (char character : cardNumber)
    {
        if (!isdigit(static_cast<unsigned char>(character)))
        {
            return false;
        }
    }
    return true;
}
 
bool isValidLength(const string& cardNumber)
{
    return cardNumber.length() >= 13 && cardNumber.length() <= 19;
}
 
string maskCard(const string& cardNumber)
{
    string masked = cardNumber;
    int visibleDigits = 4;

    int hiddenCount = static_cast<int>(masked.length()) - visibleDigits;
 
    for (int i = 0; i < hiddenCount; i++)
    {
        masked[i] = '*';
    }
 
    return masked;
}
 
bool isValid(const string& cardNumber)
{
    int totalSum = 0;
    bool shouldDouble = false;
 
    for (int i = static_cast<int>(cardNumber.length()) - 1; i >= 0; i--)
    {
        int currentDigit = cardNumber[i] - '0';
 
        if (shouldDouble)
        {
            currentDigit *= 2;
            if (currentDigit > 9)
            {
                currentDigit -= 9;
            }
        }
 
        totalSum += currentDigit;
        shouldDouble = !shouldDouble;
    }
 
    return totalSum % 10 == 0;
}
 
string detectCardType(const string& cardNumber)
{
    size_t len = cardNumber.length();
 
    if (len == 0) return "Unknown";
 
    if (len == 15 && (cardNumber.substr(0, 2) == "34" || cardNumber.substr(0, 2) == "37"))
        return "American Express";

    if (cardNumber[0] == '4' && (len == 13 || len == 16 || len == 19))
        return "Visa";

    if (len == 16)
    {
        int prefix2 = stoi(cardNumber.substr(0, 2));
        int prefix4 = stoi(cardNumber.substr(0, 4));
 
        if (prefix2 >= 51 && prefix2 <= 55) return "Mastercard";
        if (prefix4 >= 2221 && prefix4 <= 2720) return "Mastercard";
    }

    if (len == 16 && (cardNumber.substr(0, 4) == "6011" || cardNumber.substr(0, 2) == "65"))
        return "Discover";
 
    return "Unknown";
}
 
string currentTimestamp()
{
    time_t now = time(nullptr);
    string ts = ctime(&now);
    if (!ts.empty() && ts.back() == '\n') ts.pop_back(); // ctime adds a trailing newline
    return ts;
}
 
void saveHistory(const string& cardNumber, const string& cardType, bool valid)
{
    ofstream file(HISTORY_FILE, ios::app);
 
    if (file.is_open())
    {
        file << "Time   : " << currentTimestamp() << endl;
        file << "Card   : " << maskCard(cardNumber) << endl;
        file << "Type   : " << cardType << endl;
        file << "Status : " << (valid ? "Valid" : "Invalid") << endl;
        file << "-------------------------------------" << endl;
 
        file.close();
    }
    else
    {
        cout << RED << "Warning: could not write to history file.\n" << RESET;
    }
}
 
void viewHistory()
{
    ifstream file(HISTORY_FILE);
 
    if (!file.is_open())
    {
        cout << YELLOW << "\nNo history found yet.\n" << RESET;
        return;
    }
 
    cout << CYAN << "\n===== Validation History =====\n" << RESET;
 
    string line;
    bool any = false;
    while (getline(file, line))
    {
        any = true;
        cout << line << endl;
    }
 
    if (!any)
        cout << YELLOW << "History file is empty.\n" << RESET;
 
    file.close();
}
 
void clearHistory()
{
    ofstream file(HISTORY_FILE, ios::trunc);
    if (file.is_open())
    {
        cout << GREEN << "\nHistory cleared.\n" << RESET;
        file.close();
    }
    else
    {
        cout << RED << "\nCould not clear history.\n" << RESET;
    }
}
 
void displayResult(const string& cardNumber)
{
    bool valid = isValid(cardNumber);
    string cardType = detectCardType(cardNumber);
 
    cout << "\nMasked Card : " << maskCard(cardNumber) << endl;
    cout << "Card Type   : " << cardType << endl;
 
    if (valid)
        cout << GREEN << "Status      : Valid Credit Card" << RESET << endl;
    else
        cout << RED << "Status      : Invalid Credit Card" << RESET << endl;
 
    saveHistory(cardNumber, cardType, valid);
}
 
string generateRandomCard()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> digitDist(0, 9);
 
    string card = "4"; // Visa prefix
 
    while (card.length() < 15)
    {
        card += char('0' + digitDist(gen));
    }
 
    for (int checkDigit = 0; checkDigit <= 9; checkDigit++)
    {
        string temp = card + char('0' + checkDigit);
        if (isValid(temp))
        {
            return temp;
        }
    }
 
    return ""; 
}
 
int readMenuChoice()
{
    int option;
 
    while (!(cin >> option))
    {
        cout << RED << "Please enter a number.\n" << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter your choice: ";
    }
 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return option;
}
 
void printMenu()
{
    cout << CYAN;
    cout << "\n=====================================\n";
    cout << BOLD << "      CREDIT CARD VALIDATOR\n" << RESET << CYAN;
    cout << "=====================================\n";
    cout << RESET;
 
    cout << "1. Validate Credit Card\n";
    cout << "2. Generate Random Valid Card\n";
    cout << "3. View History\n";
    cout << "4. Clear History\n";
    cout << "5. Exit\n";
 
    cout << "\nEnter your choice: ";
}
 
int main()
{
    int option;
 
    do
    {
        printMenu();
        option = readMenuChoice();
 
        switch (option)
        {
            case 1:
            {
                string cardNumber;
 
                cout << "\nEnter credit card number: ";
                getline(cin, cardNumber);
 
                cardNumber = removeSpaces(cardNumber);
 
                if (cardNumber.empty())
                {
                    cout << RED << "\nError: No card number entered.\n" << RESET;
                }
                else if (!isDigitsOnly(cardNumber))
                {
                    cout << RED << "\nError: Card number should contain digits only.\n" << RESET;
                }
                else if (!isValidLength(cardNumber))
                {
                    cout << RED << "\nError: Card number must contain between 13 and 19 digits.\n" << RESET;
                }
                else
                {
                    displayResult(cardNumber);
                }
                break;
            }
 
            case 2:
            {
                string card = generateRandomCard();
 
                cout << GREEN;
                cout << "\nGenerated Valid Card\n";
                cout << "----------------------\n";
                cout << "Card Number : " << card << endl;
                cout << "Masked Card : " << maskCard(card) << endl;
                cout << RESET;
 
                saveHistory(card, detectCardType(card), true);
                break;
            }
 
            case 3:
                viewHistory();
                break;
 
            case 4:
                clearHistory();
                break;
 
            case 5:
                cout << GREEN << "\nThank you for using Credit Card Validator!\n" << RESET;
                break;
 
            default:
                cout << RED << "\nInvalid Choice!\n" << RESET;
        }
 
    } while (option != 5);
 
    return 0;
}
