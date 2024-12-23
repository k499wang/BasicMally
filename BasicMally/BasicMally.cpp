// BasicMally.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <sstream>

using namespace std;

//void xor_decrypt(char *pMem, string& value, string& key) {
//    for (int i = 0; i < value.size(); i +=2) {
//		int int_value = stoi(value.substr(i, 2), nullptr, 16);
//        char decrypted_key = (char)(int_value ^ key[(i / 2) % key.size()]);
//		pMem[i / 2] = decrypted_key;
//
//    }
//
//	pMem[(value.size()/2)] = '\0'; // null terminate the string
//}

//int main()
//{
//    string key = "k3vin";
//    string value = "0a471e0c000a";
//
//
//    LPVOID pMem = VirtualAlloc(0, sizeof(value), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//	if (pMem == NULL) {
//		cout << "VirtualAlloc failed" << endl;
//		return 1;
//	}
//
//	RtlCopyMemory(pMem, value.c_str(), sizeof(value)); // c_str returns non-modifiable non temrinated version of S
//	xor_decrypt((char*)pMem, value, key);
//
//	cout << "Decrypted value: " << (char*)pMem << endl;
//
//	MessageBoxA(0, (char*)pMem, "Decrypted value", MB_OK); // WE WILL BE HOOKING THIS FUNCTIOn
//
//	VirtualFree(pMem, 0, MEM_RELEASE);
//
//	return 0;
//
//
//}


// Function to XOR-decrypt a string using a key

string xor_decrypt(string& value, string& key) {
	ostringstream os;
    for (int i = 0; i < value.size(); i +=2) {
		int int_value = stoi(value.substr(i, 2), nullptr, 16);
        char decrypted_key = (char)(int_value ^ key[(i / 2) % key.size()]);
		os << decrypted_key;

    }

	return os.str();
}

int main()
{



    string key = "k3vin";
    string value = "0a471e0c000a"; // encrypted value, which the original message is 'athena'

	string decrypt = xor_decrypt(value, key);

    
    LPVOID pMem = VirtualAlloc(0, sizeof(decrypt), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); // dynamically allocate memory to store our key
	if (pMem == NULL) {
		cout << "VirtualAlloc failed" << endl;
		return 1;
	}

	RtlCopyMemory(pMem, decrypt.c_str(), sizeof(decrypt)); // c_str returns a c-string.

	cout << "Decrypted value: " << (char*)pMem << endl;

	std::cin.get();

	MessageBoxA(0, (char*)pMem, "Decrypted value", MB_OK); // WE WILL BE HOOKING THIS FUNCTION

	VirtualFree(pMem, 0, MEM_RELEASE);

	return 0;


}
