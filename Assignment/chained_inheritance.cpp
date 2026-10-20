// Chained (Multilevel) Inheritance
// Real-world example: mobile money system
// Chain: Account -> MobileWallet -> AgentWallet

#include <iostream>
#include <string>
using namespace std;

// Level 1: Base class
class Account {
protected:
    // Data members
    string ownerName;
    string accountId;
    double balance;

public:
    // Member functions
    Account(string name, string id, double openingBalance)
        : ownerName(name), accountId(id), balance(openingBalance) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "  [Account] Deposited UGX " << amount << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "  [Account] Withdrew UGX " << amount << endl;
            return true;
        }
        cout << "  [Account] Withdrawal failed: insufficient funds" << endl;
        return false;
    }

    void showAccountInfo() const {
        cout << "  Owner: " << ownerName << " | ID: " << accountId
             << " | Balance: UGX " << balance << endl;
    }
};

// Level 2: Derived from Account
class MobileWallet : public Account {
protected:
    // Data members
    string phoneNumber;
    int transactionCount;

public:
    // Member functions
    MobileWallet(string name, string id, double bal, string phone)
        : Account(name, id, bal), phoneNumber(phone), transactionCount(0) {}

    bool sendMoney(MobileWallet &receiver, double amount) {
        cout << "  [Wallet] " << ownerName << " -> " << receiver.ownerName << endl;
        if (withdraw(amount)) {        // inherited from Account
            receiver.deposit(amount);  // inherited from Account
            transactionCount++;
            return true;
        }
        return false;
    }

    void showWalletInfo() const {
        showAccountInfo();             // inherited from Account
        cout << "  Phone: " << phoneNumber
             << " | Transactions sent: " << transactionCount << endl;
    }
};

// Level 3: Derived from MobileWallet
class AgentWallet : public MobileWallet {
private:
    // Data members
    string agentCode;
    double commissionRate;
    double commissionEarned;

public:
    // Member functions
    AgentWallet(string name, string id, double bal, string phone,
                string code, double rate)
        : MobileWallet(name, id, bal, phone),
          agentCode(code), commissionRate(rate), commissionEarned(0) {}

    void cashIn(MobileWallet &customer, double amount) {
        cout << "  [Agent " << agentCode << "] Cash-in of UGX " << amount << endl;
        if (sendMoney(customer, amount)) {   // inherited from MobileWallet
            double commission = amount * commissionRate;
            commissionEarned += commission;
            balance += commission;           // balance inherited from Account
        }
    }

    void showAgentInfo() const {
        showWalletInfo();                    // inherited from MobileWallet
        cout << "  Agent Code: " << agentCode
             << " | Commission earned: UGX " << commissionEarned << endl;
    }
};

int main() {
    cout << "CHAINED INHERITANCE: Account -> MobileWallet -> AgentWallet\n\n";

    // Object of Level 1 (base class)
    cout << "1) Account object:" << endl;
    Account acc("Grace Nakato", "ACC-001", 50000);
    acc.deposit(10000);
    acc.showAccountInfo();

    // Objects of Level 2: inherited (deposit) and local (sendMoney) members
    cout << "\n2) MobileWallet objects:" << endl;
    MobileWallet w1("Brian Okello", "W-101", 80000, "0771000111");
    MobileWallet w2("Sarah Namuli", "W-102", 20000, "0702000222");
    w1.sendMoney(w2, 30000);   // local to MobileWallet
    w1.deposit(5000);          // inherited from Account
    w1.showWalletInfo();
    w2.showWalletInfo();

    // Object of Level 3: inherited (withdraw, sendMoney) and local (cashIn) members
    cout << "\n3) AgentWallet object:" << endl;
    AgentWallet agent("Moses Ssemanda", "A-501", 500000, "0752000333", "AG-77", 0.01);
    agent.cashIn(w2, 100000);  // local to AgentWallet
    agent.withdraw(20000);     // inherited from Account
    agent.showAgentInfo();
    w2.showWalletInfo();

    return 0;
}
