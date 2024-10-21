// NetRom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

// Make car class

class Customer {
private:
	int Nr; // Client No: 1987
	int Age; // Age: 21
	string Email; // tommy.vercetti@vicecity.com
	string clientType;

	string Surname; // Vercetti
	string Name; // Tommy
public:
	Customer(string Surname, string Name, string Email, string clientType, int Nr, int Age) {
		this->Surname = Surname;
		this->Name = Name;
		this->Email = Email;
		this->clientType = clientType;

		this->Nr = Nr;
		this->Age = Age;
	}
};

class Car {
public:
	string NumberPlate; // DJ 30 ROM
	string Brand; // Mercedes
	string Model; // 450 SEL
	int Year; // 1987

	int Mileage; // 200,312 km
	int PriceFromCatalog; // $50,000
	string RegistrationCountry; // In the United States: Florida, California, etc
								// Elsewhere: RO, DE, FR, GB, etc.
	string PreviousVisit;

	Car(string NumberPlate, string Brand, string Model, int Year, int Mileage, int PriceFromCatalog, string RegistrationCountry, string PreviousVisit) {
		this->NumberPlate = NumberPlate;
		this->Brand = Brand;
		this->Model = Model;
		this->Year = Year;
		this->Mileage = Mileage;
		this->PriceFromCatalog = PriceFromCatalog;
		this->RegistrationCountry = RegistrationCountry;
		this->PreviousVisit = PreviousVisit;
	}
};

class Part {
protected:
	float Price; // $100
	float Discount; // 20.3%
public:
	string Description; // A great OEM engine, for a great car
	Part(string Description, float Price, float Discount) {
		this->Description = Description;
		this->Price = Price;
		this->Discount = Discount;
	}

	virtual float calculate_total() {
		return Price - (Price * (Discount / 100));
	}

	// Virtual destructor
	virtual ~Part() = default;
};

class Order {
	string Number; // order number, can be LA-2013
	Car Vehicle; // car class
	Customer Client; // customer
	string Service_Desc;
	string Mechanic_Remarks;
	vector<Part*> Parts;

public:
	Order(string Number, string Service_Desc, string Mechanic_Remarks, Car Vehicle, Customer Client)
		: Number(Number), Service_Desc(Service_Desc), Mechanic_Remarks(Mechanic_Remarks), Vehicle(Vehicle), Client(Client) {
		this->Number = Number;
		this->Service_Desc = Service_Desc;
		this->Mechanic_Remarks = Mechanic_Remarks;
		this->Vehicle = Vehicle;
		this->Client = Client;
	}

	// Method to add parts to the work order
	void addPart(Part* part) {
		Parts.push_back(part);
	}

	// Method to calculate total cost
	float calculate_total() const {
		float sum = 0.0;

		for (int i = 0; i < Parts.size(); i++) {
			sum += Parts[i]->calculate_total();
		}
		return sum;
	}

	~Order() {
		for (Part* part : Parts) {
			delete part;
		}
	}
};

class PTC : public Part { // That's not a part, it's a technical check;
protected:
	int Mileage; // for mileage of let's say 150,000 km
public:
	PTC(string Description, float Price, float Discount, int Mileage) : Part(Description, Price, Discount) {
		this->Mileage = Mileage;
	}
};

class Recycled : public Part { // Basically part + recycle;
protected:
	float RecyclingPrice; // for example $100.2
public:
	Recycled(string Description, float Price, float Discount, float RecyclingPrice) : Part(Description, Price, Discount) {
		this->RecyclingPrice = RecyclingPrice;
	}

	float calculate_total() override {
		return Part::calculate_total() + RecyclingPrice;
	}
};

class Standard : public Part { // Standard, non-recycled part; p.s: it can be quite pricey
protected:
	int Quantity; // for mileage of let's say 150,000 km
	float LabourCost; // for example $150.2
public:
	Standard(string Description, float Price, float Discount, int Quantity, float LabourCost) : Part(Description, Price, Discount) {
		this->Quantity = Quantity;
		this->LabourCost = LabourCost;
	}

	float calculate_total() override {
		return (Part::calculate_total() * Quantity) + LabourCost;
	}
};

int main() {

	vector<Part*> parts = {
		new Standard("Windshield", 450.00, 20, 1, 150.00),
		new Recycled("OEM Battery 105Ah", 220.00, 13.00, 15.00),
		new PTC("Periodical Technical Check", 100.00, 0, 23400)
	};

	Car car("FJ-66-75", "Audi", "A2 1.4 Pro Line", 2003, 23400, 53500, "NL", "5/6/2021");
	Customer customer("Phone", "Debbie Manley", "debby.manley@gmail.com", "Owner", 221, 47);

	Order order(
		"WO-0410",
		"We need to replace the battery and change the windshield.",
		"The engine oil + filters will need to be replaced in 2000 KM. The front left door has a big chip that will need a spot repaint job.",
		car,
		customer
	);

	for (int i = 0; i < parts.size(); i++) {
		order.addPart(parts[i]);
	}

	cout << order.calculate_total();

	// For a responsible memory usage, we clean up the allocated parts afterwards
	/*for (Part* part : parts) {
		delete part;
	}*/
}