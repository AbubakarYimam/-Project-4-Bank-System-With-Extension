#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const string FileName = "Clients.txt";

struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDlete = false;
};

enum enMenueOptons {
	ShowClient = 1, AddNewCliet = 2, DeleClient = 3, UpdateClient = 4, FindClient = 5, Transaction = 6, Exit = 7
};

vector<string> SplitingString(string Line, string Deli = "#//#") {
	vector <string> vClient;
	string sWord = "";
	short pos = 0;
	while ((pos = Line.find(Deli)) != std::string::npos) {
		sWord = Line.substr(0, pos);
		if (sWord != "") {
			vClient.push_back(sWord);
		}
		Line.erase(0, pos + Deli.length());
	}
	if (Line != "") {
		vClient.push_back(Line);
	}

	return vClient;
}

sClient ConvertLineToRecord(string Line) {
	sClient Client;
	vector<string> vClient = SplitingString(Line);
	Client.AccountNumber = vClient[0];
	Client.PinCode = vClient[1];
	Client.Name = vClient[2];
	Client.Phone = vClient[3];
	Client.AccountBalance = stod(vClient[4]);
	return Client;
}

vector<sClient> LoadClientFromFile() {
	vector<sClient>vsClient;
	fstream Myfile(FileName, ios::in);
	if (Myfile.is_open()) {
		string Line;
		sClient Client;
		while (getline(Myfile, Line)) {
			Client = ConvertLineToRecord(Line);
			vsClient.push_back(Client);
		}
		Myfile.close();
	}
	return vsClient;

}

// Show Client 
void ShowEachClient(sClient Client) {
	cout << "|" << setw(15) << left << Client.AccountNumber;
	cout << "|" << setw(15) << left << Client.PinCode;
	cout << "|" << setw(15) << left << Client.Name;
	cout << "|" << setw(15) << left << Client.Phone;
	cout << "|" << setw(15) << left << Client.AccountBalance;


}

void ShowClients() {
	vector<sClient>vsClient = LoadClientFromFile();
	cout << "\n\t\t\t Clients number(" << vsClient.size() << ").\n";
	cout << "\n=========================The Menue Of All Client=================================\n";
	cout << "|" << setw(15) << left << "Account Number";
	cout << "|" << setw(15) << left << "Pin Code";
	cout << "|" << setw(15) << left << "Name";
	cout << "|" << setw(15) << left << "Phone";
	cout << "|" << setw(15) << left << "Account Balance\n";
	cout << "----------------------------------------------------------------------------------\n";
	if (vsClient.size() != 0) {
		for (sClient s : vsClient) {
			ShowEachClient(s);
			cout << "\n";
		}
	}
	else {
		cout << "\n----------------No Client-----------------\n";
	}

}

// Add  New
bool isExisted(string Acc, vector<sClient> vsClient) {
	for (sClient s : vsClient) {
		if (s.AccountNumber == Acc) {
			return true;
		}
	}
	return false;
}

