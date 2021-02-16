//
//  investment.cpp
//  HW3
//
//  Created by Kratik Agrawal on 2/3/21.
//


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

