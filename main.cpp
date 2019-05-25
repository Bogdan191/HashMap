#include <iostream>
#include <vector>
#include <cstring>
//#define tableSize
using namespace std;

template <typename K>
struct KeyHash{
    unsigned long operator() (const K &key) const
    {
        return reinterpret_cast<unsigned long> (&key)%111;
    }
 };
template <class K, class V>
class HashNode
{
    K key;
    V value;
    HashNode *next;

    public:
       HashNode(const K &, const V &);
       K GetKey() const;
       V GetValue() const;
       void SetValue(V);
       HashNode* GetNext();
       void SetNext(HashNode* n);

};
template <class K, class V>
HashNode<K, V>::HashNode(const K &k, const V &v) : key(k), value(v), next(nullptr)
{

}
template<class K, class V>
K HashNode<K, V>::GetKey() const
{
    return key;
}
template <class K, class V>
V HashNode<K, V>::GetValue() const
{
    return value;
}
template <class K ,class V>
void HashNode<K, V>::SetValue(V v)
{
    value = v;
}
template <class K, class V>
HashNode<K, V>* HashNode<K, V>::GetNext()
{
    return next;
}
template <class K, class V>
void HashNode<K, V>::SetNext(HashNode<K, V> *n)
{
   next = n;
}


template <class K, class V >
class HashMap
{
    HashNode <K, V> ** table;
    KeyHash<K> hashFunction;
    int tableSize;
    public:
        HashMap();
        HashMap(const HashMap &h);
        bool Get(const K &key, const V &value);                                         // returneaza true daca valoarea apare in cheie, false in caz contrar
        V* GetVector(const K &key);                                                     // returneaza vectorul cu toate elementele din cheia respectiva
        void PutInHash(const K &key, const V &value);                                   // adauga in HashMap valoare noua
        ~HashMap();                                                                     // destructor
        void Delete(const K &key, const V &value);                                      // sterge din cheia 'key' valoarea 'value'
        int NrOfKeys();                                                                 // returneaza numarul de chei
        HashMap operator=(HashMap &);                                                   // supraincarcarea operatorului de atribuire
        V operator[](const K& key);                                                     // returneaza prima valoare cunoscuta pentru cheia 'key'
        HashNode<K, V>** GetTable();                                                    // returneaza tabelul
        friend ostream& operator<<(ostream &out, HashMap<K, V>&);                       // supraincarcarea operatorului de afisare
        void Afisare();                                                                 // functie ce afiseaza tabelul de dispersie


};
template<class K, class V>
HashMap<K, V>::HashMap()
{
    table = new HashNode<K, V>*[10001]();
    tableSize = 10001;
}
template<class K, class V>
HashMap<K, V>::HashMap(const HashMap &h)
{
    table = h.table;
}
template <class K, class V>
bool HashMap<K, V>::Get(const K &key, const V &value)
{

    HashNode<K, V> *entry = table[key];
    while(entry != NULL)
    {
        if(entry->GetValue() == value)
        {
            //value = entry->GetValue();
            return true;
        }
        entry = entry->GetNext();
    }

    return false;

}
template <class K, class V>
V* HashMap<K, V>::GetVector(const K &key)
{
    int i = 1;
    V *p;
    p = new V[1001];
    HashNode<K, V> *entry = table[key];

    while(entry != nullptr)
    {

            p[i++] = entry->GetValue();
           entry = entry->GetNext();
    }
     p[0]  = i;
    return p;
}
template <class K, class V>
void HashMap<K, V>::PutInHash(const K &key, const V &value)
{

    HashNode<K, V> *prev = NULL;
    HashNode<K, V> *entry = table[key];
    while(entry != nullptr)
    {

        prev = entry;
        entry = entry->GetNext();
    }

    if(prev == NULL)
    {
        entry = new HashNode<K, V> (key, value);
        entry->SetNext(nullptr);
        table[key] = entry;

    }
    else
    {

        entry = new HashNode<K, V> (key, value);
        prev->SetNext(entry);

    }


}
template <class K, class V>
int HashMap<K, V>::NrOfKeys()
{
    int nrKeys = 0;
    for(int i = 0; i < tableSize; i++)
    {
        HashNode <K, V> *entry = table[i];

        if(entry != NULL)
            nrKeys++;
    }

    return nrKeys;

}
template <class K, class V>
HashMap<K, V>::~HashMap()
{
    for(int i = 0; i < tableSize; i++)
    {
        HashNode<K, V> *entry = table[i];

        while(entry != NULL)
        {
            HashNode<K, V>*prev = entry;
            entry = entry->GetNext();
            delete prev;
        }

        table[i] = NULL;
    }

}
template <class K, class V>
void HashMap<K, V>::Delete(const K &key, const V &value)
{

    HashNode<K, V> *entry, *prev;
   entry = table[key];
   prev = NULL;
     if(entry->GetValue() == value)
            {
                table[key] = entry->GetNext();
                delete entry;
                return;

            }
            while(entry != NULL)
            {
                prev = entry;
                entry = entry->GetNext();
                if(entry->GetValue() == value)
                {
                    prev->SetNext(entry->GetNext());
                    delete entry;
                    return;
                }


            }
}
template <class K, class V>
HashNode<K, V>** HashMap<K, V>::GetTable()
{
    return table;
}
template <class K, class V>
HashMap<K, V> HashMap<K, V>::operator=( HashMap<K, V> &T)
{
    this->table = T.GetTable();


}
template <class K, class V>
V HashMap<K, V>::operator[](const K &key)
{

    HashNode<K, V> *entry = table[key];
    if(entry != NULL)
        return entry->GetValue();

    return NULL;

}
template <class K, class V>
ostream& operator<<(ostream & out, HashMap<K, V> &T)
{ int i, k = 1;
    HashNode<K, V> *prev, *entry;
    prev = NULL;
    for(i = 0; i < 100; i++)
    {
        entry = T.GetTable()[i];
        cout << entry->GetKey() << ": ";
        while(entry != NULL)
        {
            cout << entry->GetValue() << " ";
            entry = entry->GetNext();
        }
        cout << "\n";
    }
    return out;
}
template <class K, class V>
void HashMap<K, V>::Afisare()
{
     int i = 0; int k = 0, n = 0;
    HashNode<K, V> *prev, *entry;
    prev = NULL;
    K *p = new K[100];
    for(i = 0; i < tableSize; i++)
    {
        entry = table[i];
        if(entry != NULL)
            p[n++] = entry->GetKey();
    }
    for(k = 0; k < n; k++)
    {
        entry = table[p[k]];

        cout << entry->GetKey() << ": ";
        while(entry != NULL)
        {
            cout << entry->GetValue() << " ";
            entry = entry->GetNext();
        }
        cout << "\n";
    }

}

