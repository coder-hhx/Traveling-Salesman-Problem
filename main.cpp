#include "MCST.h"
#define MaxInt 32767

using namespace std;

int main()
{
	AMGraph G;
	AMGraph EulerG;

	CreateUDN(G);

    cout<<"Display AMGraph:"<<endl<<endl;
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++)
            cout<<"<"<<i+1<<","<<j+1<<">["<<G.arcs[i][j]<<"] \t ";
        cout<<endl;
    }

	EulerG=MST_to_EulerGraph(G,G.vexs[0]);
	cout<<endl;
	cout<<"Display EulerG:"<<endl<<endl;
    for(int i=0;i<EulerG.vexnum;i++)
    {
        for(int j=0;j<EulerG.vexnum;j++)
            cout<<"<"<<i+1<<","<<j+1<<">["<<EulerG.arcs[i][j]<<"] \t ";
        cout<<endl;
    }
    Get_TSP_circuit(EulerG);
}
