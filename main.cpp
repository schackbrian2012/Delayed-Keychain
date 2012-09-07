//
//  main.cpp
//  Delayed Keychain
//
//  Created by Brian Schack on 1/21/12.
//  Copyright (c) 2012 Brian Schack. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <sys/stat.h>

int main(int argc, const char* argv[]) {
    const char* folder = "/Users/brianschack/Delayed Keychain";
    const char* keychain = "/Users/brianschack/Delayed Keychain/Delayed Keychain.txt";
    const char* status = "/Users/brianschack/Delayed Keychain/Delayed Keychain Status.txt";
    time_t wait =   60 * 60;
    if (argc > 1 && strcmp(argv[1], "Lock") == 0) {
        std::cout << chmod(folder, 0555) << "\n";
        std::cout << chown(folder, 0, 20) << "\n";
        std::cout << chmod(keychain, 0) << "\n";
        std::cout << chown(keychain, 0, 20) << "\n";
        std::ofstream statusStream(status);
        statusStream << 0;
        statusStream.close();
        std::cout << chmod(status, 0) << "\n";
        std::cout << chown(status, 0, 20) << "\n";
        std::cout << "Delayed Keychain Locked\n";
    } else if (argc > 1 && strcmp(argv[1], "Unlock") == 0) {
        std::ifstream statusStream(status);
        time_t lockTime;
        statusStream >> lockTime;
        statusStream.close();
        time_t currentTime;
        time(&currentTime);
        if (lockTime == 0) {
            std::ofstream statusStream(status);
            statusStream << currentTime;
            statusStream.close();
            lockTime = currentTime;
        }
        time_t remainingTime = lockTime + wait - currentTime;
        if (remainingTime > 0) {
            std::cout << remainingTime / 3600 << " hour(s) " << (remainingTime % 3600) / 60 << " minute(s) " << remainingTime % 60 << " second(s) remaining\n";
        } else {
            std::cout << chmod(folder, 0700) << "\n";
            std::cout << chown(folder, 501, 20) << "\n";
            std::cout << chmod(keychain, 0644) << "\n";
            std::cout << chown(keychain, 501, 20) << "\n";
            std::cout << chmod(status, 0644) << "\n";
            std::cout << chown(status, 501, 20) << "\n";
            std::cout << "Delayed Keychain Unlocked\n";
        }   
    }
    return 0;
}