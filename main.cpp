#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include "./QuickScribe/QuickScribe.h"

using namespace std;

void TypeString(const std::string& input) {
    for (char ch : input) {
        SHORT vkCode = VkKeyScan(ch);
        if (vkCode == -1) continue;

        BYTE virtualKey = vkCode & 0xFF;
        BYTE shiftState = (vkCode >> 8) & 0xFF;

        if (shiftState & 1) {
            INPUT shiftDown = {0};
            shiftDown.type = INPUT_KEYBOARD;
            shiftDown.ki.wVk = VK_SHIFT;
            SendInput(1, &shiftDown, sizeof(INPUT));
        }

        INPUT keyDown = {0};
        keyDown.type = INPUT_KEYBOARD;
        keyDown.ki.wVk = virtualKey;
        SendInput(1, &keyDown, sizeof(INPUT));

        INPUT keyUp = {0};
        keyUp.type = INPUT_KEYBOARD;
        keyUp.ki.wVk = virtualKey;
        keyUp.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &keyUp, sizeof(INPUT));

        if (shiftState & 1) {
            INPUT shiftUp = {0};
            shiftUp.type = INPUT_KEYBOARD;
            shiftUp.ki.wVk = VK_SHIFT;
            shiftUp.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &shiftUp, sizeof(INPUT));
        }

        Sleep(30);
    }
}

void clearString(const string& str) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_BACK;

    for (size_t i = 0; i < str.length(); i++) {
        input.ki.dwFlags = 0;
        SendInput(1, &input, sizeof(INPUT));
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
        Sleep(30);
    }
}

void replace(const string& oldWord, const string& newWord) {
    clearString(oldWord);
    TypeString(newWord);
}

char getCharFromKey(int key, bool shift, bool caps) {
    if (key >= 'A' && key <= 'Z') {
        return shift ^ caps ? key : key + 32;
    }

    if (shift) {
        switch (key) {
            case '1': return '!';
            case '2': return '@';
            case '3': return '#';
            case '4': return '$';
            case '5': return '%';
            case '6': return '^';
            case '7': return '&';
            case '8': return '*';
            case '9': return '(';
            case '0': return ')';
            case '-': return '_';
            case '=': return '+';
            case '[': return '{';
            case ']': return '}';
            case '\\': return '|';
            case ';': return ':';
            case '\'': return '"';
            case ',': return '<';
            case '.': return '>';
            case '/': return '?';
            default: return key;
        }
    }
    return key;
}

void toLowerCase(string* str) {
    if (str != nullptr) {
        transform(str->begin(), str->end(), str->begin(), ::tolower);
    }
}

DWORD WINAPI RunInBackground(LPVOID lpParam) {
    string word = "";
    string sentence = "";
    string prefix = "";
    string fetchWord = "";
    QuickScribe qs("./Data/data.bin", 3);
    cout << "Autocomplete initialized" << endl;
    bool shift, caps;

    while (true) {
        shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) || 
                (GetAsyncKeyState(VK_LSHIFT) & 0x8000) || 
                (GetAsyncKeyState(VK_RSHIFT) & 0x8000);
        caps = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;

        for (int ch = 8; ch <= 190; ch++) {
            if (ch == VK_SHIFT || ch == VK_LSHIFT || ch == VK_RSHIFT) continue;

            if (GetAsyncKeyState(ch) & 0x8000) {
                if (!prefix.empty() && ch != VK_INSERT) prefix = "";

                if (ch == VK_SPACE || ch == VK_RETURN) {
                    if (!word.empty()) sentence += word + " ";
                    if (ch == VK_RETURN) {
                        qs.insertSentence(sentence);
                        sentence.clear();
                        qs.save();
                    }
                    word.clear();
                    prefix.clear();
                } else if (ch == VK_BACK) {
                    if (!word.empty()) {
                        word.pop_back();
                    }
                } else if (ch == VK_INSERT) {
                    if (!word.empty()) {
                        if (prefix.empty()) {
                            prefix = word;
                            string key = word;
                            toLowerCase(&key);
                            fetchWord = qs.fetchRecommendations(key);
                        } else fetchWord = qs.nextReccomendation();

                        string newWord = prefix + fetchWord.substr(prefix.length());
                        replace(word, newWord);
                        word = newWord;
                    }
                } else if (isprint(ch)) {
                    char actualChar = getCharFromKey(ch, shift, caps);
                    if (actualChar) {
                        word += actualChar;
                    }
                }
                while (GetAsyncKeyState(ch) < 0) {}
            }
        }
        Sleep(10);
    }
    return 0;
}

int main() {
    HANDLE hThread = CreateThread(NULL, 0, RunInBackground, NULL, 0, NULL);
    if (hThread == NULL) {
        cerr << "Error creating background thread!" << endl;
        return 1;
    }

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    return 0;
}