sClient askClientInfo() {
	sClient Client;
	vector<sClient>vsClient = LoadClientFromFile();
	cout << "Enter Acount Number ? ";
	getline(cin >> ws, Client.AccountNumber);
	while (isExisted(Client.AccountNumber, vsClient)) {
		cout << "\nThis Account Number (" << Client.AccountNumber << ")  Already Existed\n\n";
		cout << "Enter Acount Number ? ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter Pin Code ? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Acount Balance ? ";
	cin >> Client.AccountBalance;

	return Client;

}

string ConvertRecordToLine(sClient Client, string sepa = "#//#") {
	string Line = "";
	Line += Client.AccountNumber + sepa;
	Line += Client.PinCode + sepa;
	Line += Client.Name + sepa;
	Line += Client.Phone + sepa;
	Line += to_string(Client.AccountBalance);
	return Line;

}

void AddClients() {
	fstream MyFile(FileName, ios::app);
	if (MyFile.is_open()) {
		MyFile << ConvertRecordToLine(askClientInfo()) << endl;
	}
	MyFile.close();
}

void NewClientOption() {

	char is = 'y';
	do {
		system("cls");
		cout << "\n\t\t---------------------------------------\n";
		cout << "\t\t\tAdd New Client Option";
		cout << "\n\t\t---------------------------------------\n\n";
		AddClients();
		cout << "\nDo You Want To Add Another Client (y/n) ? ";
		cin >> is;
		cout << endl;
	} while (tolower(is) == 'y');

}

// Delete
bool isExistedForDelete(string Acc, vector<sClient> vsClient, sClient& Client) {
	for (sClient& s : vsClient) {
		if (s.AccountNumber == Acc) {
			Client = s;
			return true;
		}
	}
	return false;
}

void MarkTodelete(string Acc, vector<sClient>& vsClient) {
	for (sClient& s : vsClient) {
		if (s.AccountNumber == Acc) {
			s.MarkForDlete = true;

		}
	}

}

string ReadAccountNumber() {
	string Acc;
	cout << "Enter Account Number : ";
	cin >> Acc;
	return Acc;
}

void WriteToFile(vector<sClient> vsClient) {
	fstream MyFile(FileName, ios::out);
	for (sClient s : vsClient) {
		if (s.MarkForDlete == false) {
			MyFile << ConvertRecordToLine(s) << endl;
		}
	}
}

void PrintClient(sClient Client) {
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "Pin Code : " << Client.PinCode << endl;
	cout << "Name : " << Client.Name << endl;
	cout << "Phone : " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
}

void DeleteClient(vector<sClient>& vsClient) {

	sClient Client;
	char is = 'y';
	while (true) {
		string Acc = ReadAccountNumber();
		if (isExistedForDelete(Acc, vsClient, Client)) {
			PrintClient(Client);
			cout << "\nDo Want To Delete This Client (y/n) ?  ";
			cin >> is;
			if (is == 'y') {
				MarkTodelete(Acc, vsClient);
				WriteToFile(vsClient);
				cout << "\n\t\tDelete Sucssefully\n";
			}
			vsClient = LoadClientFromFile();
			break;

		}
		else {
			cout << "\n\nThe Account Number (" << Acc << ") Not Found !\n\n";
		}
	}
}

void DeleteOption() {

	vector<sClient> vsClient = LoadClientFromFile();

	char is = 'y';
	do {
		system("cls");
		cout << "\n\t\t---------------------------------------\n";
		cout << "\t\t\tDelete Option";
		cout << "\n\t\t---------------------------------------\n";
		DeleteClient(vsClient);
		cout << "Do You want To Delete Another Client (y/n) ? ";
		cin >> is;
	} while (is == 'y');

}

// Update
bool isExistedForUpdate(string Acc, vector<sClient>& vsClient, sClient& Client) {
	for (sClient& s : vsClient) {
		if (s.AccountNumber == Acc) {
			Client = s;

			return true;
		}
	}
	return false;
}

sClient UpdatClient() {
	sClient Client;
	cout << "Enter Client Number :";
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter Pin Code ? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	cout << "\n";
	return Client;

}

void Upadate(vector<sClient>& vsClient) {
	string Acc = ReadAccountNumber();
	sClient Client;
	char is = 'y';
	if (isExistedForUpdate(Acc, vsClient, Client)) {
		PrintClient(Client);
		cout << "\nDo You Want To Update The Client (y/n) ? ";
		cin >> is;
		if (is == 'y') {
			for (sClient& s : vsClient) {
				if (s.AccountNumber == Acc) {
					s = UpdatClient();
				}
			}
			WriteToFile(vsClient);
			cout << "\nUpdate Succesfully .\n";
		}
	}
	else {
		cout << "\nThe Account Number (" << Acc << ") Is Not Found !\n";
	}
}

void UpdateOption() {
	vector<sClient> vsClient = LoadClientFromFile();

	char is = 'y';
	while (is == 'y') {
		system("cls");
		cout << "\n\t\t--------------------------------------\n";
		cout << "\t\t\tUpdate Option";
		cout << "\n\t\t--------------------------------------\n";
		Upadate(vsClient);
		cout << "\nDo You Want To Update Another Client (y/n) ? ";
		cin >> is;
		cout << endl;
	}
}

// Find Client 
bool isExisted(string Acc, vector<sClient>& vsClient, sClient& Client) {
	for (sClient& s : vsClient) {
		if (s.AccountNumber == Acc) {
			Client = s;

			return true;
		}
	}
	return false;
}

void Find() {
	vector<sClient> vsClient = LoadClientFromFile();
	string Acc = ReadAccountNumber();
	sClient Client;
	if (isExisted(Acc, vsClient, Client)) {
		PrintClient(Client);
	}
	else {
		cout << "\nThe Account Number (" << Acc << ") Not Found!\n";
	}

}

void FindOption() {

	char is = 'y';
	do {
		system("cls");
		cout << "\n\t\t__________________________________________\n";
		cout << "\t\t\t Client Information";
		cout << "\n\t\t__________________________________________\n";
		Find();
		cout << "\ndo Yow Want To See Another Client (y/n) ?\n";
		cin >> is;
	} while (is == 'y');
}

// Exist 
void ExistOpton() {
	system("cls");
	cout << "\n\t\t__________________________________________\n";
	cout << "\t\t\t        THE END :-) ";
	cout << "\n\t\t__________________________________________\n";
}

// Transaction 
////////Deposite 
bool isExistedForTranscition(string Acc, vector<sClient>& vsClient, sClient& Client) {
	for (sClient& s : vsClient) {
		if (s.AccountNumber == Acc) {
			Client = s;

			return true;
		}
	}
	return false;
}

sClient AddMoney(sClient Client) {
	int num;
	cout << "Enter Amount : ";
	cin >> num;
	Client.AccountBalance += num;
	return Client;

}

void Deposite(vector<sClient>& vsClient) {
	string Acc = ReadAccountNumber();
	sClient Client;
	char is = 'y';
	if (isExistedForTranscition(Acc, vsClient, Client)) {
		PrintClient(Client);
		cout << "\nYou Want To Deposite Money (y/n) ? ";
		cin >> is;
		if (is=='y') {
			for (sClient& s : vsClient) {
				if (s.AccountNumber == Acc) {
					s = AddMoney(s);
					WriteToFile(vsClient);
					cout << "\n\tAdd Sucssefully!\n";
					break;
				}
			}
		}
	}
	else {
		cout << "\nThe Account Number (" << Acc << ") Not Find !\n";
	}

}

void DepostieOption() {

	vector<sClient> vsClient = LoadClientFromFile();
	char is = 'y';
	while (is == 'y') {
		system("cls");
		cout << "\n\t\t__________________________________________\n";
		cout << "\t\t\t        Deposite Option";
		cout << "\n\t\t__________________________________________\n";
		Deposite(vsClient);
		cout << "\nDo You Want To Add Money Again (y/n) ? ";
		cin >> is;
		cout << endl;
	}

}

///////Withdraw

sClient MinusMoney(sClient Client) {
	long int num=0;

	while (num==0) {
		cout << "\nEnter Amount : ";
		cin >> num;
		if (num <= Client.AccountBalance) {
			Client.AccountBalance -= num;
			break;
		}
		else {
			cout << "You Can Withdraw Upto " << Client.AccountBalance;
			break;
		}
	}
	return Client;
}

void WithDraw(vector<sClient>& vsClient) {
	string Acc = ReadAccountNumber();
	sClient Client;
	char is = 'y';
	if (isExistedForTranscition(Acc, vsClient, Client)) {
		PrintClient(Client);
		cout << "\nYou Want To WithDraw Money (y/n) ? ";
		cin >> is;
		if (is=='y') {
			for (sClient& s : vsClient) {
				if (s.AccountNumber == Acc) {
					s = MinusMoney(s);
					WriteToFile(vsClient);
					cout << "\n\tAdd Sucssefully!\n";
					break;
				}
			}
		}
	}
	else {
		cout << "\nThe Account Number (" << Acc << ") Not Find !\n";
	}

}

void WithdrawOption() {

	vector<sClient> vsClient = LoadClientFromFile();
	char is = 'y';
	while (is == 'y') {
		system("cls");
		cout << "\n\t\t__________________________________________\n";
		cout << "\t\t\t        Withdraw Option";
		cout << "\n\t\t__________________________________________\n";
		WithDraw(vsClient);
		cout << "\nDo You Want To Minus Money Again (y/n) ? ";
		cin >> is;
		cout << endl;
	}

}

//////// Total  Balance

void ShowEachClientBalance(sClient Client) {
	cout << "|" << setw(20) << left << Client.AccountNumber;
	cout << "|" << setw(20) << left << Client.Name;
	cout << "|" << setw(25) << left << Client.AccountBalance;


}

void ShowClientsBalance() {
	vector<sClient>vsClient = LoadClientFromFile();
	int Amount = 0;
	cout << "\n\t\t\t Clients number(" << vsClient.size() << ").\n";
	cout << "\n=========================The Menue Of All Client=================================\n";
	cout << "|" << setw(20) << left << "Account Number";
	cout << "|" << setw(20) << left << "Name";
	cout << "|" << setw(25) << left << "Account Balance";
	cout << "\n----------------------------------------------------------------------------------\n";
	if (vsClient.size() != 0) {
		for (sClient s : vsClient) {
			ShowEachClientBalance(s);
			Amount += s.AccountBalance;
			cout << "\n";
		}
		cout << "\n\t\t\t\tThe Total Amount =" << Amount;
	}
	else {
		cout << "\n----------------No Client-----------------\n";
	}

}

// The Main Page

short TheMainMenue() {
	short num;
	cout << "\n============================================================\n";
	cout << "                       Main Menue Screen";
	cout << "\n============================================================\n";
	cout << "             [1] Show Client List.\n";
	cout << "             [2] Add New Client.\n";
	cout << "             [3] Client Delete. \n";
	cout << "             [4] Update Client Info.\n";
	cout << "             [5] Find Client.\n";
	cout << "             [6] Transactions.\n";
	cout << "             [7] Exist.\n";
	cout << "\n============================================================\n";
	cout << "Choose what You Want To Do [1 to 6] ? ";
	cin >> num;
	return num;


}

short TranscationMenue() {
	short num;
	cout << "\n============================================================\n";
	cout << "                       Transaction Menue Screen";
	cout << "\n============================================================\n";
	cout << "             [1] Deposit.\n";
	cout << "             [2] WithDraw.\n";
	cout << "             [3] Total Balance. \n";
	cout << "             [4] Main Menue.\n";
	cout << "\n============================================================\n";
	cout << "Choose what You Want To Do [1 to 4] ? ";
	cin >> num;
	return num;

}

void TransactionOption(short num) {
	system("cls");
	switch (num) {
	case 1: {
		
		DepostieOption();
		system("cls");
		TransactionOption(TranscationMenue());
		break;
	}
	case 2: {
		WithdrawOption();
		system("cls");
		TransactionOption(TranscationMenue());
		break;
	}
	case 3: {
		ShowClientsBalance();
		char is = 'y';
		cout << "\nDo You Want To return To Transaction Menue(y/n) ?   ";
		cin >> is;
		if (is == 'y') {
			system("cls");
			TransactionOption(TranscationMenue());
		}

		break;
		
		
	}
	case 4: {
		system("cls");
		TheMainMenue();
		break;
	}
	}
}



void TheBigMenue(short num) {
	
	switch (num) {
	case 1: {
		system("cls");
		char is = 'y';
		ShowClients();
		cout << "\nDo You Want To return To Main Menue(y/n) ?   ";
		cin >> is;
		if (is == 'y') {
			system("cls");
			TheBigMenue(TheMainMenue());
		}
		
		break;
	}
	case 2: {
		system("cls");
		NewClientOption();
		system("cls");
		TheBigMenue(TheMainMenue());
		break;
	}
	case 3: {
		system("cls");
		DeleteOption();
		system("cls");
		TheBigMenue(TheMainMenue());
		break;
	}
	case 4: {
		system("cls");
		UpdateOption();
		system("cls");
		TheBigMenue(TheMainMenue());
		break;
	}
	case 5: {
		system("cls");
		FindOption();
		system("cls");
		TheBigMenue(TheMainMenue());
		break;
	}
	case 6: {
		system("cls");
		TransactionOption(TranscationMenue());
		TheBigMenue(TheMainMenue());
		break;
	}
	case 7: {
		ExistOpton();
		break;
	}

	}

}

int main() {
	TheBigMenue(TheMainMenue());

}
