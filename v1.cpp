#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

#define INF 100000

struct heap_struct
{
	int nod,cost;
};

struct apcm_struct
{
	int n1,n2,c;
};

void citire_graf(int nr_muchi , vector<pair<int,int> > *la)
{
	int a,b,c;
	a=b=c=0;
	for(int i=1;i<=nr_muchi;i++)
	{
		scanf("%d %d %d ",&a,&b,&c);
		la[a].push_back(make_pair(b,c));
		la[b].push_back(make_pair(a,c));
	}
}	


//urcarea unui element in heap
void min_heap(heap_struct *h,int poz,int *v)
{
	while(1)
	{
		if(h[poz/2].cost>h[poz].cost)
		{
			swap(v[h[poz].nod],v[h[poz/2].nod]);
			swap(h[poz],h[poz/2]);
			poz=poz/2;
		}
		else break;
	}
}
//functia de inserare a unui nod si a costului sau intr-un heap
void inserare(heap_struct *h,int c,int n,int *poz)
{
	int i;
	for(i=0;h[i].nod;i++);
		h[i].nod=n;
		h[i].cost=c;
		poz[n]=i;
	//operatia de transformare a unui heap intr-un min-heap
	min_heap(h,i,poz);
}

void down(heap_struct *h, int *v)
{
	int poz=0,f1,f2;
	while(1)
	{
		f1=2*poz+1;
		f2=2*poz+2;
		if(h[f1].nod == 0 && h[f2].nod) // are doar fiu drept
		{
			if(h[f2].cost<h[poz].cost)
			{
				swap(v[h[f2].nod],v[h[poz].nod]);
				swap(h[f2],h[poz]);
				poz=f2;
			}
		}
		else if(h[f1].nod && h[f2].nod==0) // are doar fiu stang
		{
			if(h[f1].cost<h[poz].cost)
			{
				swap(v[h[f1].nod],v[h[poz].nod]);
				swap(h[f1],h[poz]);
				poz=f1;
			}
		}
		else if(h[f1].nod && h[f2].nod) // are ambii fii
		{
			if(h[f1].cost<h[f2].cost)
			{
				swap(v[h[f1].nod],v[h[poz].nod]);
				swap(h[f1],h[poz]);
				poz=f1;
			}
			else if(h[f2].cost<h[f1].cost)
			{
				swap(v[h[f2].nod],v[h[poz].nod]);
				swap(h[f2],h[poz]);
				poz=f2;
			}
			else break;
		}
		else break; // nu mai are niciun fiu
	}
}

void Decapitare(heap_struct *h,int *v)
{
	int i;
	for(i=0;h[i+1].nod;i++);
	///////////////////////////////////////////////////////////////
		swap(h[0],h[i]);
		swap(v[0],v[i]);
	v[h[i].nod]=-1;
	h[i].nod=h[i].cost=0;
	down(h,v);

}
void algoritm(vector<pair<int,int> > *la,int n,int m,int start)
{
	//variabile
	int *tata,*costuri,*viz,vecin,curent,cost,*poz;
	heap_struct *heap;
	apcm_struct *apcm;

	//alocare memorie
	tata=new int [n+1];
	costuri=new int [n+1];
	viz=new int [n+1];
	heap=new heap_struct[n+1];
	poz=new int[n+1];
	apcm=new apcm_struct[n+1];

	//initializare variabile
	for(int i=0;i<=n;i++)
		{
			tata[i]=viz[i]=0;
			heap[i].nod=heap[i].cost=0;
			costuri[i]=INF;
			poz[i]=-1;
		}
	costuri[start]=0;
	poz[start]=0;

	//inserare start in heap
	inserare(heap,costuri[start],start,poz);

	for(int i=1;i<=n-1;i++)
	{
		curent=heap[0].nod;
		//printf("%d\n",curent);
		Decapitare(heap,poz);
		viz[curent]=1;
		//printf("Nodul %d este: %d\n",i,curent);
		for(int j=0;j<la[curent].size();j++)
		{
			vecin = la[curent][j].first;
			cost = la[curent][j].second;
			if(viz[vecin]==0)
			{
				if(costuri[vecin]>cost)
				{
					tata[vecin] = curent;
					costuri[vecin]=cost;
					if(poz[vecin]==-1) // trebuie inserat in heap
						inserare(heap,costuri[vecin],vecin,poz);
					else // se face o reordonare
					{
						heap[poz[vecin]].cost=cost;
						min_heap(heap,poz[vecin],poz);
					}
				}
			}
		}
	}

	for(int i=0;i<=n;i++)
		if(tata[i])printf("%d %d %d\n",i,tata[i],costuri[i]);

}

int main()
{
	freopen("date.in","r",stdin);
	freopen("date.out","w",stdout);
	//declarare variabile
	int n,m,start;
	//vectorul de liste de adiacenta pentru muchii. Pereche de (i,j), cu prop ca i este vecin, j cost
	vector <pair<int, int> > *la;

	//citire numar noduri si muchii;
	scanf("%d%d",&n,&m);

	la=new vector<pair<int, int> >[n+1];
	citire_graf(m,la);

	scanf("%d",&start);

	algoritm(la,n,m,start);
	return 0;
}