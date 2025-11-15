
#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    string AcountBalance;
    bool MarkDelete = false;
};
enum enMenueScreen
{
    //Rename all enums by Crtl + R
    ShowClientListOption = 1,
    AddNewClientOption = 2,
    DeleteClientOption = 3,
    UpdateClientInfoOption = 4,
    FindClientOption = 5,
    ExitOption = 6
};

const string FileName = "Aly.txt";

void ShowMainMenue();

string ReadString(string Message)
{
    string String;
    cout << Message << endl;
    getline(cin, String);

    return String;
}

vector<string> SplitWordsInString(string S1, string delim)
{
    vector<string> vWrods;

    int pos = 0;
    string sWord;

    while ((pos = S1.find(delim)) != std::string::npos) // ' ' != no postion
    {
        sWord = S1.substr(0, pos);

        if (sWord != "")
        {
            vWrods.push_back(sWord);
        }

        S1.erase(0, (pos + delim.length())); // delim.length() => 1 | we writed it to .length delete it cuz may be delim 3 chars
    }
    if (S1 != "")
    {
        vWrods.push_back(S1);
    }

    return vWrods;
}

string ConvertRecordToLine(stClientData Client, string Separetor = "#__#")
{
    string ClientRecord = "";

    ClientRecord += Client.AccountNumber + Separetor;
    ClientRecord += Client.PinCode + Separetor;
    ClientRecord += Client.Name + Separetor;
    ClientRecord += Client.Phone + Separetor;
    ClientRecord += Client.AcountBalance;

    return ClientRecord;
}

stClientData ConvertLineToRecord(string Line, string Separetor = "#__#")
{
    stClientData Client;
    vector<string> SplitedRecord = SplitWordsInString(Line, Separetor);

    Client.AccountNumber = SplitedRecord[0];
    Client.PinCode = SplitedRecord[1];
    Client.Name = SplitedRecord[2];
    Client.Phone = SplitedRecord[3];
    Client.AcountBalance = SplitedRecord[4];

    return Client;
}

vector<stClientData> LoadClientDataFromFile(string FileName)
{
    vector<stClientData> vClients;

    fstream file;

    file.open(FileName, ios::in);

    if (file.is_open())
    {
        string line;
        stClientData Client;

        while (getline(file, line)) // Read "file" and store it into "line"
        {
            Client = ConvertLineToRecord(line, "#__#");

            vClients.push_back(Client);
        }
    }

    file.close();

    return vClients;
}

void ShowClientData(stClientData &Client)
{
    cout << Client.AccountNumber << "\t";
    cout << Client.PinCode << "\t";
    cout << Client.Name << "\t\t";
    cout << Client.Phone << "\t";
    cout << Client.AcountBalance;
}

void PrintClientData(stClientData Client)
{
    cout << "The Following are the client data : \n";

    cout << "------------------------------------\n";
    cout << "AcountNumber  : " << Client.AccountNumber << "\n";
    cout << "PinCode       : " << Client.PinCode << "\n";
    cout << "Name          : " << Client.Name << "\n";
    cout << "Phone         : " << Client.Phone << "\n";
    cout << "AcountBalance : " << Client.AcountBalance << "\n";
    cout << "------------------------------------\n";
}

stClientData ChangeClientRecord(string AccountNumber)
{
    stClientData Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode ?" << endl;
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name ?" << endl;
    getline(cin, Client.Name);

    cout << "Enter Phone ?" << endl;
    getline(cin, Client.Phone);

    cout << "Enter AcountBalance ?" << endl;
    getline(cin, Client.AcountBalance);

    return Client;
}

stClientData ReadClientData(string NewAccountNumber)
{
    stClientData Client;

    Client.AccountNumber = NewAccountNumber;
    Client.PinCode = ReadString("Enter Pin Cod ?");
    Client.Name = ReadString("Enter Name ?");
    Client.Phone = ReadString("Enter Phone ?");
    Client.AcountBalance = ReadString("Enter AcountBalance ?");

    return Client;
}

