#include <iostream>
#include "bank_customer.h"
#include "buyer.h"

using namespace std;

// Menu utama
enum PrimaryPrompt {
    LOGIN,
    REGISTER,
    EXIT_PROGRAM
};

// Menu setelah login
enum LoginPrompt {
    CHECK_ACCOUNT_STATUS,
    UPGRADE_ACCOUNT,
    CREATE_BANKING_ACCOUNT,
    LOGOUT_TO_MAIN
};

int main() {
    Buyer* buyer1 = nullptr;
    BankCustomer* bankAcc = nullptr;

    bool isBuyer = false;
    bool isSeller = false;
    bool isBankLinked = false;

    PrimaryPrompt prompt = LOGIN;

    while (prompt != EXIT_PROGRAM) {
        cout << "=== Main Menu ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose option: ";

        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);

        switch (prompt) {
            case LOGIN: {
                cout << "\n--- Login selected ---\n";
                LoginPrompt loginPrompt = CHECK_ACCOUNT_STATUS;

                while (loginPrompt != LOGOUT_TO_MAIN) {
                    cout << "\n=== Login Menu ===" << endl;
                    cout << "1. Check Account Status" << endl;
                    cout << "2. Upgrade Account to Seller" << endl;
                    cout << "3. Create Banking Account" << endl;
                    cout << "4. Logout to Main Menu" << endl;
                    cout << "Choose option: ";

                    int loginChoice;
                    cin >> loginChoice;
                    loginPrompt = static_cast<LoginPrompt>(loginChoice - 1);

                    switch (loginPrompt) {
                        case CHECK_ACCOUNT_STATUS: {
                            cout << "\n[INFO] Check Account Status selected." << endl;

                            cout << "\n[User Role Status]" << endl;
                            if (isBuyer && isSeller) {
                                cout << "Your Role is Buyer and Seller." << endl;
                            } else if (isBuyer) {
                                cout << "Your Role is Buyer." << endl;
                            } else if (isSeller) {
                                cout << "Your Role is Seller." << endl;
                            } else {
                                cout << "You do not have Buyer or Seller account." << endl;
                            }

                            if (isBuyer && buyer1) {
                                cout << "\n[Buyer Account Details]" << endl;
                                cout << "Name : " << buyer1->getName() << endl;
                                cout << "ID   : " << buyer1->getId() << endl;
                                cout << "Linked Bank Account ID: " 
                                     << buyer1->getAccount().getId() << endl;
                            }

                            if (isBankLinked && bankAcc) {
                                cout << "\n[Banking Account Status]" << endl;
                                cout << "You have a linked banking account." << endl;
                                bankAcc->printInfo();
                            } else {
                                cout << "\nYou do not have a linked banking account." << endl;
                            }
                            break;
                        }

                        case UPGRADE_ACCOUNT: {
                            cout << "\n[INFO] Upgrade Account to Seller selected." << endl;

                            if (!isBankLinked) {
                                cout << "⚠️ Upgrade ditolak: Anda belum punya Bank Account linked!\n";
                            } else if (isSeller) {
                                cout << "⚠️ Anda sudah menjadi Seller!\n";
                            } else {
                                string storeName, storeAddr, storePhone, storeEmail;
                                cin.ignore();
                                cout << "Masukkan Store Name   : ";
                                getline(cin, storeName);
                                cout << "Masukkan Store Address: ";
                                getline(cin, storeAddr);
                                cout << "Masukkan Store Phone  : ";
                                getline(cin, storePhone);
                                cout << "Masukkan Store Email  : ";
                                getline(cin, storeEmail);

                                isSeller = true;

                                cout << "\nUpgrade successful! You are now also a Seller.\n";
                                cout << "--- Seller Details ---" << endl;
                                cout << "Store Name : " << storeName << endl;
                                cout << "Store Addr : " << storeAddr << endl;
                                cout << "Store Phone: " << storePhone << endl;
                                cout << "Store Email: " << storeEmail << endl;
                            }
                            break;
                        }

                        case CREATE_BANKING_ACCOUNT: {
                            cout << "\n[INFO] Create Banking Account selected." << endl;

                            if (isBankLinked) {
                                cout << "You already have a linked banking account.\n";
                            } else {
                                int accId;
                                double initDeposit;
                                string accName, address, phone, email;

                                cout << "Masukkan Account ID      : ";
                                cin >> accId;
                                cin.ignore();
                                cout << "Input Name               : ";
                                getline(cin, accName);
                                cout << "Input Initial Deposit    : ";
                                cin >> initDeposit;
                                cin.ignore();
                                cout << "Input Address            : ";
                                getline(cin, address);
                                cout << "Input Phone              : ";
                                getline(cin, phone);
                                cout << "Input Email              : ";
                                getline(cin, email);

                                bankAcc = new BankCustomer(accId, accName, initDeposit);
                                isBankLinked = true;

                                cout << "\nBanking account created successfully!\n";
                                bankAcc->printInfo();
                            }
                            break;
                        }

                        case LOGOUT_TO_MAIN:
                            cout << "\n[INFO] Logging out to Main Menu..." << endl;
                            break;

                        default:
                            cout << "\n[ERROR] Invalid option." << endl;
                            break;
                    }
                }

                /* 
                if Login is selected, based on authority then provide options:
                assume user is logged in as Buyer for now
                1. Check Account Status (will display if user is Buyer or Seller or both and linked banking account status)
                   Will display Buyer, Seller and Banking Account details

                2. Upgrade Account to Seller
                   Will prompt user to enter Seller details and create a Seller account linked to Buyer account
                   Will reject if a user dont have a banking account linked

                3. Create Banking Account (if not already linked), will be replaced with banking functions
                   Must provides: initial deposit amount, Address, Phone number, Email
                   Banking functions will provides: Balance checking, Transaction History, Deposit, Withdraw

                4. Browse Store Functionality
                5. Order Functionality
                6. Payment Functionality
                7. Logout (return to main menu)
                8. Delete Account
                assume user is logged in as Seller for now
                9.  Check Inventory
                10. Add Item to Inventory
                11. Remove Item from Inventory
                12. View Orders
                extra functions
                9. Exit to main Menu
                10. Exit Program
                */
                break;
            }

            case REGISTER: {
                cout << "\n--- Register selected ---" << endl;
                /* 
                if register is selected then go through registration process:
                1. Create a new Buyer Account
                   Must provides: Name, Home Address, Phone number, Email

                2. Option to create a Seller Account (will be linked to Buyer account)
                   Must provides: Store Name, Store Address, Store Phone number, Store Email

                After finished, immediately logged in as Buyer/Seller
                */
                break;
            }

            case EXIT_PROGRAM:
                cout << "\nExiting program. Goodbye!" << endl;
                break;

            default:
                cout << "\n[ERROR] Invalid option." << endl;
                break;
        }

        cout << endl;
    }

    // Cleanup memory (jaga-jaga)
    delete buyer1;
    delete bankAcc;

    return 0;
}
