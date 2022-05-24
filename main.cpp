//Adam Emanuel

#include <fstream>
using namespace std;
ifstream cin("abce.in");
ofstream cout("abce.out");

struct Nod {
    Nod *tata;
    Nod *stanga;
    Nod *dreapta;
    int data;
};

typedef Nod* PointerNod;



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


    void findnodfinal(int k) {
        PointerNod x = findnod(this->radacina, k);
        if (x!= nullptr) {
            splay(x);
            cout<<1<<"\n";
        }
        else{
            cout<<0<<"\n";
        }


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

    PointerNod maxim(PointerNod Nod) {
        while (Nod->dreapta != nullptr) {
            Nod = Nod->dreapta;
        }
        return Nod;
    }

    PointerNod minim(PointerNod Nod) {
        while (Nod->stanga != nullptr) {
            Nod = Nod->stanga;
        }
        return Nod;
    }

    int  predecesor(PointerNod nod,int x){
        if(nod== nullptr)
            return  -1000000001;
        if(nod->data>x)
            return predecesor(nod->stanga,x);
        return max(nod->data,predecesor(nod->dreapta,x));


    }

    void sir(PointerNod nod, int stanga, int dreapta) {
        if ( nod == nullptr )
            return;
        sir(nod -> stanga, stanga, dreapta);
        if ( nod->data >= stanga && nod -> data <= dreapta )
            cout << nod->data << " " ;
        sir( nod -> dreapta, stanga, dreapta) ;}

    int  succesor(PointerNod nod,int x){
        if(nod== nullptr)
            return  1000000001;
        if(nod->data<x)
            return succesor(nod->dreapta,x);
        return min(nod->data,succesor(nod->stanga,x));


    }
    void succesorfinal(int x){
        cout<< succesor(this->radacina,x)<<"\n";
    }
    void predecesorfinal(int x){
        cout<< predecesor(this->radacina,x)<<"\n";
    }

    void sirfinal(int stanga,int dreapta){
        sir(this->radacina,stanga,dreapta);
        cout<<"\n";
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
    int q, c, x, y;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> c;
        if (c == 1) {
            cin >> x;
            arbore.adauga(x);
        } else if (c == 2) {
            cin >> x;
            arbore.stergerefinala(x);
        } else if (c == 3) {
            cin >> x;
            arbore.findnodfinal(x);
        } else if (c == 4) {
            cin >> x;
            arbore.predecesorfinal(x);
        } else if (c == 5) {
            cin >> x;
            arbore.succesorfinal(x);
        } else if (c == 6) {
            cin>>x>>y;
            arbore.sirfinal(x,y);

        }

    }
}