string JoinString(stClientData Client, string delim = "#__#")
{
    string LineRecord = "";

    LineRecord += Client.AccountNumber + delim;
    LineRecord += Client.PinCode + delim;
    LineRecord += Client.Name + delim;
    LineRecord += Client.Phone + delim;
    LineRecord += Client.AcountBalance;

    return LineRecord;
}

void AddRecordLineToFile(string FileName, string RecordLine)
{

    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        cout << "\nAdding Record Line To File ...\n";

        MyFile << RecordLine << endl;
    }

    MyFile.close();
}

void AddNewClient(vector<stClientData>& vClients, string &NewAccountNumber)
{
    stClientData Client = ReadClientData(NewAccountNumber);

    AddRecordLineToFile(FileName, JoinString(Client));
}

void SaveClientDataToFile(string FileName, vector<stClientData> &vClients)
{
    fstream file;

    file.open(FileName, ios::out); // out => Re-Write File

    if (file.is_open())
    {
        for (stClientData &C : vClients)
        {
            if (C.MarkDelete == false) //* Not have Delete Mrak
            {
                file << ConvertRecordToLine(C) << endl;
            }
        }
    }

    file.close();
}

bool FindClientByAccountNumber(string AccountNumberToFind, vector<stClientData> &vClients, stClientData &Client)
{

    for (stClientData C : vClients)
    {
        if (C.AccountNumber == AccountNumberToFind)
        {
            Client = C;
            return 1;
        }
    }

    return 0;
}

bool FindClientByAccountNumber(string AccountNumberToFind, vector<stClientData> &vClients)
{

    for (stClientData C : vClients)
    {
        if (C.AccountNumber == AccountNumberToFind)
            return true;
    }

    return false;
}

void MarkForDeleteByAccNum(string AccountNumber, vector<stClientData> &vClients)
{
    for (stClientData &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkDelete = true;
        }
    }
}

void PrintChooseTilt(string Title)
{
    cout << "------------------------------------\n";
    cout << "\t\t" << Title;
    cout << "\n------------------------------------\n\n";
}

void BackToMenue()
{
    
    cout << "Press any key to back to main menue!\n";
    system("pause>0");
    ShowMainMenue();
}

string CheckAccountNumber(vector<stClientData>& vClients)
{
    string AccountNumber;

    while (true)
    {
        cout << "Enter Account Number?\n";
        getline(cin >> ws, AccountNumber);


        if (FindClientByAccountNumber(AccountNumber, vClients))
        {
            cout << "\nClient with [" << AccountNumber << "] already exists, enter another number.\n\n";
            continue; // لو موجود، نطلب رقم جديد
        }

        // الرقم جديد وصحيح
        return AccountNumber;
    }
}

// Func 1 : Show Client List
void ShowClientsList(vector<stClientData> &vClients)
{
    printf("                Client List (%d) Clients\n", (int)vClients.size());
    cout << "\n---------------------------------------------\n";

    for (stClientData Client : vClients)
    {
        ShowClientData(Client);
        cout << endl;
    }

    cout << "\n---------------------------------------------\n";

}

