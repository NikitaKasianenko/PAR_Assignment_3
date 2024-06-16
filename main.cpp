#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

typedef string(*encrypt_ptr)(string, int);
typedef string(*decrypt_ptr)(string, int);

void clearInputBuffer() {
    cin.ignore(); 
    while (cin.get() != '\n');
}

int main() {

    HINSTANCE handle = LoadLibrary(TEXT("caesar.dll"));
    if (handle == nullptr) {
        cout << "Library not found or failed to load" << endl;
        return 1;
    }

    encrypt_ptr encrypt = (encrypt_ptr)GetProcAddress(handle, "encrypt");
    decrypt_ptr decrypt = (decrypt_ptr)GetProcAddress(handle, "decrypt");

    if (encrypt == nullptr || decrypt == nullptr) {
        cout << "Function(s) not found in the library" << endl;
        FreeLibrary(handle);
        return 1;
    }

    while (true) {
        string command;
        string text;

        cout << "Encrypt - 1, Decrypt - 2, Exit - 3: ";
        getline(cin, command);

        if (command == "3") {
            FreeLibrary(handle);
            break;
        }

        if (command != "1" && command != "2") {
            cout << "Invalid command." << endl;
            continue;
        }

        cout << "Please enter text: ";
        getline(cin, text);
        cout << "Enter key: ";
        int key;

        while (!(cin >> key)) {
            cin.clear(); 
            clearInputBuffer();
            cout << "Invalid key. Please enter a valid integer key: ";
        }

        cin.ignore(); 

        if (command == "1") {
            string encrypted_text = encrypt(text, key);
            cout << "Encrypted text: " << encrypted_text << endl;
        }

        else if (command == "2") {
            string decrypted_text = decrypt(text, key);
            cout << "Decrypted text: " << decrypted_text << endl;
        }
    }

    return 0;
}
