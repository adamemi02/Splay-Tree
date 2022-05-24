//Adam Emanuel

#include <iostream>
using namespace std;

struct Nod {
    Nod *tata;
    Nod *stanga;
    Nod *dreapta;
    int data;
};

typedef Nod *PointerNod;



class SplayTree {
public:
    PointerNod radacina;
    PointerNod findnod(PointerNod Nod, int valoare) {
        if (Nod == nullptr || valoare == Nod->data) {
            return Nod;
        }

        if (valoare < Nod->data) {
            return findnod(Nod->stanga, valoare);
        }
        else
        {return findnod(Nod->dreapta, valoare);}
    }

    void stergere(PointerNod Nod, int valoare) {
        PointerNod x = nullptr;
        PointerNod t, s;
        while (Nod != nullptr){
            if (Nod->data == valoare) {
                x = Nod;
            }

            if (Nod->data <= valoare) {
                Nod = Nod->dreapta;
            } else {
                Nod = Nod->stanga;
            }
        }

        if (x == nullptr) {
            cout<<"Valoarea data nu este in arbore\n";
            return;
        }
        split(x, s, t);
        if (s->stanga){
            s->stanga->tata = nullptr;
        }
        radacina = join(s->stanga, t);
        delete(s);
        s = nullptr;
    }

    void afisare(PointerNod radacina, int depth, int pos) {
        if (radacina != nullptr) {
            if(radacina->tata == nullptr)
                cout<<"Radacina:";
            else if(pos == false)
                cout << "stanga(" << depth << "):";
            else cout << "dreapta(" << depth << "):";
            cout<<radacina->data<<"\n";

            afisare(radacina->stanga, depth + 1, false);
            afisare(radacina->dreapta, depth + 1, true);
            cout << "back\n";
        }

    }

    
    void RotatieStanga(PointerNod x) {
        PointerNod y = x->dreapta;
        x->dreapta = y->stanga;
        if (y->stanga != nullptr) {
            y->stanga->tata = x;
        }
        y->tata = x->tata;
        if (x->tata == nullptr) {
            this->radacina = y;
        } else if (x == x->tata->stanga) {
            x->tata->stanga = y;
        } else {
            x->tata->dreapta = y;
        }
        y->stanga = x;
        x->tata = y;
    }

    
    void RotatieDreapta(PointerNod x) {
        PointerNod y = x->stanga;
        x->stanga = y->dreapta;
        if (y->dreapta != nullptr) {
            y->dreapta->tata = x;
        }
        y->tata = x->tata;
        if (x->tata == nullptr) {
            this->radacina = y;
        } else if (x == x->tata->dreapta) {
            x->tata->dreapta = y;
        } else {
            x->tata->stanga = y;
        }
        y->dreapta = x;
        x->tata = y;
    }

    
    void splay(PointerNod x) {
        while (x->tata) {
            if (!x->tata->tata) {
                if (x == x->tata->stanga) {
                    
                    RotatieDreapta(x->tata);
                } else {
                    RotatieStanga(x->tata);
                }
            } else if (x == x->tata->stanga && x->tata == x->tata->tata->stanga) {
                
                RotatieDreapta(x->tata->tata);
                RotatieDreapta(x->tata);
            } else if (x == x->tata->dreapta && x->tata == x->tata->tata->dreapta) {
                RotatieStanga(x->tata->tata);
                RotatieStanga(x->tata);
            } else if (x == x->tata->dreapta && x->tata == x->tata->tata->stanga) {
                RotatieStanga(x->tata);
                RotatieDreapta(x->tata);
            } else {
                RotatieDreapta(x->tata);
                RotatieStanga(x->tata);
            }
        }
    }
    
    PointerNod join(PointerNod s, PointerNod t){
        if (!s) {
            return t;
        }

        if (!t) {
            return s;
        }
        PointerNod x = maxim(s);
        splay(x);
        x->dreapta = t;
        t->tata = x;
        return x;
    }


    void split(PointerNod &x, PointerNod &s, PointerNod &t) {
        splay(x);
        if (x->dreapta) {
            t = x->dreapta;
            t->tata = nullptr;
        } else {
            t = nullptr;
        }
        s = x;
        s->dreapta = nullptr;
        x = nullptr;
    }
    SplayTree() {
        radacina = nullptr;
    }


    PointerNod findnodfinal(int k) {
        PointerNod x = findnod(this->radacina, k);
        if (x!= nullptr) {
            splay(x);
            cout<<"Am gasit nodul\n";
        }
        else{
            cout<<"Nu am gasit nodul\n";
        }
    }
    

    
    PointerNod maxim(PointerNod Nod) {
        while (Nod->dreapta != nullptr) {
            Nod = Nod->dreapta;
        }
        return Nod;
    }
    

    void adauga(int valoare) {

        PointerNod nod = new Nod ;
        nod->tata = nullptr;
        nod->stanga = nullptr;
        nod->dreapta = nullptr;
        nod->data = valoare;
        PointerNod y = nullptr;
        PointerNod x = this->radacina;

        while (x != nullptr) {
            y = x;
            if (nod->data < x->data) {
                x = x->stanga;
            } else {
                x = x->dreapta;
            }
        }


        nod->tata = y;
        if (y == nullptr) {
            radacina = nod;
        } else if (nod->data < y->data) {
            y->stanga = nod;
        } else {
            y->dreapta = nod;
        }

        splay(nod);
    }



    void stergerefinala(int data) {
        stergere(this->radacina, data);
    }


    void afisarefinala() {
        afisare(this->radacina, 0, false);
    }

};

int main() {

    SplayTree arbore;
    arbore.adauga(15);
    arbore.adauga(24);
    arbore.adauga(45);
    arbore.adauga(7);
    arbore.adauga(58);
    arbore.adauga(20);
    arbore.adauga(21);
    arbore.adauga(56);
    arbore.adauga(32);
    arbore.afisarefinala();
    arbore.findnodfinal(7);
    arbore.findnodfinal(2);
    arbore.stergerefinala(58);
    arbore.stergerefinala(21);
    arbore.stergerefinala(1);
    arbore.afisarefinala();
}