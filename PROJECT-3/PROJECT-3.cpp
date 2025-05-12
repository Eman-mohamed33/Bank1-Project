#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;
struct ClientData
{
    string Account_Number;
    string PinCode;
    string Client_Name;
    string PhoneNumber;
    long double AccountBalance;
    bool markfordelete = false;
};
const string filename = "ClientsDATA.txt";
void Main_Menu_Screen();
vector <string> Split(string STRING, string delim)
{
    vector <string> VECTOR;

    int pos = 0;
    string sword;
    while ((pos = STRING.find(delim)) != std::string::npos)
    {
        sword = STRING.substr(0, pos);
        if (sword != "")
        {
            VECTOR.push_back(sword);
        }
        STRING.erase(0, pos + delim.length());
    }
    if (STRING != "")
    {
        VECTOR.push_back(STRING);
    }

    return VECTOR;
}
ClientData Client_Record(string str)
{
    ClientData CD;
    vector <string> vstruct = Split(str, "#//#");
    CD.Account_Number = vstruct[0];
    CD.PinCode = vstruct[1];
    CD.Client_Name = vstruct[2];
    CD.PhoneNumber = vstruct[3];
    CD.AccountBalance = stod(vstruct[4]);
    return CD;
}
void SHOWDATA(ClientData CD)
{
    cout << "|" << left << setw(18) << CD.Account_Number << "| " << left << left << setw(11) << CD.PinCode << "| " << left << setw(48) << CD.Client_Name << " | " << left << setw(10) << CD.PhoneNumber << "|" << left << setw(12) << CD.AccountBalance << endl;

}
vector <ClientData> PrintDataFromFile(string filename)
{
    vector <ClientData> VClient;
    ClientData CD;
    fstream File;
    File.open(filename, ios::in);
    if (File.is_open())
    {
        string line;
        while (getline(File, line))
        {
            CD = Client_Record(line);
            VClient.push_back(CD);

        }
        File.close();
    }
    return VClient;
}
void ShowClientList(string fileName)
{
    system("cls");
    system("color 0f");
    vector <ClientData> VClient = PrintDataFromFile(fileName);
    cout << endl;
    cout << "                                          Client List (" << VClient.size() << ") Client(s).                                                 " << endl;
    cout << "_____________________________________________________________________________________________________________________" << endl;
    cout << endl;
    cout << setw(20) << "|  Account Number  |" << setw(12) << "  Pin Code  |" << setw(30) << "  Client Name                                     |" << setw(12) << " Phone     |" << setw(12) << " Balance  " << endl;
    cout << "_____________________________________________________________________________________________________________________" << endl;
    cout << endl;
    for (ClientData& CD : VClient)
    {
        SHOWDATA(CD);
    }
    cout << "_____________________________________________________________________________________________________________________" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    
    
}


bool ClientExisetByAccountNumber( string UserAccountNumber)
{
    vector <ClientData> vClient;
    
    fstream File;
    File.open(filename, ios::in);
    if (File.is_open())
    {
        ClientData CD;
        string line;
        while (getline(File, line))
        {
            CD = Client_Record(line);
            if (CD.Account_Number==UserAccountNumber)
            {
                File.close();
                return true;
            }
            vClient.push_back(CD);

        }
        File.close();

    }
    return false;
}
ClientData Read_ClientData(string filename)
{
    
    cout << endl;
    cout << "----------------------------------" << endl;
    cout << "      Add New Clients Screen      " << endl;
    cout << "----------------------------------" << endl;
    cout << "Adding New Client : " << endl;
    cout << endl;
    ClientData CD;
    cout << "Enter Account Number? ";
    getline(cin >> ws, CD.Account_Number);
    
    while (ClientExisetByAccountNumber(CD.Account_Number))
    {
        cout << "Client with [" << CD.Account_Number << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, CD.Account_Number);
    }
            

 
   
    

    cout << "Enter PinCode? ";
    getline(cin, CD.PinCode);

    cout << "Enter Name? ";
    getline(cin, CD.Client_Name);

    cout << "Enter Phone? ";
    getline(cin, CD.PhoneNumber);

    cout << "Enter AccountBalance? ";
    cin >> CD.AccountBalance;

    return CD;
}
string ClientRecord(ClientData CD, string Delim)
{

    string RECORD = "";
    RECORD = CD.Account_Number + Delim;
    RECORD = RECORD + CD.PinCode + Delim;
    RECORD = RECORD + CD.Client_Name + Delim;
    RECORD = RECORD + CD.PhoneNumber + Delim;
    RECORD = RECORD + to_string(CD.AccountBalance);
    return RECORD;

}
void LineAddedToFile(ClientData CD,string filename)
{
    fstream ClientsDataFile;
    ClientsDataFile.open(filename, ios::out | ios::app);
    if (ClientsDataFile.is_open())
    {
        ClientsDataFile << ClientRecord(CD, "#//#") << endl;
        ClientsDataFile.close();
    }
}
void AddingNewClientScreen(string filename)
{
    ClientData CD;
    
    char Op;
    do
    {

        system("cls");
        system("color 0f");
        CD = Read_ClientData(CD.Account_Number);
        LineAddedToFile(CD, filename);
        cout << endl;
        cout << "Client Added Successfully, Do you want to add more Clients ? [yes(Y/y) Or No] ?" << endl;
        cin >> Op;
        cout << endl;
        cout << endl;
        cout << endl;
    } while (Op == 'y' || Op == 'Y');
    cout << endl;
    cout << endl;

}



