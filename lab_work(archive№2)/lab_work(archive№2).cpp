

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <thread>


using namespace std;

/* Devices hierarchy */
class Device
{

public:

	virtual ~Device() {}
	virtual void ShowInfo()
	{
		cout << "\t\tMerch info" << endl;
		cout << "Name: " << this->name << endl;
		cout << "Price: " << this->price << endl;

		cout << "= Technical info =" << endl;
		cout << "Voltage: " << this->power.voltage << " V" << endl;
		cout << "Amperage: " << this->power.amperage << " A" << endl;
		cout << "Frequency: " << this->power.frequency << " Hz" << endl;

	}
	virtual int GetPrice()
	{
		return price;
	}

protected:

	Device()
	{
		price = 0;
		name = "";

		power.voltage = 0;
		power.amperage = 0;
		power.frequency = 0;
	}
	
	class Electricity
	{
	public:

		Electricity()
		{

			this->voltage = 0;
			this->amperage = 0;
			this->frequency = 0;

		}
		~Electricity() {}

		int voltage;
		int amperage;
		int frequency;

	};

	double price;
	string name;
	Electricity power;

};

class Microwave : public Device
{
public:

	Microwave()
	{
		this->name = "Some microwave";
		this->price = 500 + (rand() % (2500 - 500 + 1));

		this->power.voltage = 2 + (rand() % (10 - 2 + 1));
		this->power.amperage = 10 + (rand() % (25 - 10 + 1));
		this->power.frequency = 25 + (rand() % (144 - 25 + 1));
	}
	~Microwave()override {}
	
};
class Fridge : public Device
{
public:

	Fridge()
	{
		this->name = "Some Fridge";
		this->price = 500 + (rand() % (2500 - 500 + 1));

		this->power.voltage = 2 + (rand() % (10 - 2 + 1));
		this->power.amperage = 10 + (rand() % (25 - 10 + 1));
		this->power.frequency = 25 + (rand() % (144 - 25 + 1));
	}
   ~Fridge()override {}

};
class TV : public Device
{
public:

	TV()
	{
		this->name = "Some TV";
		this->price = 500 + (rand() % (2500 - 500 + 1));

		this->power.voltage = 2 + (rand() % (10 - 2 + 1));
		this->power.amperage = 10 + (rand() % (25 - 10 + 1));
		this->power.frequency = 25 + (rand() % (144 - 25 + 1));
	}
   ~TV()override {}

};



/* Customer class */
class Customer
{
public:

	Customer()
	{
		this->id_gen++;
		this->id = id_gen;

		this->FullName = "customer" + to_string(this->id);
		this->Adress = "some adress of " + this->FullName;

		this->quantity_of_devices = 0;
		this->devices_bucket;
		this->sum_of_purchases = 0;

	}
	~Customer()
	{

	} 

	void ShowCustomerInfo()
	{

		cout << "=========================================================================================" << endl;

		cout << "Name: " << this->FullName << endl;
		cout << "Adress: " << this->Adress << endl;
		 
		cout << "Quantity of devices in the bucket "<< this->quantity_of_devices << endl;

		ShowTheSumOfAllPurchases();

		for (auto it = devices_bucket.begin();it != devices_bucket.end();++it)
		{
			(*it).get()->ShowInfo();
		}

		cout << "=========================================================================================" << endl;

		cout << endl << endl;
	}
	void ShowTheSumOfAllPurchases()
	{
		for (int i = 0; i < devices_bucket.size(); i++)
		{
			this->sum_of_purchases += devices_bucket[i].get()->GetPrice();
		}

		cout << "Sum of purchases " << sum_of_purchases << endl;
	}


	/* Add new element to the bucket*/
	void AddToBucket()
	{

		int choice;
		int howmany; // quantity of devices to buy


		cout << "How many purchases do you want to make, "<<this->FullName <<" ?"<< endl;
		cin >> howmany;

		cout << "=========================================================================================" << endl;

		for (int k = 0; k < howmany; k++) 
		{

			do 
			{
				cout << "What do you want to buy?..." << endl;
				cout << "1.Fridge\n2.TV\n3.Microwave oven" << endl;

				cin >> choice;


				if (choice == 1)
				{
					this->devices_bucket.push_back(make_unique<Fridge>());
					this->quantity_of_devices++;
				}

				else if (choice == 2)
				{
					this->devices_bucket.push_back(make_unique<TV>() );
					this->quantity_of_devices++;
				}

				else if (choice == 3)
				{
					this->devices_bucket.push_back(make_unique<Microwave>());
					this->quantity_of_devices++;
				}

				else
				{
					cout << "This product doesnt exist" << endl;
				}

			} while (choice > 3 || choice < 1); 
		}

		cout <<	"=========================================================================================" << endl;

	}
	

private:

	int id; 
	static int id_gen; 

	string FullName;
	string Adress;

	int quantity_of_devices; 
	vector <unique_ptr<Device>> devices_bucket; 

	double sum_of_purchases;
	
};
int Customer::id_gen = 0; // static variable to generate ID


void StartInteractions(list <Customer>& lst)
{

	bool isContinue = true;
	int choice;

	do
	{

		do
		{

			cout << "Choose the action ... " << endl;
			cout << "1. Start shopping\n2. Show shopping results\n3. End" << endl;

			cin >> choice;

			if (choice < 1 || choice > 3)
			{
				cout << "Enter correct action!" << endl;

				this_thread::sleep_for(2s);
				system("cls");
			}

			while (cin.fail())
			{

				cin.clear();
				cin.ignore();
				cin >> choice;
			}

			if (choice == 1)
			{
				for (auto it = lst.begin(); it != lst.end(); ++it)
				{
					(*it).AddToBucket();
					this_thread::sleep_for(2s);
					system("cls");
				}
			}
			else if (choice == 2)
			{
				for (auto it = lst.begin(); it != lst.end(); ++it)
				{
					(*it).ShowCustomerInfo();
				}
			}
			else if (choice == 3)
			{
				isContinue = false;
			}

		} while (choice < 1 || choice > 3 || cin.fail());

	} while (isContinue);
	
}


int main()
{

	setlocale(LC_ALL, "Rus");
	srand(time(NULL));


	list <Customer> customers(2); // just test list of customers

	StartInteractions(customers);
	

	return 0;
}


