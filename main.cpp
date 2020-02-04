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
	cout << "����ID : " << id << endl;
	cout << "�ܾ� : " << balance << endl;
	cout << "�̸� : " << name << endl;
}
void Account::InMoney(int val) {
	balance += val;
}
void Account::OutMoney(int val) {
	balance -= val;
}
Account* DyArr = new Account[ACC_MAX];
int index = 0;	//���� ��ü ���� keeptrack
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
		cout << "���� : ";
		cin >> choice;
		//switch �̿��� ��
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
	cout << "1(���°���)" << endl;
	cout << "2(�Ա�)" << endl;
	cout << "3(���)" << endl;
	cout << "4(��ü��ȸ)" << endl;
	cout << "5(���α׷� ����)" << endl;

}
void MakeAccount() {
	int id, bal;
	char name[NAME_LEN];
	//index�� ACC_MAX �̻��̸� "���¸� ������ �� ����" ���
	//����ڿ��� id, balance, �̸��� ��� index ��° ��ü�� �Է��ϰ�
	//index�� ������Ų��.(index++)
	if (index >= ACC_MAX) {
		cout << "���¸� ������ �� ����(������ MAX ���� �ʰ�)" << endl;
	}
	else {
		cout << "���°����� ���� �Է�(����id, �ܾ�, �̸�) : ";
		cin >> id >> bal >> name;
		DyArr[index].SetId(id);
		(DyArr + index)->SetBalance(bal);
		(*(DyArr + index)).SetName(name);
		index++;
	}
}
void Deposit() {
	//����ڿ��� ���� id�� �Աݾ��� ���´�.
	//���� id�� ���� ���θ� Ȯ���Ѵ�.
	//���°� �����ϴ� ��� �Ա��ϰ� �Ա��� �Ŀ� ���� �ܰ� cout�Ѵ�.
	//�������� �ʴ� ��� "�������� �ʴ� ID �Դϴ�"
	int id, bal;
	cout << "���� ID : ";
	cin >> id;
	int val = index;
	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) val = i;
	}
	if (val == index) {
		cout << "�������� �ʴ� ID�Դϴ�." << endl;
	}
	else {
		cout << "�Աݾ� : ";
		cin >> bal;
		DyArr[val].InMoney(bal);
		cout << "���� �ܰ� : " << DyArr[val].GetBalance() << endl;
	}
}
void Withdraw() {
	//���� ID�� ��ݾ��� ���´�
	//ID�� �����ϴ� ��� �ܾװ� ��ݾ��� ���Ѵ�.
	//�ܾ��� ��ݾ׺��� Ŭ ��쿡�� ��ݰ���.
	//��� �� ���� �ܰ� �����ش�.
	int id, bal;
	cout << "���� ID : ";
	cin >> id;
	int val = index;
	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) val = i;
	}
	if (val == index) {
		cout << "�������� �ʴ� ID�Դϴ�." << endl;
	}
	else {
		cout << "��ݾ� : ";
		cin >> bal;
		if (bal <= DyArr[val].GetBalance()) {
			DyArr[val].OutMoney(bal);
			cout << "���� �ܰ� : " << DyArr[val].GetBalance() << endl;
		}
		else {
			cout << "�ܾ��� �����մϴ�" << endl;
		}
	}
}
void Inquire() {
	for (int i = 0; i < index; i++) {
		(DyArr + i)->ShowAll();
	}
}