bool SearchClientData(vector <ClientData> vClients, string userAccount, ClientData& cC)
{
    for (ClientData& client : vClients)
    {
        if (userAccount == client.Account_Number)
        {

            cC = client;
            return true;

        }

    }
    return false;


}
void ClientDetails(ClientData cC)
{
    cout << "The Following are The Client Details : " << endl;
    cout << "-----------------------------------" << endl;
    cout << "Account Number : " << cC.Account_Number << endl;
    cout << "Pin Code       : " << cC.PinCode << endl;
    cout << "Name           : " << cC.Client_Name << endl;
    cout << "Phone          : " << cC.PhoneNumber << endl;
    cout << "Account Balance: " << cC.AccountBalance << endl;
    cout << "-----------------------------------" << endl;

}

bool MarkForDelete(string AccountNumber, vector <ClientData>& VClient)
{
    for (ClientData& vclient : VClient)
    {
        if (AccountNumber == vclient.Account_Number)
        {
            vclient.markfordelete = true;
            return true;
        }
    }
    return false;
}
vector <ClientData> saveVectorTofile(string filename, vector <ClientData> VClient)
{
    fstream FILE;
    FILE.open(filename, ios::out);
    string data = "";
    if (FILE.is_open())
    {

        for (ClientData& C : VClient)
        {
            if (C.markfordelete == false)
            {
                data = ClientRecord(C, "#//#");
                FILE << data << endl;
            }
        }
        FILE.close();
    }
    return VClient;
}
void CheckAccountNumberToDeleteClientData(vector <ClientData> vClients,string filename)
{
    system("cls");
    system("color 0f");
    ClientData cC;
    string accnum;
    cout << endl;
    cout << "----------------------------------" << endl;
    cout << "       Delete Client Screen       " << endl;
    cout << "----------------------------------" << endl;
    cout << endl;
    cout << "Please Enter AccountNumber ?  ";
    getline(cin >> ws, accnum);
    cout << endl;
    char UserInput = 'n';
    if (SearchClientData(vClients, accnum, cC))
    {
        ClientDetails(cC);
        cout << endl;
        cout << "Are You Sure You Want To Delete This Client ?  y/n ? ";
        cin >> UserInput;
        if (UserInput == 'Y' || UserInput == 'y')
        {

            MarkForDelete(accnum, vClients);
            saveVectorTofile(filename, vClients);
            vClients = PrintDataFromFile(filename);
            cout << endl;
            cout << "Client Deleted Successfully." << endl;
            // return true;
        }
        // return false;
       
    }
    else
    {
        cout << "Client With Account Number (" << accnum << ") Not Found!" << endl;
       
    }
    cout << endl;
    cout << endl;

}


