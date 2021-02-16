//
//  Flatulan.h
//  Proj1
//
//  Created by Kratik Agrawal on 1/8/21.
//

#ifndef Flatulan_h
#define Flatulan_h

class City;  // This is needed to let the compiler know that City is a
             // type name, since it's mentioned in the Flatulan declaration.

class Flatulan
{
  public:
        // Constructor
    Flatulan(City* cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();
    bool possiblyGetConverted();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
};


#endif /* Flatulan_h */
