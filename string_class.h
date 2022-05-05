#include <iostream>
using namespace std;

class myString
{
    char *myStr;
    int size;

public:
    myString() // default contructor sets size to 100 and dynamically allocates memory to myStr. initializes first character to \0 so its an empty string
    {
        size = 100;
        myStr = new char[size];
        myStr[0] = '\0';
    }

    myString(int len) // parameterized contructor sets size to length passed as parameter and dynamically allocates memory to myStr. initializes first character to \0 so its an empty string
    {
        myStr = new char[len];
        size = len;
        myStr[0] = '\0';
    }

    myString(char *arr) // overloaded parameterized constructor initializes myStr to the character array passed as parameter
    {
        int len = strlength(arr);
        myStr = new char[len + 1];
        size = len + 1;

        for (int i = 0; i < len + 1; i++)
            myStr[i] = arr[i];
    }

    ~myString() {} // destructor

    void changeSize(int newSize) // changes size of this->myStr to newSize
    {
        if (myStr != NULL)
        {
            delete[] myStr;
            this->myStr = new char[newSize];
            this->size = newSize;
        }
    }

    int myStrLen() // returns length of this->myStr
    {
        int i;
        for (i = 0; myStr[i] != '\0'; i++);

        return i;
    }

    int strlength(char *arr) // returns length of character array passed
    {
        int i;
        for (i = 0; arr[i] != '\0'; i++);

        return i;
    }

    int myStrSize() // returns size of the dynamic array this->myStr
    {
        return size;
    }

    myString operator+(myString strobj) // overloads the '+' operator and returns the result of concatinating two strings (*this + strobj)
    {
        myString temp;

        int i = 0;
        while (myStr[i] != '\0')
        {
            temp[i] = myStr[i];
            i++;
        }

        int j = 0;
        while (strobj[j] != '\0')
        {
            temp[i] = strobj[j];
            i++;
            j++;
        }

        temp[i] = '\0';

        return temp;
    }

    void operator+=(myString strobj) // overloads the += operator and sets the value of *this = *this + strobj
    {
        myString temp;

        int i = 0;
        while (myStr[i] != '\0')
        {
            temp[i] = myStr[i];
            i++;
        }

        int j = 0;
        while (strobj[j] != '\0')
        {
            temp[i] = strobj[j];
            i++;
            j++;
        }

        temp[i] = '\0';
        // temp = *this + strobj

        int len = temp.myStrLen();
        changeSize(len + 1);

        for (int i = 0; i < len; i++)
            myStr[i] = temp[i]; // myStr = temp.myStr

        myStr[len] = '\0';
    }

    void operator=(myString strobj) // overloads the assignment operator and sets value of *this = strobj
    {
        int len = strobj.myStrLen();
        changeSize(len + 1); // deletes myStr and reallocates memory to change the size to length of strobj

        for (int i = 0; i < len; i++)
            myStr[i] = strobj[i];

        myStr[len] = '\0';
    }

    char &operator[](int index) // gets/sets individual characters of myString. returns the refrence of the index element of myString
    {
        return myStr[index];
    }

    bool operator==(myString strobj) // overloads the '==' operator to check if two strings are equal. returns 1 if theyre equal and zero otherwise
    {
        int len1 = myStrLen();
        int len2 = strobj.myStrLen();

        if (len1 != len2)
            return false;

        for (int i = 0; i < len1 && i < len2; i++)
        {
            if (myStr[i] != strobj[i])
                return false;
        }

        return true;
    }

    bool operator!=(myString strobj) // overloads the '!=' operator to check if two strings are equal. returns 1 if theyre not equal and 0 otherwise
    {
        int len1 = myStrLen();
        int len2 = strobj.myStrLen();

        if (len1 != len2)
            return true;

        for (int i = 0; i < len1 && i < len2; i++)
        {
            if (myStr[i] != strobj[i])
                return true;
        }

        return false;
    }

    bool operator<(myString strobj) // overloads the '<' operator to return 1 if str1 < str2  ( or *this < strobj) and 0 otherwise
    {
        int len1 = myStrLen();
        int len2 = strobj.myStrLen();

        for (int i = 0; i < len1 && i < len2; i++)
        {
            if (myStr[i] < strobj[i])
                return true;
            else if (myStr[i] > strobj[i])
                return false;
        }

        if (len1 < len2) // if characters same but length is different
            return true;
        else
            return false;
    }

    bool operator>(myString strobj) // overloads the '>' operator to return 1 if str1 > str2 ( or *this > strobj) and 0 otherwise
    {
        int len1 = myStrLen();
        int len2 = strobj.myStrLen();

        for (int i = 0; i < len1 && i < len2; i++)
        {
            if (myStr[i] > strobj[i])
                return true;
            else if (myStr[i] < strobj[i])
                return false;
        }

        if (len1 > len2) // if characters same but length is different
            return true;
        else
            return false;
    }

    myString operator()(int start, int numchars) // returns string based on the starting index and number of characters of *this->myStr. first parameter = starting index, second parameter = number of characters to copy
    {
        myString temp(numchars + 1);

        for (int i = start, j = 0; i < numchars; i++, j++)
        {
            temp[j] = myStr[i];
        }

        temp[numchars] = '\0';

        return temp;
    }

    friend ostream &operator<<(ostream &output, myString strobj) // overloads the stream insertion operator to output myStr
    {
        output << strobj.myStr;

        return output;
    }

    friend istream &operator>>(istream &input, myString &strobj) // overloads the stream extraction operator to take input to store in myStr. strobj is passed as refrence so that value of strobj.myStr can be changed
    {
        strobj.changeSize(100); // changes size of strobj.myStr to 100, incase the original size is too small to store all of the characters
        input >> strobj.myStr;

        return input;
    }

    myString operator<<(int numchars) // overloads the string left shift operator and returns the left most numchars number of characters
    {
        myString str(numchars + 1); // str is the string that will be returned. calling overloaded constructor which accepts length as parameter.
        // length of str = numchars + 1, 1 is added to numchars due to \0

        for (int i = 0; i < numchars; i++) // storing the first numchars characters of myStr into str
            str[i] = myStr[i];

        str[numchars] = '\0';

        int strlen = myStrLen();
        int newlen = strlen - numchars;                     // new length of myStr = original length - number of characters removed
        myString temp(newlen + 1);                         // + 1 for \0
        for (int i = numchars, j = 0; j < newlen; i++, j++) // stores the last newlen number of characters in temp
            temp[j] = myStr[i];

        temp[newlen] = '\0';

        *this = temp; // calls the overloaded assignment operator

        return str;
    }

    myString operator>>(int numchars) // overloads the string right shift operator and returns the right most numchars number of characters
    {
        myString str(numchars + 1); // calling overloaded constructor which accepts length as parameter.
        // size of str = numchars + 1, 1 is added to numchars due to \0

        int strlen = myStrLen();

        for (int i = strlen - 1, j = 0; j < numchars; i--, j++) // storing last numchars characters in str
            str[j] = myStr[i];

        str[numchars] = '\0';

        int newlen = strlen - numchars; // new length of myStr = length - number of characters removed
        myString temp(newlen + 1);     // +1 for \0

        for (int i = 0; i < newlen; i++) // only stores the first newlen characters in temp
            temp[i] = myStr[i];

        temp[newlen] = '\0';

        *this = temp; // calls the overloaded assignment operator

        return str;
    }
};
