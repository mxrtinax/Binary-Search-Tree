#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
//ifstream f("input.in");
//Martinas Paul
//Roman Iulian-Robert
//Cherim Erol
struct Nod
{
        long long info;
        Nod *parinte;
        Nod *stanga;
        Nod *dreapta;
        long long contor_elemente_mai_mici;
};

struct ABC
{
    Nod *radacina;
    long long contor;
};

bool frunza(Nod* n)
{
    if(n->stanga==NULL && n->dreapta==NULL)
        return 1;
    return 0;
}

long long cardinal(ABC arbore)
{
    return arbore.contor;
}


bool este_in(ABC arbore, long long x)
{
  Nod *rad = arbore.radacina;
  while (rad!=NULL)
  {
    if(rad->info==x)
       return 1;
    if(x<rad->info)
        rad = rad->stanga;
    else
        if(x>rad->info)
            rad = rad->dreapta;
  }
  return 0;
}

void insereaza(ABC &arbore, long long x)
{
    Nod *rad;
    Nod *nou=new Nod;
    nou->info=x;
    rad=arbore.radacina;
    bool ok=0;

    if(arbore.contor==0)
    {
        ok=1;
        nou->stanga=NULL;
        nou->dreapta=NULL;
        nou->parinte=NULL;
        nou->contor_elemente_mai_mici=0;
        arbore.radacina=nou;
        arbore.contor++;
    }

    while(ok==0&&x!=rad->info)
    {
        if(x<rad->info)
        {
            rad->contor_elemente_mai_mici++;
            if(rad->stanga==NULL)
            {
                ok=1;
                rad->stanga=nou;
                nou->stanga=NULL;
                nou->dreapta=NULL;
                nou->parinte=rad;
                arbore.contor++;
            }
            else
                rad=rad->stanga;
        }
        if(x>rad->info)
        {
            if(rad->dreapta==NULL)
            {
                ok=1;
                rad->dreapta=nou;
                nou->stanga=NULL;
                nou->dreapta=NULL;
                nou->parinte=rad;
                arbore.contor++;
            }
            else
                rad=rad->dreapta;
        }
    }
    if(ok==0)
        delete nou;
}

void sterge(ABC &arbore, long long x)
{
    Nod* deSters;
    Nod *rad = arbore.radacina;
    bool ok=0;
    while (rad!=NULL&&ok==0)
    {
      if(rad->info==x)
         ok=1;
      if(x<rad->info)
         rad = rad->stanga;
      else
         if(x>rad->info)
             rad = rad->dreapta;
    }
    if (ok==0)
    {
        cout<<"Nodul cu valoarea "<<x<<" nu exista in arbore."<<'\n';
    }
    else
    {
        arbore.contor--;
        deSters=rad;
        if(frunza(deSters)==1) ///in cazul in care este frunza, nodul se sterge direct
        {
            if(deSters->parinte->stanga==deSters)
                deSters->parinte->stanga=NULL;
            else
                deSters->parinte->dreapta=NULL;
            deSters = NULL;
        }

        else if(deSters->stanga==NULL && deSters->dreapta!=NULL) ///cazul in care nodul are fiu doar la dreapta
        {
            if(deSters->parinte->dreapta==deSters)
                 deSters->parinte->dreapta = deSters->dreapta;
            else
                 deSters->parinte->stanga=deSters->dreapta;

            deSters->dreapta->parinte = deSters->parinte;
            ///delete deSters;
        }
    else
     {
        if(deSters->stanga->dreapta==NULL) ///cazul in care nodul nu are succesor de gradul al 2-lea pe dreapta
        {
            if(deSters->parinte->stanga==deSters)
                 deSters->parinte->stanga = deSters->stanga; //aici se fac legaturile intre noduri
            else
                 deSters->parinte->dreapta=deSters->stanga;
            deSters->stanga->parinte = deSters->parinte;
            deSters->stanga->dreapta = deSters->dreapta;
           deSters = NULL;
        }
        else ///se cauta elementul de inlocuit
        {
           Nod* aux;
           aux = deSters->stanga;
           while (aux->dreapta != NULL){aux = aux->dreapta;}
           deSters->info=aux->info;
           aux->stanga->parinte=aux->parinte;
           aux->parinte->dreapta=aux->stanga;
           ///delete aux;
        }
     }
    }
}

