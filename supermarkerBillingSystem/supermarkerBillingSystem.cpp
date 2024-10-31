
#include <iostream>
#include<fstream>
#include<sstream>
#include<windows.h>
using namespace std;
  //Kodun tamamı bir fatura yönetim sistemi olarak çalışır; kullanıcı yeni ürünler ekleyebilir, ürünleri listeleyebilir ve toplam faturayı görebilir.
class Bill {
private:
	string Item;//fatura adı
	int Rate, Quantity;// birim ücret,adet miktarı 
public:
	Bill():Item(""),Rate(0),Quantity(0){}//fatura adı boş ,diğerleri 0

	void setItem(string item) {
		Item = item;
	}
	void setRate(int rate) {
		Rate = rate;
	}
	void setQuant(int quant) {
		Quantity = quant;
	}
	string getItem() {
		return Item;
	}
	int getQuant() {
		return Quantity;
	}
	int getRate() {
		return Rate;
	}

};
//addItem fonksiyonunun Türkçe açıklaması. Bu fonksiyon, kullanıcıya yeni fatura 
//öğeleri eklemek veya işlemi sonlandırmak için bir arayüz sağlar ve bu bilgileri bir metin
//dosyasına kaydeder
void addItem(Bill b) {
	bool close = false;//Bu değişken, kullanıcının işlemi sonlandırıp sonlandırmadığını belirlemek için kullanılır.
	while (!close) {
		int choice;
		cout << "\t1.Add." << endl; //Yeni bir fatura öğesi eklemek.
		cout << "\t2.close." << endl; //İşlemi sonlandırmak
		cout << "\tEnter Choice: ";
		cin >> choice;

		if (choice == 1) { // ürün adı, birim fiyatı ve miktarı alınır.
			system("cls");
			string item;
			int rate, quant;

			cout << "\tEnter Item Name: ";
			cin >> item;
			b.setItem(item);

			cout << "\tEnter Rate Of Item: ";
			cin >> rate;
			b.setRate(rate);

			cout << "\tEnter Quantity Of Item: ";
			cin >> quant;
			b.setQuant(quant);
			// bir metin dosyasına (Bill.txt) eklenir.
			ofstream out("D:/Bill.txt", ios::app);
			if (!out) {
				cout << "\tError: File Can't Open!" << endl;
			}
			else {
				out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl << endl;
			}
			out.close();
			cout << "\tItem Added Successfuly" << endl;
			Sleep(3000);
		}

		else if (choice == 2) {
			system("cls");
			close = true;
			cout << "\tBack To Main Menu!" << endl;
			Sleep(3000);
		}
	}
}



/*
Bu kod, bir fatura sistemi simüle eder.
Kullanıcı, bir alışveriş seansı sırasında farklı öğeleri ve miktarlarını ekleyebilir.
Fatura bilgileri bir metin dosyasında (Bill.txt) saklanır ve 
sonunda toplam fatura miktarı kullanıcıya gösterilir.
*/


void printBill() {
	system("cls"); //Konsol ekranı temizlenir
	int count = 0;
	bool close = false;
	while (!close) {
		system("cls");
		int choice;
		cout << "\t1.Add Bill." << endl;
		cout << "\t2.Close Session." << endl;
		cout << "\tEnter Choice: ";
		cin >> choice;

		if (choice == 1) {
			string item;
			int quant;
			cout << "\tEnter Item: ";
			cin >> item;
			cout << "\tEnter Quantity: ";
			cin >> quant;

			ifstream in("D:/Bill.txt");
			ofstream out("D:/Bill Temp.txt");

			string line;
			bool found = false;

			while (getline(in, line)) {
				stringstream ss;
				ss << line;
				string itemName;
				int itemRate, itemQuant;
				char delimiter;
				ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

				if (item == itemName) {
					found = true;
					if (quant <= itemQuant) {
						int amount = itemRate * quant;
						cout << "\t Item | Rate | Quantity | Amount" << endl;
						cout << "\t" << itemName << "\t " << itemRate << "\t " << quant << "\t " << amount << endl;
						int newQuant = itemQuant - quant;
						itemQuant = newQuant;
						count += amount;

						out << "\t" << itemName << " : " << itemRate << " : " << itemQuant << endl;
					}
					else {
						cout << "\tSorry, " << item << " Ended!" << endl;
					}
				}
				else {
					out << line << endl;
				}
			}
			if (!found) {
				cout << "\tItem Not Available!" << endl;
			}
			out.close();
			in.close();
			remove("D:/Bill.txt");
			rename("D:/Bill Temp.txt", "D:/Bill.txt");
		}
		else if (choice == 2) {
			close = true;
			cout << "\tCounting Total Bill" << endl;
		}
		Sleep(3000);
	}
	system("cls");
	cout << endl << endl;
	cout << "\t Total Bill ----------------- : " << count << endl << endl;
	cout << "\tThanks For Shopping!" << endl;
	Sleep(5000);
}



int main() {
	Bill b;

	bool exit = false;
	while (!exit) {
		system("cls");
		int val;

		cout << "\tWelcome To Super Market Billing System" << endl;
		cout << "\t**************************************" << endl;
		cout << "\t\t1.Add Item." << endl;
		cout << "\t\t2.Print Bill." << endl;
		cout << "\t\t3.Exit." << endl;
		cout << "\t\tEnter Choice: ";
		cin >> val;

		if (val == 1) {
			system("cls");
			addItem(b);
			Sleep(3000);
		}

		else if (val == 2) {
			printBill();
		}

		else if (val == 3) {
			system("cls");
			exit = true;
			cout << "\tGood Luck!" << endl;
			Sleep(3000);
		}
	}
}