// Func 2 : Add Clients List
void AddNewClients(vector<stClientData> &vClients)
{
    char AddMore = 'y';

    PrintChooseTilt("Add Clients List");

    do
    {
        cout << "Adding New Client:\n\n";

        string NewAccountNumber = CheckAccountNumber(vClients);

        AddNewClient(vClients, NewAccountNumber);
        
        vClients = LoadClientDataFromFile(FileName);

        cout << "Client Added Successfully to File , do u want add more ?\n";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

// Func 3 : Delete Client
void DeleteClientFromFileByAccountNumber(vector<stClientData> &vClients)
{
    stClientData ClientToDelete;

    PrintChooseTilt("Delete Client Screen");

    string AccountNumber = ReadString("Enter Account Number? ");

    if (FindClientByAccountNumber(AccountNumber, vClients, ClientToDelete))
    {
        cout << "\nThe following are client details :\n\n";
        PrintClientData(ClientToDelete);

        cout << "\n\nAre U Sure to Delete This Client (y/n) ??\n";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkForDeleteByAccNum(AccountNumber, vClients);
            SaveClientDataToFile(FileName, vClients);

            // Re-fresh vector
            vClients = LoadClientDataFromFile(FileName);

            cout << "\n\nClient deleted successfly.\n";
        }
    }
    else
    {
        cout << "Client With Account Number "
             << "(" << AccountNumber << ")"
             << " Not Found!\n";
    }

}

// Func 4: Update Client Info
void UpdateClientDataByAccountNumber(vector<stClientData> &vClients)
{
    stClientData Client;
    char Answer = 'n';

    PrintChooseTilt("Update Client Info Screen");

    string AccountNumber = ReadString("Enter Account Number ?");

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nThe following are client details :\n\n";
        PrintClientData(Client);

        cout << "\n\nAre U Sure to Update This Client ??\n";
        cin >> Answer;
        cin.ignore();

        // Update Client Info
        if (Answer == 'y' || Answer == 'Y')
        {
            for (stClientData &Client : vClients)
            {
                if (Client.AccountNumber == AccountNumber)
                {
                    Client = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientDataToFile(FileName, vClients);

            cout << "\n\nClient Updated successfly.\n";
        }
    }
    else
    {
        cout << "Client With Account Number "
             << "(" << AccountNumber << ")"
             << " Not Found!\n";
    }

}

// Func 5: Find Client
void FindClient(vector<stClientData> &vClients)
{
    stClientData Client;
    PrintChooseTilt("Find Client Screen");

    string AccountNumber = ReadString("Enter Account Number ?");

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientData(Client);
    }
    else
    {
        cout << "Client With Account Number "
             << "(" << AccountNumber << ")"
             << " Not Found!\n";
    }

}

// Fun 6 : Exit
void Exitt()
{
    cout << "----------------------------------------\n";
    cout << "           Program End :)               \n";
    cout << "----------------------------------------\n";
}

// Start App

void PerformMainMenueOption(short UserChoose)
{
    vector<stClientData> vClients = LoadClientDataFromFile(FileName);

    switch (UserChoose)
    {
    case enMenueScreen::ShowClientListOption:   
    {
        system("cls");
        ShowClientsList(vClients);
        BackToMenue();
        break;
    }
    case enMenueScreen::AddNewClientOption:
    {
        system("cls");
        AddNewClients(vClients);
        BackToMenue();
        break;
    }
    case enMenueScreen::DeleteClientOption:
    {
        system("cls");
        DeleteClientFromFileByAccountNumber(vClients);
        BackToMenue();
        break;
    }

    case enMenueScreen::UpdateClientInfoOption:
    {
        system("cls");
        UpdateClientDataByAccountNumber(vClients);
        BackToMenue();
        break;
    }

    case enMenueScreen::FindClientOption:
    {
        system("cls");
        FindClient(vClients);
        BackToMenue();
        break;
    }

    case enMenueScreen::ExitOption:
    {
        system("cls");
        Exitt();
        break;
    }

    default:
        system("cls");
        printf("Number (%d) Not Option of Our Menu!", UserChoose);
        BackToMenue();
        break;
    }
}

void ShowMainMenue()
{
    system("cls");

    cout << "================================================\n";
    cout << "               Main Menue Screen                \n";
    cout << "================================================\n";

    cout << "[1] " << "\t\tShow Client List.\n";
    cout << "[2] " << "\t\tAdd New Client.\n";
    cout << "[3] " << "\t\tDelete Client.\n";
    cout << "[4] " << "\t\tUpdate Client Info.\n";
    cout << "[5] " << "\t\tFind Client.\n";
    cout << "[6] " << "\t\tExit.\n";

    cout << "================================================\n";

    short UserChoose;
    cout << "Choose what do wanna to do? [1 to 6]? ";
    cin >> UserChoose;
    cin.ignore();

    PerformMainMenueOption(UserChoose);
}

int main()
{
   
    ShowMainMenue();

    system("pause>0");
    return 0;
}
