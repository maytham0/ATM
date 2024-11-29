#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
const string ClientFileName = "Client_data.txt";
const string* ptrAccount_Logined;
void Login();
struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
enum enTransaction_Menue_Screen {
	QuickWithdrow=1, eWithdrow = 2,eDposit = 3, eBalanc = 4, Logout = 5
};
enum enQuickWithdrow{e20=1,e50=2,e100=3,e200=4,e400=5,e500=6,e800=7,e1000=8};

vector<string> SplitString(string S1, string Delim) {
    vector<string> vString;
    short pos = 0;
    string sWord;
    // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos) {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "") {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "") {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") {
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); // cast string to double
    return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}
vector<sClient> LoadCleintsDataFromFile(string FileName) {
    vector<sClient> vClients;
    fstream MyFile0;

    MyFile0.open(FileName,ios::in); // read Mode
    if (MyFile0.is_open()) {
        string Line;
        sClient Client;

        while (getline(MyFile0, Line)) {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile0.close();
    }
    return vClients;
}
string ReadClientAccountNumber() {
    string AccountNumber = "";
    cout << "\nPlease enter Account Number? ";
    cin >> AccountNumber;
    return AccountNumber;
}
void PrintClientCard(sClient Client) {
    cout << "\nThe following are the client details:\n";
    cout << "\n----------------------------------------------\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n----------------------------------------------\n";
}
void SaveVectorToFileToUpdate(string FileName, vector <sClient>& vVectorContect)
{
    fstream MyFile0;
    MyFile0.open(FileName, ios::out);
    string DataLine;
    if (MyFile0.is_open())
    {

        for (sClient Line : vVectorContect)
        {
            DataLine = ConvertRecordToLine(Line);
            MyFile0 << DataLine << endl;
        }
        MyFile0.close();
    }
}
int Deposit(string FileName)
{
    char Answer = 'y';
    bool clientFound = false;
    int DepostNumber;
    vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
    sClient Client;
    string AccountNumber = *ptrAccount_Logined;
    for (sClient& Line : vClient) {
        if (AccountNumber == Line.AccountNumber)
        {
            PrintClientCard(Line);
            clientFound = true;
            cout << "\nPleas Enter Deposit amount? ";
            cin >> DepostNumber;
            cout << "\nAre you sure wont Deposit?(y,n)\n";
            cin >> Answer;
            if (tolower(Answer) == 'y') {

                Line.AccountBalance = Line.AccountBalance + DepostNumber;
                SaveVectorToFileToUpdate(FileName, vClient);
                return Line.AccountBalance;

            }

        }


    }
    if (!clientFound) { cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!"; }
    return -1;
}
int ReadNumberWithDrow()
{
    int WithdrowNumber = 0;
    cout << "\nPleas Enter Withdrow amount? ";
    cin >> WithdrowNumber;
    return WithdrowNumber;
}
int WithDrow(string FileName,int WithdrowNumber)

{
    bool clientFuond = false;
    char Answer = 'y';
    vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
   /// string AccountNumber = ReadClientAccountNumber();
    string AccountNumber = * ptrAccount_Logined;
    for (sClient& Line : vClient) {
        if (AccountNumber == Line.AccountNumber)
        {
            Line.AccountBalance;
            PrintClientCard(Line);
            clientFuond = true;
            if (WithdrowNumber > (Line.AccountBalance)) {
                cout << "Amount Exceeds the balanc,you can withdrow UP to :" << Line.AccountBalance << endl;
                cout << "Pleas Enter another amount ?";
                cin >> WithdrowNumber;
            }
            cout << "\nAre you sure wont Withdrow?(y,n)\n";
            cin >> Answer;
            if (tolower(Answer) == 'y') {

                Line.AccountBalance = Line.AccountBalance - WithdrowNumber;
                SaveVectorToFileToUpdate(FileName, vClient);
                return Line.AccountBalance;

            }

        }

    }
    if (!clientFuond) { cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!"; }
    return -1;

}
int QucikWithDrow(enQuickWithdrow Quick) {

    switch (Quick)
    {
    case enQuickWithdrow::e20:
        //
       return  WithDrow(ClientFileName, 20);
        break;
    case enQuickWithdrow::e50:
        //
       return  WithDrow(ClientFileName, 50);
        break;
    case enQuickWithdrow::e100:
     return    WithDrow(ClientFileName, 100);
        break;
    case enQuickWithdrow::e200:
        //
       return WithDrow(ClientFileName, 200);
        break;
    case enQuickWithdrow::e400:
        //
       return WithDrow(ClientFileName, 400);
        break;
    case enQuickWithdrow::e500:
        ///
       return  WithDrow(ClientFileName, 500);
        break;
    case enQuickWithdrow::e800:
     return   WithDrow(ClientFileName, 800);
        ///
        break;
    case enQuickWithdrow::e1000:
       return WithDrow(ClientFileName, 1000);
        //
        break; 

    default:
        cout << "!Wrong..";
        return 0;
        break;


    }

}
void ShowQuick()
{
    short Quick = 0;
    cout << "---------------------------\n";
    cout << "\t Quick withdrow  \n";
    cout << "---------------------------\n";
    cout << "1.20$\t2.50\n3.100$\t4.200$\n5.400$\t6.500\n$7.800$\t8.1000$\n";
    cout<< "---------------------------\n";
    cout << "Enter Quick withdro ";
    cin >> Quick;
    QucikWithDrow((enQuickWithdrow)Quick);
    
}
void Balanc(string FileName)
{

    vector<sClient> vClient = LoadCleintsDataFromFile(FileName);

    for (sClient& Line : vClient) {
        if (*ptrAccount_Logined == Line.AccountNumber)
        {
            cout << "balanc Is : " << Line.AccountBalance;
       }

    }


}

void Transactcion();
void GoBackToTransactionMenue()
{

	cout << "\n\nPress any key to go back to Transaction Menue...";
	system("pause>0");
	cout << endl;
	Transactcion();
}
short ReadNumberToPerfromTransctionMenueScreen()
{
	short N;

	cin >> N;
	return N;
}
void ShowDeposit()
{
	cout << "---------------------------\n";
	cout << "\t Deposit  \n";
	cout << "---------------------------\n";
	Deposit(ClientFileName);
}
void ShowWithdrow() {
	cout << "---------------------------\n";
	cout << "\t Deposit  \n";
	cout << "---------------------------\n";
	WithDrow(ClientFileName,ReadNumberWithDrow());
}

void PerfromTransctionMenueScreen(enTransaction_Menue_Screen TransactionMenue)
{

	switch (TransactionMenue)
	{
    case enTransaction_Menue_Screen::QuickWithdrow:
        system("cls");
        ShowQuick();
            GoBackToTransactionMenue();
        break;

	case enTransaction_Menue_Screen::eWithdrow:
		system("cls");
		//withdow
		//WithDrow(ClientsFileName);
		ShowWithdrow();
		GoBackToTransactionMenue();
		break;

	case enTransaction_Menue_Screen::eBalanc:
		system("cls");

        Balanc(ClientFileName);
		GoBackToTransactionMenue();
		break;

case enTransaction_Menue_Screen::eDposit:
		system("cls");
		//Deposit;
		//Deposit(ClientFileName);
		ShowDeposit();
		GoBackToTransactionMenue();
		break;
	case enTransaction_Menue_Screen::Logout:
		system("cls");
		//main Menue 
        Login();
		break;

	}
}
void Transactcion()
{
	system("cls");
	cout << "==========================================\n";
	cout << setw(32) << right << "Transaction Menue Screen\n";
	cout << "==========================================\n";
	cout << setw(16) << right << "[1]" << "Quick Withdrow.\n";
	cout << setw(16) << right << "[2]" << "Normal Withdrow.\n";
	cout << setw(16) << right << "[3]" << "Deposit.\n";
	cout << setw(16) << right << "[4]" << "Balanc.\n";
    cout << setw(16) << right << "[5]" << "Logout.\n";
	cout << "==========================================\n";

	cout << "Choose what do you want to do ? [1 to 5]?";
	PerfromTransctionMenueScreen((enTransaction_Menue_Screen)ReadNumberToPerfromTransctionMenueScreen());
}




string ReadAcountNumber()
{
	string AccountNumber;
	cout << "Entr Account Number ?";
	getline(cin >> ws, AccountNumber);
	return AccountNumber;
}
string ReadPinCode()
{
	string PinCode;
	cout << "Enter Pin Code ?";
    getline(cin >> ws, PinCode);
	return PinCode;
}

bool CheckAccountNumberPinCode(string AccountNumber ,string PinCode)
{
    vector<sClient>vClient = LoadCleintsDataFromFile(ClientFileName);
 
    for (sClient & Client : vClient)
    {
        if (AccountNumber == Client.AccountNumber && PinCode ==Client.PinCode)
        {
            
            return true;
            
        }
    }
    return false; 
}
void ReTry()
{
    system("cls");
    
    Login();
}
void Login()
{
    cout << "----------------------\n";
    cout << "\tLogin \n";
    cout << "----------------------\n";
    string AccountNumber = ReadAcountNumber();
    string PinCode = ReadPinCode();
   if( CheckAccountNumberPinCode(AccountNumber, PinCode))
    {
       ptrAccount_Logined = & AccountNumber;
      
       Transactcion();
    }
   else
   {
       cout << "Wrong Account Number Or Password Try agen\n";
       ReTry();
      
   }

}

int main()
{
    Login();
}