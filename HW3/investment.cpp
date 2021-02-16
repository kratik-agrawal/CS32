//
//  investment.cpp
//  HW3
//
//  Created by Kratik Agrawal on 2/3/21.
//
#include <iostream>
#include <string>

using namespace std;

//Your declarations and implementations would go here
class Investment {
    public:
        Investment(string name, int price): m_name(name), m_purchasePrice(price){}
        string name() const { return m_name; }
        int purchasePrice() const { return m_purchasePrice; }
        virtual string description() const = 0;
        virtual bool fungible() const = 0;
        virtual ~Investment() {};
    
    private:
        string m_name;
        int m_purchasePrice;
    
};

class Painting: public Investment{
    public:
        Painting(string name, int price): Investment(name, price){}
        virtual string description() const { return "painting"; }
        virtual bool fungible() const { return false; }
        virtual ~Painting(){
            cout << "Destroying " << this->name() << ", a painting" << endl;
        }
};

class Stock: public Investment{
    public:
        Stock(string name, int price, string tick): Investment(name, price), m_ticker(tick){}
        virtual string description() const { return "stock trading as " + m_ticker;}
        virtual bool fungible() const { return true; }
        virtual ~Stock() {
            cout << "Destroying " << this->name() << ", a stock holding" << endl;
        }

    private:
        string m_ticker;
};

class House: public Investment{
    public:
        House(string name, int price): Investment(name, price){}
        virtual string description() const { return "house"; }
        virtual bool fungible() const { return false; }
        virtual ~House() {
            cout << "Destroying the house " << this->name() << endl;
        }
};


void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

int main()
{

    Investment* portfolio[4];
    portfolio[0] = new Painting("Salvator Mundi", 450300000);
      // Stock holdings have a name, value, and ticker symbol
    portfolio[1] = new Stock("Lyft", 50000, "LYFT");
    portfolio[2] = new Stock("GameStop", 10000, "GME");
    portfolio[3] = new House("4 Privet Drive", 660000);

    for (int k = 0; k < 4; k++)
        display(portfolio[k]);

      // Clean up the investments before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete portfolio[k];
}

