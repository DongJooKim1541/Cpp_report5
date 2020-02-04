#include <iostream>
using namespace std;
const int NAME_LEN = 20;
const int ACC_MAX = 2;
class Account {
private:
	int id, balance;
	char* name;
public:
	Account();
	Account(int id1, int bal1, char* name1);
	Account(const Account& a);
	~Account();
	Account& operator=(Account& a);
	void SetId(int val);
	void SetBalance(int val);
	void SetName(char* name1);
	int GetId();
	int GetBalance();
	char* GetName();
	void ShowAll();
	void InMoney(int val);
	void OutMoney(int val);
};
Account::Account() {
	id = 0; balance = 0;
	name = new char[NAME_LEN];
	name[0] = NULL;
}
Account::Account(int id1, int bal1, char* name1) {
	id = id1; balance = bal1;
	name = new char[strlen(name1) + 1];
	strcpy_s(name, strlen(name1) + 1, name1);
}
Account::Account(const Account& a) {
	id = a.id; balance = a.balance;
	name = new char[strlen(a.name) + 1];
	strcpy_s(name, strlen(a.name) + 1, a.name);
}
Account::~Account() {
	if (name) {
		delete[] name;
		name = NULL;
	}
}
Account& Account::operator=(Account& a) {
	if (this != &a) {
		delete[] name;
		name = new char[strlen(a.name) + 1];
		strcpy_s(name, strlen(a.name) + 1, a.name);
		id = a.id; balance = a.balance;
	}
	return *this;
}
void Account::SetId(int val) {
	id = val;
}
void Account::SetBalance(int val) {
	balance = val;
}
void Account::SetName(char* name1) {
	strcpy_s(name, strlen(name1) + 1, name1);
}
int Account::GetId() {
	return id;
}
int Account::GetBalance() {
	return balance;
}
char* Account::GetName() {
	return name;
}
void Account::ShowAll() {
	cout << "계좌ID : " << id << endl;
	cout << "잔액 : " << balance << endl;
	cout << "이름 : " << name << endl;
}
void Account::InMoney(int val) {
	balance += val;
}
void Account::OutMoney(int val) {
	balance -= val;
}
Account* DyArr = new Account[ACC_MAX];
int index = 0;	//계좌 객체 개수 keeptrack
void PrintMenu();
void MakeAccount();
void Deposit();
void Withdraw();
void Inquire();
enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };
int main() {
	int choice;
	while (true) {
		PrintMenu();
		cout << "선택 : ";
		cin >> choice;
		//switch 이용할 것
		switch (choice) {
		case MAKE:
			MakeAccount();
			break;
		case DEPOSIT:
			Deposit();
			break;
		case WITHDRAW:
			Withdraw();
			break;
		case INQUIRE:
			Inquire();
			break;
		case EXIT:
			return 0;
		}
	}
	return 0;
}
void PrintMenu() {
	cout << "----------Menu----------" << endl;
	cout << "1(계좌개설)" << endl;
	cout << "2(입금)" << endl;
	cout << "3(출금)" << endl;
	cout << "4(전체조회)" << endl;
	cout << "5(프로그램 종료)" << endl;

}
void MakeAccount() {
	int id, bal;
	char name[NAME_LEN];
	//index가 ACC_MAX 이상이면 "계좌를 개설할 수 없음" 출력
	//사용자에게 id, balance, 이름을 물어서 index 번째 객체에 입력하고
	//index는 증가시킨다.(index++)
	if (index >= ACC_MAX) {
		cout << "계좌를 개설할 수 없음(계좌의 MAX 개수 초과)" << endl;
	}
	else {
		cout << "계좌개설을 위한 입력(계좌id, 잔액, 이름) : ";
		cin >> id >> bal >> name;
		DyArr[index].SetId(id);
		(DyArr + index)->SetBalance(bal);
		(*(DyArr + index)).SetName(name);
		index++;
	}
}
void Deposit() {
	//사용자에게 계좌 id와 입금액을 묻는다.
	//계좌 id의 존재 여부를 확인한다.
	//계좌가 존재하는 경우 입금하고 입금한 후에 현재 잔고를 cout한다.
	//존재하지 않는 경우 "존재하지 않는 ID 입니다"
	int id, bal;
	cout << "계좌 ID : ";
	cin >> id;
	int val = index;
	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) val = i;
	}
	if (val == index) {
		cout << "존재하지 않는 ID입니다." << endl;
	}
	else {
		cout << "입금액 : ";
		cin >> bal;
		DyArr[val].InMoney(bal);
		cout << "현재 잔고 : " << DyArr[val].GetBalance() << endl;
	}
}
void Withdraw() {
	//계좌 ID와 출금액을 묻는다
	//ID가 존재하는 경우 잔액과 출금액을 비교한다.
	//잔액이 출금액보다 클 경우에만 출금가능.
	//출금 후 현재 잔고를 보여준다.
	int id, bal;
	cout << "계좌 ID : ";
	cin >> id;
	int val = index;
	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) val = i;
	}
	if (val == index) {
		cout << "존재하지 않는 ID입니다." << endl;
	}
	else {
		cout << "출금액 : ";
		cin >> bal;
		if (bal <= DyArr[val].GetBalance()) {
			DyArr[val].OutMoney(bal);
			cout << "현재 잔고 : " << DyArr[val].GetBalance() << endl;
		}
		else {
			cout << "잔액이 부족합니다" << endl;
		}
	}
}
void Inquire() {
	for (int i = 0; i < index; i++) {
		(DyArr + i)->ShowAll();
	}
}