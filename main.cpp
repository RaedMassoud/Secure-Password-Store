#include <iostream>
#include <string>
#include "linkedList.cpp"

using namespace std;

// Array to store values
uint32_t storedValues[1000];

// djb2 (Daniel J. Bernstein)
uint32_t djb2(const std::string& str) {

    // Initialize a 32 bit unsigned integer
    uint32_t hash = 5381;

    // Go over each charcter of the string.
    // For each character shift the bits of the hash to the left by 5 places ( multiply by 32 )
    // add the hash value and the charcter value
    for (char c : str) {
        
        hash = (hash << 5) + hash + c;
    }

    return hash;
}

// Method to store message
uint32_t messageIndex(uint32_t hashedMessage) {
    uint32_t buffer1, buffer2, buffer3, buffer4, buffer5;

    buffer1 = (hashedMessage / 100000000) % 10;
    buffer2 = (hashedMessage / 1000000) % 10;
    buffer3 = (hashedMessage / 10000) % 10;
    buffer4 = (hashedMessage / 1000) % 10;
    buffer5 = (hashedMessage / 10) % 10;

    uint32_t messageIndex = (buffer1 * buffer3 * buffer5); // starting number
    messageIndex = (messageIndex * 8) + buffer2; // shift bits 3 places and add buffer 2
    messageIndex = (messageIndex * 8) + buffer4; // shift bits 3 places and add buffer 4
    messageIndex = (messageIndex * 8) + (buffer1 + buffer3 + buffer5) ;  // shift bits 3 places and add random buffer

    return messageIndex % 1000; // return index
}

// Driver
int main() {

    bool flag = true;

    while(flag) {

        // user wants to insert or search ??
        cout << "1) Insert passwords \n2) Validate password \n3) Exit \n\n->";
        int choice;
        cin >> choice;
        cin.ignore(1, '\n');

        // declare
        int index;
        string rawMessage; // user input
        uint32_t hashedMessage; // hashed

        switch(choice) {
            case 1: 
                cout << "please enter passwords to store: "; // get user message
                getline(cin, rawMessage);

                hashedMessage = djb2(rawMessage); // convert raw message to hashed
                index = messageIndex(hashedMessage); // generate index for hashed message

                storedValues[index] = hashedMessage; // store hash message at index

                // Display some usefull info
                cout << "#####################################";
                cout << "\nRaw Message -> " << rawMessage <<
                "\nMessage Hash -> " << hashedMessage << 
                "\nMessage Index -> " << index;
                cout << "\n#####################################\n\n";

                break;
            case 2: 
                cout << "please password message to validate: ";
                getline(cin, rawMessage);

                hashedMessage = djb2(rawMessage); // get hash of raw message
                index = messageIndex(hashedMessage); // get index of hash

                if(storedValues[index] == hashedMessage) {

                    cout << "\n#####################################\n";
                    cout << "Password is valid!" <<
                    "\nGenerated hash matches stored hash";
                    cout << "\n#####################################\n\n";

                } else {
                    cout << "\n#####################################\n";
                    cout << "Password is invalid" <<
                    "\nGenerated hash matches stored hash";
                    cout << "\n#####################################\n\n";
                }
            
                break;

            case 3: 
                flag = false;
                break;

            default: cout << "Invalid input"; break;
        }
    }

    return 0;
}