Nod* min(ABC arbore)
{
  Nod *rad=arbore.radacina;
  while(rad->stanga!=NULL)
    rad=rad->stanga;
  return rad;
}


Nod* max(ABC arbore)
{
  Nod *rad=arbore.radacina;
  while(rad->dreapta!=NULL)
    rad=rad->dreapta;
  return rad;
}


Nod* succesor(ABC arbore, long long x)
{
  Nod *rad = arbore.radacina;
  bool ok=0;
  while (rad!=NULL&&ok==0)
  {
    if(rad->info==x)
       ok=1;
    if(x<rad->info)
        rad = rad->stanga;
    else
        if(x>rad->info)
            rad = rad->dreapta;
  }
    if(ok==0)
    {
        cout<<"nu exista nodul cu valoarea "<<x<<" in arbore"<<'\n';
        return NULL;
    }
    else
    {
      if(rad->info==max(arbore)->info)
      {
          cout<<"nodul cu valoarea "<<x<<" nu are succesor"<<'\n';
          return NULL;
      }
        Nod *src;
        src=rad;
        if(rad->dreapta!=NULL)
        {
            src=rad->dreapta;
            while(src->stanga!=NULL)
                src=src->stanga;
            return src;
        }
        else
        {
            while(1!=2)
            {
             if(src->info<src->parinte->info)
                return src->parinte;
             else
                src=src->parinte;
            }
            return src;
            }
        }
}


Nod* predecesor(ABC arbore, long long x)
{
  Nod *rad = arbore.radacina;
  bool ok=0;
  while (rad!=NULL&&ok==0)
  {
    if(rad->info==x)
       ok=1;
    if(x<rad->info)
        rad = rad->stanga;
    else
        if(x>rad->info)
            rad = rad->dreapta;
  }
    if(ok==0)
    {
        cout<<"nu exista nodul cu valoarea "<<x<<" in arbore"<<'\n';
        return NULL;
    }
    else
    {
        if(rad->info==min(arbore)->info)
        {
            cout<<"Nodul cu valoarea "<<x<<"nu are predecesor"<<'\n';
            return NULL;
        }

        Nod *src;
        src=rad;
        if(rad->stanga!=NULL)
        {
            src=rad->stanga;
            while(src->dreapta!=NULL)
                src=src->dreapta;
            return src;
        }
        else
        {
            while(1!=2)
            {
             if(src->info>src->parinte->info)
                return src->parinte;
             else
                src=src->parinte;
            }
            return src;
            }
        }
}

Nod* k_element(ABC arbore, long long k)
{
    Nod *rad=arbore.radacina;
    long long c=rad->contor_elemente_mai_mici;

    while(rad!=NULL && c!=k-1)
    {
        if(c>k-1)
        {
            c=rad->stanga->contor_elemente_mai_mici;
            rad=rad->stanga;
        }

        if(c<k-1)
        {
            c=c+1+rad->dreapta->contor_elemente_mai_mici;
            rad=rad->dreapta;
        }
    }
    return rad;
}

void afisare(Nod *rad)
{
    if(rad!=NULL)
    {
      cout<<rad->info<<' ';
      afisare(rad->stanga);
      afisare(rad->dreapta);
    }
}
void afisare_in_fisier(Nod *rad,ofstream& g)
{
    if(rad!=NULL)
    {
      g<<rad->info<<' ';
      afisare_in_fisier(rad->stanga, g);
      afisare_in_fisier(rad->dreapta, g);
    }
}