int main()
{ int ok = 0;
  char *tip_cheie, *tip_valori;


     while(ok == 0)
     {
         try{
        tip_cheie = new char[10];
       cout << "Introduceti tipul cheilor(char/int): "; cin >> tip_cheie;
       if(strcmp(tip_cheie, "int") != 0 && strcmp(tip_cheie, "char")!= 0)
           throw ok;
        ok = 1;
     }
     catch(int x)
     {
         cout << "Tip de cheie invalid!Mai incearca... \n\n";

     }
     }
     ok = 0;
     while(ok == 0)
     {
         try
         {
            tip_valori = new char[10];
            cout << "Introduceti tipul valorilor(char/int/float): "; cin >> tip_valori;
            if(strcmp(tip_valori, "int") != 0 && strcmp(tip_valori, "char") != 0 && strcmp(tip_valori, "float") != 0 && strcmp(tip_valori, "double")!= 0)
                throw ok;
            ok = 1;
         }
         catch(int x)
           {
            cout << "Tip de cheie invalid!Mai incearca... \n\n";
           }
     }
     cout << "Tip cheie: " << tip_cheie << "\n";
     cout << "Tip valori: " << tip_valori << "\n";
     if(strcmp(tip_cheie, "int") == 0 && strcmp(tip_valori, "char") == 0)
     {
         HashMap<int, char> V, T;
         int k;
         char v, *p;
         ok = 1;
         while(ok == 1)
         {
             cout << "Introdu cheia si valoarea: "; cin >> k >> v;
             V.PutInHash(k, v);
             cout << "Adaugi in continuare elemente?(1-DA/0-NU)"; cin >> ok;
         }

         V.Afisare();
         cout << "Numarul de chei: " << V.NrOfKeys() << "\n";
         cout << "\n";
           cout << "Introduceti valoarea care trebuie cautata in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua cautarea : "; cin >> k;

         if(V.Get(k, v))
            cout << "Elementul " << v << " se gaseste in cheia " << k << "\n";
           else cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu e in HashMap\n";
           cout << "Introduceti valoarea care trebuie stearsa in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua stergerea : "; cin >> k;
           if(!V.Get(k, v))
            cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu e in HashMap\n";
           else
           {
               V.Delete(k, v);
               cout << "Elementul " << v << " a fost sters din cheia " << k << "\n";
               cout << "Afisare dupa stergere: \n";
               V.Afisare();
               cout << "\n";
           }

           cout << "Introduceti cheia din care sa fie afisate toate elementele: "; cin >> k;
            p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
            {
                cout << "Afisare elemente din cheia " << k << ": ";
                for(int i = 1; i < p[0]; i++)
                    cout << p[i] << " ";
                cout << "\n";
            }

            cout << "Introduceti cheia pentru care sa se afiseze prima valoare cunoscuta: "; cin >> k;
             p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
            else
                cout << "Prima valoare cunoscuta pentru cheia " << k << " este " << V[k] << "\n";

           T = V;
           T.Afisare();
     }
     if(strcmp("int", tip_cheie) == 0 && strcmp(tip_valori,"int") == 0)
     {
         HashMap<int, int>V, T;
         int k, v, *p;
         ok = 1;
         while(ok == 1)
         {
             cout << "Introdu cheia si valoarea: "; cin >> k >> v;
             V.PutInHash(k, v);
             cout << "Adaugi in continuare elemente?(1-DA/0-NU)"; cin >> ok;
         }

         V.Afisare();
         cout << "\n";
         cout << "Numarul de chei: " << V.NrOfKeys() << "\n";

           cout << "Introduceti valoarea care trebuie cautata in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua cautarea : "; cin >> k;

         if(V.Get(k, v))
            cout << "Elementul " << v << " se gaseste in cheia " << k << "\n";
           else cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu este in HashMap\n";
           cout << "Introduceti valoarea care trebuie stearsa in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua stergerea : "; cin >> k;
           if(!V.Get(k, v))
            cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu apare in HashMap\n";
           else
           {
               V.Delete(k, v);
               cout << "Elementul " << v << " a fost sters din cheia " << k << "\n";
               cout << "Afisare dupa stergere:\n";
               V.Afisare();
               cout << "\n";
           }

           cout << "Introduceti cheia din care sa fie afisate toate elementele: "; cin >> k;
           p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
            {
                cout << "Afisare elemente din cheia " << k << ": ";
                for(int i = 1; i < p[0]; i++)
                    cout << p[i] << " ";
                cout << "\n";
            }

            cout << "Introduceti cheia pentru care sa se afiseze prima valoare cunoscuta: "; cin >> k;
            p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
                cout << "Prima valoare cunoscuta pentru cheia " << k << " este " << V[k] << "\n";


           T = V;
           T.Afisare();



     }
     if(strcmp(tip_cheie, "int") == 0 && strcmp(tip_valori, "float") == 0)
     {
         HashMap<int, float> V, T;
         int k;
         float v, *p;
         ok = 1;
         while(ok == 1)
         {
             cout << "Introdu cheia si valoarea: "; cin >> k >> v;
             V.PutInHash(k, v);
             cout << "Adaugi in continuare elemente?(1-DA/0-NU)"; cin >> ok;
         }

         V.Afisare();
         cout << "Numarul de chei: " << V.NrOfKeys() << "\n";
         cout << "\n";
           cout << "Introduceti valoarea care trebuie cautata in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua cautarea : "; cin >> k;

         if(V.Get(k, v))
            cout << "Elementul " << v << " se gaseste in cheia " << k << "\n";
           else cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu apare in HashMap\n";
           cout << "Introduceti valoarea care trebuie stearsa in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua stergerea : "; cin >> k;
           if(!V.Get(k, v))
            cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu apare in HashMap\n";
           else
           {
               V.Delete(k, v);
               cout << "Elementul " << v << " a fost sters din cheia " << k << "\n";
               cout << "Afisare dupa stergere: \n";
               V.Afisare();
               cout << "\n";
           }

           cout << "Introduceti cheia din care sa fie afisate toate elementele: "; cin >> k;
           p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
            {
                cout << "Afisare elemente din cheia " << k << ": ";
                for(int i = 1; i < p[0]; i++)
                    cout << p[i] << " ";
                cout << "\n";
            }

            cout << "Introduceti cheia pentru care sa se afiseze prima valoare cunoscuta: "; cin >> k;
            p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
                cout << "Prima valoare cunoscuta pentru cheia " << k << " este " << V[k] << "\n";

           T = V;
           T.Afisare();
     }


     if(strcmp(tip_cheie, "char") == 0 && strcmp(tip_valori, "char") == 0)
     {
         HashMap <char, char> V, T;
         char k, v, *p;
         ok = 1;
         while(ok == 1)
         {
             cout << "Introdu cheia si valoarea: "; cin >> k >> v;
             V.PutInHash(k, v);
             cout << "Adaugi in continuare elemente?(1-DA/0-NU)"; cin >> ok;
         }

         V.Afisare();
         cout << "Numarul de chei: " << V.NrOfKeys() << "\n";
         cout << "\n";
           cout << "Introduceti valoarea care trebuie cautata in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua cautarea : "; cin >> k;

         if(V.Get(k, v))
            cout << "Elementul " << v << " se gaseste in cheia " << k << "\n";
           else cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu apare in HashMap\n";
           cout << "Introduceti valoarea care trebuie stearsa in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua stergerea : "; cin >> k;
           if(!V.Get(k, v))
            cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu este in HashMap\n";
           else
           {
               V.Delete(k, v);
               cout << "Elementul " << v << " a fost sters din cheia " << k << "\n";
               cout << "Afisare dupa stergere: \n";
               V.Afisare();
               cout << "\n";
           }

           cout << "Introduceti cheia din care sa fie afisate toate elementele: "; cin >> k;
           p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
            {
                cout << "Afisare elemente din cheia " << k << ": ";
                for(int i = 1; i < p[0]; i++)
                    cout << p[i] << " ";
                cout << "\n";
            }

            cout << "Introduceti cheia pentru care sa se afiseze prima valoare cunoscuta: "; cin >> k;
              p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
            cout << "Prima valoare cunoscuta pentru cheia " << k << " este " << V[k] << "\n";

           T = V;
           T.Afisare();
     }
     if(strcmp(tip_cheie, "char") == 0 && strcmp(tip_valori, "int") == 0)
     {
         HashMap<char, int> V, T;
         char k;
         int v, *p;
         ok = 1;

         while(ok == 1)
         {
             cout << "Introdu cheia si valoarea: "; cin >> k >> v;
             V.PutInHash(k, v);
             cout << "Adaugi in continuare elemente?(1-DA/0-NU)"; cin >> ok;
         }

         V.Afisare();
         cout << "\n";
         cout << "Numarul de chei: " << V.NrOfKeys() << "\n";
           cout << "Introduceti valoarea care trebuie cautata in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua cautarea : "; cin >> k;

         if(V.Get(k, v))
            cout << "Elementul " << v << " se gaseste in cheia " << k << "\n";
           else cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia este in HashMap\n";
           cout << "Introduceti valoarea care trebuie stearsa in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua stergerea : "; cin >> k;
           if(!V.Get(k, v))
            cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau aceasta cheie nu este in HashMap\n";
           else
           {
               V.Delete(k, v);
               cout << "Elementul " << v << " a fost sters din cheia " << k << "\n";
               cout << "Afisare dupa stergere: \n";
               V.Afisare();
               cout << "\n";
           }

           cout << "Introduceti cheia din care sa fie afisate toate elementele: "; cin >> k;
           p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
            {
                cout << "Afisare elemente din cheia " << k << ": ";
                for(int i = 1; i < p[0]; i++)
                    cout << p[i] << " ";
                cout << "\n";
            }

            cout << "Introduceti cheia pentru care sa se afiseze prima valoare cunoscuta: "; cin >> k;
             p = V.GetVector(k);
                if(p[0] == 1)
                    cout << "Cheia " << k << " nu este in HashMap\n";
            else
                cout << "Prima valoare cunoscuta pentru cheia " << k << " este " << V[k] << "\n";

           T = V;
           T.Afisare();
     }
     if(strcmp(tip_cheie, "char") == 0 && strcmp(tip_valori, "float") == 0)
     {
         HashMap<char, float> V, T;
         char k;
         float v, *p;
         ok = 1;
         while(ok == 1)
         {
             cout << "Introdu cheia si valoarea: "; cin >> k >> v;
             V.PutInHash(k, v);
             cout << "Adaugi in continuare elemente?(1-DA/0-NU)"; cin >> ok;
         }

         V.Afisare();
         cout << "\n";
         cout << "Numarul de chei: " << V.NrOfKeys() << "\n";
           cout << "Introduceti valoarea care trebuie cautata in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua cautarea : "; cin >> k;

         if(V.Get(k, v))
            cout << "Elementul " << v << " se gaseste in cheia " << k << "\n";
           else cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu apare in HashMap\n";
           cout << "Introduceti valoarea care trebuie stearsa in HashMap: "; cin >> v;
           cout << "Introduceti cheia in care se va efectua stergerea : "; cin >> k;
           if(!V.Get(k, v))
            cout << "Elementul " << v << " nu se gaseste in cheia " << k << " sau cheia nu este in HashMap\n";
           else
           {
               V.Delete(k, v);
               cout << "Elementul " << v << " a fost sters din cheia " << k << "\n";
               cout << "Afisare dupa stergere: \n";
               V.Afisare();
               cout << "\n";
           }

           cout << "Introduceti cheia din care sa fie afisate toate elementele: "; cin >> k;
           p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
            {
                cout << "Afisare elemente din cheia " << k << ": ";
                for(int i = 1; i < p[0]; i++)
                    cout << p[i] << " ";
                cout << "\n";
            }

            cout << "Introduceti cheia pentru care sa se afiseze prima valoare cunoscuta: "; cin >> k;
              p = V.GetVector(k);
           if(p[0] == 1)
            cout << "Cheia " << k << " nu este in HashMap\n";
           else
            cout << "Prima valoare cunoscuta pentru cheia " << k << " este " << V[k] << "\n";


           T = V;
           T.Afisare();

     }

    return 0;
}
