#include<iostream>
using namespace std;
#include<fstream>
struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}}; // nodo di lista 
struct FIFO{nodo* primo, *ultimo;FIFO(nodo*a=0, nodo*b=0){primo=a; ultimo=b;}};
struct nodot{int info; nodot* left, *right; nodot(int a=0, nodot* b=0, nodot* c=0){info=a; left=b; right=c;}};//nodo di albero




FIFO push_end(FIFO a, nodo*b)
{
  if(!a.primo)
  {a.primo=a.ultimo=b;}
  else
   {a.ultimo->next=b; a.ultimo=b;}
  return a;
}

void stampa_L(nodo*L)
{
 if (L)
  {cout<<L->info<<' '; stampa_L(L->next);}
 else
   cout<<endl;

}
nodo* costruisci(int dim)
{
 if(dim)
   {int x; cin>>x; return new nodo(x,costruisci(dim-1));}
 return 0;
}
 nodo* clone(nodo*a)
 {
  if(a)
  {return new nodo(a->info, clone(a->next));}
  return 0;
 }
 
 //*****************************************
 
 FIFO  push_begin(FIFO x, nodo* b){
    if(x.primo==0 && x.ultimo==0){
        x.primo=b;
        x.ultimo=b;
    }else{
        b->next=x.primo;
        x.primo=b;
    }
    return x;
 }
 
nodo* presente(nodo* n, int y){
    if(n==0){
        return 0;
    }else{
        if(n->info==y){
            return n;
        }else{
           return presente(n->next, y); 
        }
    }
}
 
bool presente_iter(nodo* n, int y){
    bool b=false;
    while(n && !b){
        if(n->info==y){
            b=true;
        }
        n=n->next;
    }
    return b;
}
 
//PRE=(L(Q) è una lista corretta e vL(Q)=L(Q))
FIFO tieni_ultimo_ric(nodo*&Q){
    FIFO r;
    //caso base la lista e' vuota
    if(Q==0){//CB1
        return FIFO();//la lista dei nodi ripetuti su una lista vuota e' anche essa vuota
    }else{
        //caso ricorsivo
        r=tieni_ultimo_ric(Q->next);
        nodo *p=presente(Q->next, Q->info);//CR1
        if(p!=0){//allora q e' un duplicato
            nodo *a=Q;
            Q=Q->next;
            a->next=0;
            r=push_begin(r,a);
            
        }
        //r=push_end(r,0);
       return r;
    }
}
/*
POST=(L(Q) è ottenuta da vL(Q) eliminando i nodi con info ripetuto mantenendo solo l'ultimo
nodo per ciascun campo info e mantenendo l'ordine relativo che questi nodi hanno in vL(Q).
Inoltre restituisce un valore FIFO f tale che f.primo è la lista dei nodi eliminati
nello stesso ordine relativo che essi hanno in vL(Q))
*/

/*
PROVA INDUTTIVA
CB1) se la lista e' vuota di duplicati di una lista vuota non ce ne sono
CR1) se il nodo non e' vuoto effettuo la ricorsione
pre-ric=(L(Q->next) è una lista corretta e vL(Q->next)=L(Q->next))
POST-ric=(L(Q->next) è ottenuta da vL(Q->next) eliminando i nodi con info ripetuto mantenendo solo l'ultimo
nodo per ciascun campo info e mantenendo l'ordine relativo che questi nodi hanno in vL(Q->next).
Inoltre restituisce un valore FIFO f tale che f.primo è la lista dei nodi eliminati
nello stesso ordine relativo che essi hanno in vL(Q->next))
*/

int len(nodo* L){
    int c = 0;
    while(L){
        c++;
        L=L->next;
    }
    return c;
}

//PRE=(L(Q) è una lista corretta e vL(Q)=L(Q))
FIFO tieni_ultimo_iter(nodo*& Q){
    FIFO to_return, to_del;
    int leng = len(Q);
    nodo **L = new nodo*[leng];
    nodo* current = Q;
    for(int i=0; current; i++){
        L[i] = current;
        current = current->next;
    }
    for(int i=0; i<leng; i++){
        nodo* tmp = L[leng-1-i];
        tmp->next = 0;
        if(presente_iter(to_return.primo,tmp->info)){
            to_del = push_begin(to_del,tmp);
        } else {
            to_return = push_begin(to_return, tmp);
        }
    }

    Q = to_return.primo;
    return to_del;
}
/*
POST=(L(Q) è ottenuta da vL(Q) eliminando i nodi con info ripetuto mantenendo solo l'ultimo
nodo per ciascun campo info e mantenendo l'ordine relativo che questi nodi hanno in vL(Q).
Inoltre restituisce un valore FIFO f tale che f.primo è la lista dei nodi eliminati
nello stesso ordine relativo che essi hanno in vL(Q))

Soluzione "al contrario"
anche se in realtà leggibile e semplice da dimostrare
dato che inizia dall'ultimo nodo della lista costruendo la pila delle chiamate di una soluzione ricorsiva
metterei
R = (0<=i<=len(Q) dove len(Q) è la lunghezza di Q) && (all'iterazione i-esima inseriti gli ultimi i nodi di Q
     in to_del o to_return che questi appaiano o meno (rispettivamente) almeno una volta all'interno di to_return)
Così la dimostrazione risulta semplice
*/


/*
ESERCIZIO TEORIA
PRE=(l' albero che ricevo e' corretto e non vuoto)
POST=(restituisce il numeo di nodi con un solo figlio successivi al nodo radice dato)
*/

 //*****************************************
 
main()
{
  
   int dim;
   
   cin>>dim;
   nodo*C=costruisci(dim);
   nodo* D=clone(C);
   cout<<"Lista costruita"<<endl;
   stampa_L(C);
   FIFO a =tieni_ultimo_ric(C);
   cout<<"soluzione ricorsiva"<<endl<<"nodi tolti:"<<endl;
   
   stampa_L(a.primo);
   cout<<"lista rimanente:"<<endl;
   stampa_L(C);
   FIFO b=tieni_ultimo_iter(D);
   cout<<"soluzione iterativa"<<endl<<"nodi tolti:"<<endl;
   stampa_L(b.primo);
   cout<<"lista rimanente:"<<endl;
   stampa_L(D);
   cout<<"end";
}