ClientData ReadClientData2(string AccountNumber)
{

    cout << endl;
    ClientData CD;
    CD.Account_Number = AccountNumber;

    cout << "Enter PinCode? ";
    getline(cin >> ws, CD.PinCode);

    cout << "Enter Name? ";
    getline(cin, CD.Client_Name);

    cout << "Enter Phone? ";
    getline(cin, CD.PhoneNumber);

    cout << "Enter AccountBalance? ";
    cin >> CD.AccountBalance;

    return CD;
}
void UpdateUsingAccountNumber(vector <ClientData> &VClient,string filename)
{
    system("cls");
    system("color 0f");
    ClientData cC;
    string accnum;
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << "     Update Client Info Screen     " << endl;
    cout << "-----------------------------------" << endl;
    cout << "Please Enter AccountNumber ?  ";
    getline(cin >> ws, accnum);
    cout << endl;
    char UserInput = 'n';
    if (SearchClientData(VClient, accnum, cC))
    {
        ClientDetails(cC);
        cout << endl;
        cout << "Are You Sure You Want To Update This Client ?  y/n ? ";
        cin >> UserInput;
        if (UserInput == 'Y' || UserInput == 'y')
        {

            for (ClientData& vClient : VClient)
            {
                if (vClient.Account_Number == accnum)
                {
                    vClient = ReadClientData2(accnum);
                    break;
                }
            }

            saveVectorTofile(filename, VClient);
            VClient = PrintDataFromFile(filename);
            cout << endl;
            cout << "Client Updated Successfully." << endl;
            cout << endl;

           
        }


    }
    else
    {
        cout << "Client With Account Number (" << accnum << ") Not Found!" << endl;
       
    }


}

void FindClientUsingAccountNumber(string filename, vector <ClientData> vClients)
{
    system("cls");
    system("color 0f");
    string accnum;
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << "         Find Client Screen        " << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;
    cout << "Please Enter AccountNumber ?  ";
    getline(cin >> ws, accnum);
    cout << endl;
    ClientData cC;
    if (SearchClientData(vClients, accnum, cC))
    {
        ClientDetails(cC);
        cout << endl;
        
    }
    else
    {
        cout << "Client With Account Number (" << accnum << ") Not Found!" << endl;
    }
}

void EndProgram()
{
    system("cls");
    system("color 0f");
    cout << endl;
    cout << "-------------------------------------" << endl;
    cout << "          Program Ends :-)           " << endl;
    cout << "-------------------------------------" << endl;
}

void BackToMainMenu()
{
    cout << "Press Any Key To Go Back To Main Menu...";
    system("pause>0");
    Main_Menu_Screen();
}
void Main_Menu_Screen()
{
    system("cls");
    system("color 0f");
    
    vector <ClientData> VClient = PrintDataFromFile(filename);
    short UserChoice;
    cout << "=========================================" << endl;
    cout << "            Main Menu Screen             " << endl;
    cout << "=========================================" << endl;
    cout << "        [1] Show Client List.          " << endl;
    cout << "        [2] Add New Client.            " << endl;
    cout << "        [3] Delete Client.             " << endl;
    cout << "        [4] Update Client Info.        " << endl;
    cout << "        [5] Find Client.               " << endl;
    cout << "        [6] Exit                       " << endl;
    cout << "=========================================" << endl;
    cout << "Choose What Do You Want To Do ? [ 1 To 6 ] :  ";
    cin >> UserChoice;
    switch (UserChoice)
    {
    case 1:
        ShowClientList(filename);
       /* cout << "Press Any Key To Go Back To Main Menu...";
        system("pause>0");
        return Main_Menu_Screen();*/
        BackToMainMenu();
        break;
    case 2:
        AddingNewClientScreen(filename);
        cout << "Press Any Key To Go Back To Main Menu...";
        system("pause>0");
        return Main_Menu_Screen();
    case 3:
        CheckAccountNumberToDeleteClientData(VClient, filename);
        cout << "Press Any Key To Go Back To Main Menu...";
        system("pause>0");
        return Main_Menu_Screen();
    case 4:
        UpdateUsingAccountNumber(VClient, filename);
        cout << "Press Any Key To Go Back To Main Menu...";
        system("pause>0");
        return Main_Menu_Screen();
    case 5:
        FindClientUsingAccountNumber(filename, VClient);
        cout << "Press Any Key To Go Back To Main Menu...";
        system("pause>0");
        return Main_Menu_Screen();
    case 6:
        EndProgram();
        break;
    }  
}

int main()
{
    Main_Menu_Screen();
    

}

