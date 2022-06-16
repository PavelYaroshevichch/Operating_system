#include<stdlib.h>
#include "message.h"

using namespace std;

int main(int argc, char *argv[])
{
    string nameOfFile = argv[1];
    int senderID = atoi(argv[2]);
    fstream file;

    HANDLE fileReadSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Read Semaphore");
    HANDLE fileWriteSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Write Semaphore");
    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Current Process Mutex");
    HANDLE senderStartEvent = OpenEvent(EVENT_MODIFY_STATE,
                                        FALSE,
                                        (LPSTR)(L"Sender " + ConvertIntegerNumberToWstring(senderID) + L"Event").c_str());
    SetEvent(senderStartEvent);

    while(true){
        cout << "\n\n\nSender " << senderID << " Console \n Select Option: \n"
             << "1: Send message \n 2: Exit \n";

        int option; cin >> option;
        if (option == 2) {
            ReleaseMutex(mutex);
            break;
        }

        WaitForSingleObject(fileWriteSemaphore, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        cout << "Enter message\n";
        string message; cin >> message;

        file.open(nameOfFile.c_str(), ios::out | ios::binary | ios::app);
        file << Message(message);
        file.close();

        ReleaseMutex(mutex);
        ReleaseSemaphore(fileReadSemaphore, 1, NULL);
    }

    CloseHandle(mutex);
    CloseHandle(fileReadSemaphore);
    CloseHandle(fileWriteSemaphore);
    CloseHandle(senderStartEvent);
}