void meniu(){
    ifstream f("test.in");   // introduceti numele fisierului de input de test
    ofstream g("test.out");  //introduceti numele fisierului de output
    int raspuns=1;
    long long int x, k;
    ABC arbore;
    arbore.radacina=NULL;
    arbore.contor = 0;
    cout<<"\n Arbore binar de cautare  \n";
    cout<<"1. Cititi elementele dintr un fisier\n";  //daca introducem un arbore din fisier, tasta 1 trebuie selectata prima data
    cout<<"2. inserati elemente in arbore\n";
    cout<<"3. Stergeti elemente din arbore\n";
    cout<<"4. Calculare maxim \n";
    cout<<"5. Calculare minim\n";
    cout<<"6. Predecesorul lui x\n";
    cout<<"7. Succesorul lui x\n";
    cout<<"8. Al k-lea element\n";
    cout<<"9. Cardinalul arborelui\n";
    cout<<"10. Verifica daca x este in arbore\n";
    cout<<"11. Afiseaza arborele\n";
    cout<<"12. Ruleaza teste\n";
    cout<<"0. Inchide\n";
    cout<<"nr actiune: ";
    cin>>raspuns;
    while(raspuns!=0){
        if(raspuns==1){
          while(f>>x)
          {//cout<<x<<" ";
          insereaza(arbore,x); }
          f.close();
          cout<<endl;
        }
        if(raspuns==2){
            cout<<"ce element inserati? \n";
            cin>>x;
            insereaza(arbore,x);
        }
        if(raspuns==3){
          cout<<"ce element stergeti?\n";
          cin>>x;
          if(este_in(arbore,x))
            sterge(arbore,x);
          else cout<<x<<" nu se afla in arbore\n";
        }
        if(raspuns==4){
          if(arbore.radacina!=NULL){
          cout<<"maximul arborelui este ";
          cout<<max(arbore)->info<<"\n";}
          else cout<<" arborele este gol\n";
        }
        if(raspuns==5){
          if(arbore.radacina!=NULL){
          cout<<"minimul arborelui este ";
          cout<<min(arbore)->info<<"\n";}
          else cout<<" arborele este gol\n";
        }
        if(raspuns==6){
          cout<<"introduceti un numar x = ";
          cin>>x;
          Nod *rezultat=predecesor(arbore,x);
          if(rezultat!=NULL)
          cout<<"predecesorul lui "<<x<<" este "<<predecesor(arbore,x)->info<<"\n";
        }
        if(raspuns==7){
          cout<<"introduceti un numar x = ";
          cin>>x;
          Nod *rezultat=succesor(arbore,x);
          if(rezultat!=NULL)
          cout<<"succesorul lui "<<x<<" este "<<succesor(arbore,x)->info<<"\n";
        }
        if(raspuns==8){
          if(arbore.radacina!=NULL){
          cout<<"introduceti k = ";
          cin>>k;
          cout<<"\nAl k-lea element din arbore este "<<k_element(arbore,k)->info<<"\n";  }
          else cout<<"arborele este gol\n";}
        if(raspuns==9){
          cout<<"cardinalul arborelui este "<<cardinal(arbore)<<"\n";
        }
        if(raspuns==10){
          cout<<"ce element cautati? \n";
          cin>>x;
          if(este_in(arbore,x)) cout<<"elementul se afla i arbore\n";
          else cout<<"elementul nu se afla in arbore\n";
        }
        if(raspuns==11){
          afisare(arbore.radacina);
          }
        system("pause");
        system("cls");
        cout<<"\n Arbore binar de cautare  \n";
        cout<<"1. Cititi elementele dintr un fisier\n";
        cout<<"2. inserati elemente in arbore\n";
        cout<<"3. Stergeti elemente din arbore\n";
        cout<<"4. Calculare maxim \n";
        cout<<"5. Calculare minim\n";
        cout<<"6. Predecesorul lui x\n";
        cout<<"7. Succesorul lui x\n";
        cout<<"8. Al k-lea element\n";
        cout<<"9. Cardinalul arborelui\n";
        cout<<"10. Verifica daca x este in arbore\n";
        cout<<"11. Afiseaza arborele\n";
        cout<<"0. Inchide\n";
        cout<<"nr actiune: ";
        cin>>raspuns;
      }
      afisare_in_fisier(arbore.radacina,g);
  }


int main()
{
    meniu();
    return 0;
}
