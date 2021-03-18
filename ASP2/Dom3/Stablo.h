#ifndef _stablo_h_
#define _stablo_h_

#include <iostream>
#include <string>
using namespace std;

class Stablo  
{
protected:

      int m_brCvorova;
      int m_brKljuceva;

      Stablo() {
          m_brKljuceva = 0;
          m_brCvorova = 0;
      }


public:
    virtual ~Stablo() { }

    virtual bool umetni(const char *kljuc, const char *podaci) = 0;
	virtual bool obrisi(const char *kljuc) = 0;

    virtual string * dohvatiInfo(const char *kljuc) = 0;
	
    virtual int brojCvorova(){ return m_brCvorova; }
    virtual int brojKljuceva() { return m_brKljuceva; }

	virtual void obidji(ostream &it) = 0;
    virtual void ispisiStatistiku(ostream &it)
    {
        it << "Ukupno cvorova: " << brojCvorova() << endl;
        it << "Ukupno kljuceva: " << brojKljuceva() << endl;
    }
};

#endif
