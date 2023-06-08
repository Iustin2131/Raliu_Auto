#include <iostream>

using namespace std;
  struct nod
  {
      int info;
      nod *urm;
  };
int main()
{
    nod *prim=NULL;
    nod *ult=NULL;
    nod *q=NULL;
    int n,x;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        q=new nod;
        q->info=x;
        q->urm=NULL;
        if(prim==NULL)
        {
            prim=q;
            ult=q;
        }
        else
        {
            ult->urm=q;
            ult=q;
        }
    }
    int m;
    cin>>m;
    nod *prim2=NULL,*ult2=NULL,*e;
    for(int i=1;i<=m;i++)
    {
        cin>>x;
        e=new nod();
        e->info=x;
        e->urm=NULL;
        if(prim2==NULL)
        {
            prim2=e;
        ult2=e;
        }
        else
        {
            ult2->urm=e;
            ult2=e;
        }
    }
    q=prim; e=prim2;
    nod *iprim,*iult=NULL,*i;
    while(q!=NULL && e!=NULL)
    {
        if(q->info<e->info && iult==NULL)
        {
            i=new nod;
            i->info=q->info;
            i->urm=NULL;
            iult=i;
            iprim=i;
            q=q->urm;

        }
        else
        if(q->info<e->info && iult!=NULL)
{
              i=new nod;
              i->info=q->info;
              iult->urm=i;
              i=iult;
              q=q->urm;
}
else
     if(q->info==e->info && iult==NULL)
        {
            i=new nod;
            i->info=q->info;
            i->urm=NULL;
            iult=i;
            iprim=i;
            q=q->urm;
            i=new nod;
            i->info=e->info;
            iult->urm=i;
            iult=i;
            e=e->urm;
        }
        else
        if(q->info==e->info && iult!=NULL)
{
              i=new nod;
              i->info=q->info;
              iult->urm=i;
              i=iult;
              q=q->urm;
               i=new nod;
            i->info=e->info;
            iult->urm=i;
            iult=i;
            e=e->urm;
}
else
    if(q->info>e->info && iult==NULL)
        {
            i=new nod;
            i->info=e->info;
            i->urm=NULL;
            iult=i;
            iprim=i;
            e=e->urm;
        }
        else
        if(q->info>e->info && iult!=NULL)
{
              i=new nod;
              i->info=e->info;
              iult->urm=i;
              i=iult;
              e=e->urm;
}
    }
    nod *k;
    k=prim;
    while(k)
    {
        cout<<k->info<<" ";
        k=k->urm;
    }
    return 0;
}
