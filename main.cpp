#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

class CryptoCurrency {
public:
    virtual int getValue() const = 0;
};

class Dogecoin : public CryptoCurrency {
public:
    int getValue() const override {
        return 100; // Replace with actual Dogecoin value retrieval mechanism
    }
};

class Bitcoin : public CryptoCurrency {
public:
    int getValue() const override {
        return 500; // Replace with actual Bitcoin value retrieval mechanism
    }
};

class Account {
private:
    int balance;
    int totalEquity;
    int cryptoInvest;
    int cryptoReturn;
    int dogecoin;
    int bitcoin;
    std::vector<std::pair<std::string, int>> transactions;

    int getRandomNumber() const {
        srand(time(NULL));
        return rand();
    }

    bool canBuy() const {
        return totalEquity > 0;
    }

    bool canSell(const CryptoCurrency* currency) const {
        return (currency == &doge && dogecoin > 0) || (currency == &btc && bitcoin > 0);
    }

public:
    static Dogecoin doge;
    static Bitcoin btc;

    Account() : balance(50000), totalEquity(100), cryptoInvest(0), cryptoReturn(0), dogecoin(0), bitcoin(0) {}

    bool deposit(int money) {
        balance += money;
        transactions.push_back({ "Deposit:", money });
        return true;
    }

    bool withdraw(int money) {
        if (money > balance) {
            return false;
        }
        balance -= money;
        transactions.push_back({ "Withdraw:", money });
        return true;
    }

    void getAccountInformation() const {
        std::cout << "Money Details:\n";
        std::cout << "Bank Balance:" << balance << std::endl;
        std::cout << "Dogecoin:" << dogecoin << std::endl;
        std::cout << "Bitcoin:" << bitcoin << std::endl;
    }

    bool buyCrypto(const CryptoCurrency* currency) {
        if (!canBuy()) {
            return false;
        }

        int option;
        std::cout << "Want to purchase " << (currency == &doge ? "dogecoin" : "bitcoin") << "? Press 1 for yes, 0 for no: ";
        std::cin >> option;

        if (option == 1) {
            if (getRandomNumber() % 251 == 0) {
                if (currency == &doge) {
                    dogecoin++;
                    balance -= currency->getValue();
                    cryptoInvest += currency->getValue();
                } else {
                    bitcoin++;
                    balance -= currency->getValue();
                    cryptoInvest += currency->getValue();
                }
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    bool sellCrypto(const CryptoCurrency* currency) {
        if (!canSell(currency)) {
            return false;
        }

        int option;
        std::cout << "Want to sell " << (currency == &doge ? "dogecoin" : "bitcoin") << "? Press 1 for yes, 0 for no: ";
        std::cin >> option;

        if (option == 1) {
            if (currency == &doge) {
                cryptoReturn += currency->getValue();
                balance += currency->getValue();
                transactions.push_back({ "Dogecoin Sold:", currency->getValue() });
                dogecoin--;
            } else {
                cryptoReturn += currency->getValue();
                balance += currency->getValue();
                transactions.push_back({ "Bitcoin Sold:", currency->getValue() });
                bitcoin--;
            }
            return true;
        }
        return false;
    }

    void showHistory() {
        std::cout << "Displaying All transactions\n";
        for (auto& transaction : transactions) {
            std::cout << transaction.first << " " << transaction.second << std::endl;
        }

        char temp;
        std::cout << "Do you want to clear all transactions? (Y/N): ";
        std::cin >> temp;

        int no = transactions.size();

        if (temp == 'Y' || temp == 'y') {
            transactions.clear();
            std::cout << "Total transactions cleared: " << no << std::endl;
        } else {
            std::cout << "Total transaction: " << no << std::endl;
        }
    }
};

Dogecoin Account::doge;
Bitcoin Account::btc;

int main() {
    Account person;
    int amount, choice;
    bool check;
    while (1) {
        std::cout << "***********************************************\n";
        std::cout << "Press 1 to see your Account Info\n";
        std::cout << "Press 2 to Deposit money\n";
        std::cout << "Press 3 to Withdraw money\n";
        std::cout << "Press 4 to see your transaction history\n";
        std::cout << "Press 5 to Buy Crypto\n";
        std::cout << "Press 6 to Sell Crypto\n";
        std::cout << "Press any other key to exit\n";
        std::cout << "***********************************************\n";

        std::cin >> choice;
        int ans;

        switch (choice) {
        case 1:
            person.getAccountInformation();
            break;

        case 2:
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            ans = person.deposit(amount);
            if (ans) {
                std::cout << "Successfully deposited money" << std::endl;
            } else {
                std::cout << "Failed" << std::endl;
            }
            break;

        case 3:
            std::cout << "Enter amount to withdraw: ";
            std::cin >> amount;
            ans = person.withdraw(amount);
            if (ans) {
                std::cout << "Successfully withdrawn amount" << std::endl;
            } else {
                std::cout << "Not Enough Balance" << std::endl;
            }
            break;

        case 4:
            person.showHistory();
            break;

        case 5:
            std::cout << "Want to purchase dogecoin (1) or bitcoin (2)? ";
            std::cin >> amount;
            ans = amount == 1 ? person.buyCrypto(&Account::doge) : person.buyCrypto(&Account::btc);
            if (ans) {
                std::cout << "Successful Transaction" << std::endl;
            } else {
                std::cout << "Better Luck next time" << std::endl;
            }
            break;

        case 6:
            std::cout << "Want to sell dogecoin (1) or bitcoin (2)? ";
            std::cin >> amount;
            ans = amount == 1 ? person.sellCrypto(&Account::doge) : person.sellCrypto(&Account::btc);
            if (ans) {
                std::cout << "Successful Transaction" << std::endl;
            } else {
                std::cout << "Not Enough Cryptocoins" << std::endl;
            }
            break;

        default:
            exit(0);
            break;
        }
    }
}


