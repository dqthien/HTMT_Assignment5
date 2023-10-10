#include "GUI.h"

void GUISave()
{
    string result = "";
    int choice1 = -1, cancel = 0, byte = 0;
    while (choice1 != 0)
    {
        cancel = 0, byte = 0;
        result.clear();
        cout << "What do you want to do next: " << endl;
        cout << "0. Exit." << endl;
        cout << "1. Convert deciaml to bin as excess K." << endl;
        cout << "2. Convert integer to bin as two complement number." << endl;
        cout << "3. Convert decimal to bin as floating point 32 (always 32 bits). " << endl;
        cout << "4. Convert decimal to bin as floating point 64 (always 64 bits). " << endl;
        cout << "5. Convert string to bin as ASCII. " << endl;
        cout << "6. Convert string to bin as UTF-16. " << endl;
        cout << "Your choice: ";
        cin >> choice1;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(2000, '\n');
            choice1 = -1;
        }
        if (choice1 < 0 || choice1 > 6)
        {
            cout << "Invalid choice. Please choose again.\n\n";
        }
        if (choice1 == 0)
        {
            break;
        }
        else if (choice1 >= 1 && choice1 <= 4)
        {
            double input = 0;
            cout << "Input the number you want to convert to bin: ";
            cin >> input;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(2000, '\n');
                cout << "Invalid input.\n\n";
            }
            else
            {
                if (choice1 == 1 || choice1 == 2)
                {
                    cout << "Input the byte of the bit sequence you want to convert to: ";
                    cin >> byte;
                    if (cin.fail() || byte <= 0 || byte > 8)
                    {
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(2000, '\n');
                        }
                        cout << "Invalid input (byte must be an positive integer and not bigger than 8).\n\n";
                        cout << "Cancel converting." << endl;
                        cancel = 1;
                    }
                }
                if (cancel == 0)
                {
                    switch (choice1)
                    {
                    case 1:
                    {
                        int K = 0;
                        cout << "You choosed convert deciaml to bin as excess K." << endl;
                        cout << "Input the K: ";
                        cin >> K;
                        if (cin.fail() || K < 0)
                        {
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(2000, '\n');
                            }
                            cout << "Invalid input (K must not be a negative integer)." << endl;
                            cout << "Cancel converting." << endl;
                        }
                        else
                        {
                            if (input + K < 0 || (input + K > pow(double(2), byte * 8) - 1))
                            {
                                cout << "Warning: K=" << K << " and byte=" << byte;
                                cout << " can only represent number from ";
                                cout << -K << " to " << pow(double(2), byte * 8) - 1 - K << "." << endl;
                                cout << "Your input number will be set to " << -K << endl;
                                input = -K;
                            }
                            result += Dec_To_Bin_K(input, K, byte);
                        }
                        break;
                    }
                    case 2:
                    {
                        cout << "You choosed convert integer to bin as two complement number." << endl;
                        double temp1 = pow(double(2), byte * 8);
                        if ((input + temp1 / 2) <= -1 || (input - temp1 / 2) >= 1)
                        {
                            cout << "Warning: Two complement with " << byte << " can only represent number from ";
                            cout << (-temp1 / 2) << " to " << (temp1 / 2) - 1 << "." << endl;
                            cout << "Your input number will be set to 0" << endl;
                            input = 0;
                        }
                        else if ((input + temp1 / 2) < 0 && (input + temp1 / 2) > -1)
                        {
                            input = (-temp1) / 2;
                        }
                        else if ((input - temp1 / 2) > 0 && (input - temp1 / 2) < 1)
                        {
                            input = (temp1 / 2) - 1;
                        }
                        result += Dec_To_Signed(input, byte);
                        break;
                    }
                    case 3:
                    {
                        cout << "You choosed convert decimal to bin as floating point 32 (always 32 bits)." << endl;
                        if (input == 0)
                        {
                            for (int i = 0; i < 32; i++)
                            {
                                result.push_back('0');
                            }
                        }
                        else
                        {
                            result += Dec_To_Float32(input);
                        }
                        byte = 4;
                        break;
                    }
                    case 4:
                    {
                        cout << "You choosed convert decimal to bin as floating point 64 (always 64 bits)." << endl;
                        if (input == 0)
                        {
                            for (int i = 0; i < 64; i++)
                            {
                                result.push_back('0');
                            }
                        }
                        else
                        {
                            result += Dec_To_Float64(input);
                        }
                        byte = 8;
                        break;
                    }
                    }
                }
            }
        }
        else if (choice1 == 5 || choice1 == 6)
        {
            string inputstr;
            cin.ignore(1);
            if (choice1 == 5)
            {
                cout << "You choosed convert string to bin as ASCII." << endl;
                cout << "Input a string: ";
                getline(cin, inputstr);
                result = ASCII_To_Bin(inputstr);
                byte = 1;
            }
            else
            {
                wstring winputstr;
                cout << "You choosed convert string to bin as UTF-16." << endl;
                cout << "Input your string: ";
                getline(wcin, winputstr);
                result = UTF16_To_Bin(winputstr);
                byte = 2;
            }
        }
        system("pause");
        system("CLS");
        if (result.size() > 0)
        {
            int type_represent = 0;
            if (choice1 != 5)
            {
                while (type_represent < 1)
                {
                    cout << "Which way do want to represent it?" << endl;
                    cout << "1. BE" << endl;
                    cout << "2. LE" << endl;
                    cout << "Your choice: ";
                    cin >> type_represent;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(2000, '\n');
                        type_represent = 0;
                    }
                    if (type_represent < 1 || type_represent > 2)
                    {
                        cout << "Invalid choice. Please choose again.\n\n";
                    }
                }
                if (type_represent == 2)
                {
                    result = BE_To_LE(result, byte);
                }
            }
            cout << "Your bit sequence is: ";
            printBitSequence(result);
            int choicesave = -1;
            while (choicesave < 0)
            {
                cout << "Do you want to save it?" << endl;
                cout << "0. No" << endl;
                cout << "1. Yes" << endl;
                cout << "Your choice: ";
                cin >> choicesave;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(2000, '\n');
                    choicesave = -1;
                }
                if (choicesave < 0 || choicesave > 1)
                {
                    cout << "Invalid choice. Please choose again.\n\n";
                }
            }
            if (choicesave == 1)
            {
                Write_To_BinFile(result);
            }
            else
            {
                cout << "You chossed not save." << endl;
            }
        }
        else
        {
            cout << "There is nothing to save." << endl;
        }
        system("pause");
        system("CLS");
    }
}
void GUILoad()
{
    string output = ""; // , readfromfile = "";
    int offset = -1, choice2 = -1, typeseq = 0;
    double byte = -1;
    bool nothing_to_print = true;
    //function to read all the file to the string readfromfile.
    while (choice2 != 0)
    {
        nothing_to_print = true;
        //readfromfile.clear();
        output.clear();
        cout << "What do you want to do next:" << endl;
        cout << "0. Exit" << endl;
        cout << "1. Convert to dec as excees K and print it to console." << endl;
        cout << "2. Convert to dec as two complement number and print it to console." << endl;
        cout << "3. Convert to dec as floating point 32 and print it to console." << endl;
        cout << "4. Convert to dec as floating point 64 and print it to console." << endl;
        cout << "5. Convert to string as ASCII and print it to console." << endl;
        cout << "6. Convert to string as UTF-16 and print it to console." << endl;
        cout << "Your choice: ";
        cin >> choice2;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(2000, '\n');
            choice2 = -1;
        }
        if (choice2 < 0 || choice2 > 6)
        {
            cout << "Invalid choice. Please choose again.\n\n";
        }
        if (choice2 == 0)
        {
            break;
        }
        else if (choice2 >= 1 && choice2 <= 6)
        {
            system("CLS");
            cout << "Choose the offset you want to start to read from: ";
            cin >> offset;
            if (cin.fail() || offset < 0)
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(2000, '\n');
                }
                offset = -1;
                cout << "Invalid offset (must not be a negative number)." << endl;
                cout << "Cancel reading file.";
                choice2 = -1;
            }
            else
            {
                int byte = 0;
                cout << "Choose the byte you want to read: ";
                cin >> byte;
                if (cin.fail() || byte < 0 || ((choice2 >= 1 && choice2 <= 4) && byte > 8))
                {
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(2000, '\n');
                    }
                    cout << "Invalid input (must be a positive number and not bigger than 8 if you want to read a number from file)." << endl;
                    cout << "Your byte will be set to 0." << endl;
                    byte = 0;
                }
                if (byte > 0)
                {
                    Read_From_BinFile(output, offset * 8, byte * 8);
                    if (output.size() > 0)
                    {
                        typeseq = 0;
                        nothing_to_print = false;
                        if (choice2 != 5)
                        {
                            while (typeseq <= 0)
                            {
                                cout << "This sequence is represent as:" << endl;
                                cout << "1. BE." << endl;
                                cout << "2. LE." << endl;
                                cout << "Your choice: ";
                                cin >> typeseq;
                                if (cin.fail())
                                {
                                    cin.clear();
                                    cin.ignore(2000, '\n');
                                    typeseq = 0;
                                }
                                if (typeseq < 1 || typeseq > 2)
                                {
                                    cout << "Invalid choose. Please choose again." << endl;
                                }
                            }
                            if (typeseq == 2)
                            {
                                if (choice2 >= 1 && choice2 <= 4)
                                {
                                    output = LE_To_BE(output, byte);
                                }
                                else
                                {
                                    output = LE_To_BE(output, 2);
                                }
                            }
                        }
                        switch (choice2)
                        {
                        case 1:
                        {
                            int K = 0;
                            cout << "You choosed convert to dec as excees K and print it to console." << endl;
                            cout << "Input the K: ";
                            cin >> K;
                            if (cin.fail() || K < 0)
                            {
                                if (cin.fail())
                                {
                                    cin.clear();
                                    cin.ignore(2000, '\n');
                                }
                                cout << "Invalid input (K must not be a negative integer)." << endl;
                                cout << "Cancel converting." << endl;
                            }
                            else
                            {
                                double result1 = 0;
                                BinToDecExcessK(output, result1, K);
                                cout << "Your number is: " << result1 << endl;
                            }
                            break;
                        }
                        case 2:
                        {
                            cout << "You choosed convert to dec as two complement number and print it to console." << endl;
                            double result2 = 0;
                            BinToDecTwoComplement(output, result2);
                            cout << "Your number is: " << result2 << endl;
                            break;
                        }
                        case 3:
                        {
                            cout << "You choosed convert to dec as floating point 32 and print it to console." << endl;
                            if (output.size() == 32)
                            {
                                float result3 = 0;
                                Float32_To_Dec(output, result3);
                                cout << "Your number is: " << fixed << setprecision(6) << result3 << endl;
                            }
                            else
                            {
                                cout << "Unable to convert to this type of number because your data does not have 32 bits." << endl;
                                nothing_to_print = true;
                            }
                            break;
                        }
                        case 4:
                        {
                            cout << "You choosed convert to dec as floating point 64 and print it to console." << endl;
                            if (output.size() == 64)
                            {
                                double result4 = 0;
                                Float64_To_Dec(output, result4);
                                cout << "Your number is: " << fixed << setprecision(6) << result4 << endl;
                            }
                            else
                            {
                                cout << "Unable to convert to this type of number because your data does not have 64 bits." << endl;
                                nothing_to_print = true;
                            }
                            break;
                        }
                        case 5:
                        {
                            cout << "You choosed convert to string as ASCII and print it to console." << endl;
                            string result5;
                            result5 = Bin_To_Str_ASCII(output);
                            cout << "Your string is: " << result5 << endl;
                            break;
                        }
                        case 6:
                        {
                            cout << "You choosed convert to string as UTF-16 and print it to console." << endl;
                            if (byte >= 2)
                            {
                                string result6;
                                if (output.size() % 16 == 0)
                                {
                                    result6 = Bin_To_Str_UTF16(output);
                                    cout << "Your string is: " << result6 << endl;
                                }
                                else
                                {
                                    cout << "The size of the bit sequence must divisible by 16" << endl;
                                }
                            }
                            else
                            {
                                cout << "UTF-16 needs at least 2 bytes to convert." << endl;
                            }
                            break;
                        }
                        }
                    }
                }
            }
        }
        if (nothing_to_print)
        {
            cout << "There is nothing to print out." << endl;
        }
        system("pause");
        system("CLS");
    }
}
void GUI()
{
    int choice = -1;
    while (choice != 0)
    {
        cout << "------------------------------------------------WELCOME TO OUR PROGRAM-----------------------------------------------";
        cout << "\nWhat do you want to do:" << endl;
        cout << "0.Exit" << endl;
        cout << "1.Write bit sequence to file." << endl;
        cout << "2.Read bit sequence from file as number or string." << endl;
        cout << "Your choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(2000, '\n');
            choice = -1;
        }
        if (choice < 0 || choice > 2)
        {
            cout << "Invalid choice. Please choose again." << endl;
        }
        else
        {
            system("CLS");
            if (choice == 0)
            {
                cout << "THANKS FOR USING OUR PROGRAM. HOPE TO SEE YOU AGAIN!!!\n";
                break;
            }
            else if (choice == 1)
            {
                cout << "You choosed write data to file." << endl;
                GUISave();
            }
            else if (choice == 2)
            {
                cout << "You choosed read data from file." << endl;
                GUILoad();
            }
        }
        system("pause");
        system("CLS");
    }
}
