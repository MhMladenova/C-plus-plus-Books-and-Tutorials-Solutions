#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string* expandClipboardArr(string* currentClipboard, int numWords, int& currentClipboardSize)
{
    int newSize = numWords + currentClipboardSize;
    string* clipboard = new string[newSize];

    for (int i = 0; i < currentClipboardSize; i++)
    {
        clipboard[i] = currentClipboard[i];
    }

    if (currentClipboard != NULL)
    {
        delete[] currentClipboard;
    }

    return clipboard;
}

string* copyToClipboard(const string& text, int firstIndex, int lastIndex,
                        string* currentClipboard, int& currentClipboardSize)
{
    while (firstIndex > 0 && isalpha(text[firstIndex]))
    {
        firstIndex--;
    }

    while (lastIndex < text.size() - 1 && isalpha(text[lastIndex]))
    {
        lastIndex++;
    }

    string copied = text.substr(firstIndex, (lastIndex + 1) - firstIndex);

    stringstream copiedStream(copied);

    int numWords = 0;
    string word;
    while(copiedStream >> word)
    {
        numWords++;
    }

    stringstream readStream(copied);

    string* clipboard = expandClipboardArr(currentClipboard, numWords, currentClipboardSize);

    int index = currentClipboardSize;
    while(readStream >> word)
    {
        clipboard[index] = word;
        index++;
    }

    currentClipboardSize = numWords + currentClipboardSize;;
    return clipboard;
}

void paste(string& text, int clipboardIndex, int pasteIndex, string* clipboard)
{
    string pasteString = clipboard[clipboardIndex];

    text.insert(pasteIndex, pasteString);
}

int main()
{
    string text;

    getline(cin, text);

    int n;
    cin >> n;

    //copy 10 20
    //paste 0 1

    string* clipboard = NULL;
    int clipboardSize = 0;
    for (int i = 0; i < n; i++)
    {
        string operationName;

        cin >> operationName;
        if (operationName == "copy")
        {
            int startIndex, endIndex;
            cin >> startIndex >> endIndex;
            clipboard = copyToClipboard(text, startIndex, endIndex, clipboard, clipboardSize);
        }
        else //if(operation == "paste")
        {
            int clipboardIndex, pasteIndex;
            cin >> clipboardIndex >> pasteIndex;

            paste(text, clipboardIndex, pasteIndex, clipboard);
        }

    }

    delete[] clipboard;

    cout << text;

    return 0;
}
