#ifndef MCST_H_INCLUDED
#define MCST_H_INCLUDED

#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include "stdlib.h"
#include <ctime>
#include <sstream>
#include <iostream>

#define MVNum 400
#define MaxInt 32767

using namespace std;

bool visited[MVNum];
typedef string VerTexType;
typedef int ArcType;

typedef struct      //图的邻接矩阵
{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum;
} AMGraph;

typedef struct     //普里姆算法辅助数组
{
    VerTexType adjvex;
    ArcType lowcost;
} Node, closedge[MVNum];

int LocateVex(AMGraph& G, VerTexType v)    //查询顶点下标
{
    for (int i = 0; i < G.vexnum; i++)
        if (G.vexs[i] == v)
            return i;
    return -1;
}

int Min(closedge& c)
{
    int i;
    int min;
    int j;
    for (i = 0; i < MVNum; i++)
    {
        if (c[i].lowcost != 0)
        {
            min = c[i].lowcost;
            j = i;
            break;
        }
    }
    for (i = 0; i < MVNum; i++)
    {
        if (c[i].lowcost != 0 && c[i].lowcost < min)
        {
            min = c[i].lowcost;
            j = i;
        }
    }
    return j;
}

void CreateUDN(AMGraph& G)      //创建无向网
{
    srand((unsigned)time(NULL));
    int num;
    cout<<"please input the quantity of city:";
    cin>>num;
    cout<<endl;
    G.vexnum=num;
    G.arcnum=num*(num-1)/2;
    for(int i=0; i<G.vexnum; i++)
    {
        stringstream ss;
        string b = "city";
        ss << b << (i+1);
        G.vexs[i]= ss.str();
    }
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)
            G.arcs[i][j]=MaxInt;
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)
        {
            if(i<j)
                G.arcs[j][i]=G.arcs[i][j]=rand()%100+1;
        }
}

AMGraph MST_to_EulerGraph(AMGraph& G, VerTexType u)   //生成最小生成树转为欧拉图
{
    AMGraph EulerG;
    int i, j;
    int m, n;
    int k = LocateVex(G, u);
    closedge c;
    EulerG.vexnum = G.vexnum;
    EulerG.arcnum = 0;
    for (m = 0; m < EulerG.vexnum; m++)
    {
        for (n = 0; n < EulerG.vexnum; n++)
            EulerG.arcs[m][n] = 0;
        EulerG.vexs[m] = G.vexs[m];
    }
    for (i = 0; i < MVNum; i++)
        c[i].lowcost = MaxInt;
    for (j = 0; j < G.vexnum; j++)
    {
        if (j != k)
        {
            c[j].adjvex = u;
            c[j].lowcost = G.arcs[k][j];
        }
    }
    c[k].lowcost = 0;
    for (i = 1; i < G.vexnum; i++)
    {
        k = Min(c);
        VerTexType u0 = c[k].adjvex;
        VerTexType v0 = G.vexs[k];
        m = LocateVex(G, u0);
        n = LocateVex(G, v0);
        EulerG.arcs[m][n] = EulerG.arcs[n][m] = 1;
        EulerG.arcnum++;
        c[k].lowcost = 0;
        for (j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[k][j] < c[j].lowcost)
            {
                c[j].adjvex = G.vexs[k];
                c[j].lowcost = G.arcs[k][j];
            }
        }
    }
    return EulerG;
}

void Get_TSP_circuit(AMGraph& EulerG)
{
    VerTexType Eul_cir[4 * EulerG.arcnum];
    VerTexType TSP_cir[MVNum + 1];
    VerTexType Stack[EulerG.vexnum];
    int top = -1;
    int i = 0;
    int n = 0;
    int x = 0;
    for (int m = 0; m < EulerG.vexnum; m++)
        visited[m] = false;
    Stack[++top] = EulerG.vexs[0];
    Eul_cir[n] = EulerG.vexs[0];
    visited[0] = true;
    while (top != -1)
    {
        bool flag = true;
        i = LocateVex(EulerG, Stack[top]);
        for (int j = 0; j < EulerG.vexnum; j++)
        {
            if (EulerG.arcs[i][j] == 1 && !visited[j])
            {
                Stack[++top] = EulerG.vexs[j];
                Eul_cir[++n] = EulerG.vexs[j];
                visited[j] = true;
                flag = false;
                break;
            }
        }
        if (flag)
        {
            top--;
            if (top != -1)
                Eul_cir[++n] = Stack[top];
        }
    }

    for (int m = 0; m < EulerG.vexnum; m++)
        visited[m] = false;
    for (int k = 0; k <= n; k++)
    {
        i = LocateVex(EulerG, Eul_cir[k]);
        if (!visited[i])
        {
            TSP_cir[x++] = EulerG.vexs[i];
            visited[i] = true;
        }
    }
    TSP_cir[x] = TSP_cir[0];
    cout << endl << endl;
    cout << "Display TSP_circuit:" << endl << endl;
    for (int k = 0; k <= x; k++)
    {
        cout << TSP_cir[k] << " ";
        if(k < x)
            cout << "-> ";
    }
    cout << endl;
}

#endif // MCST_H_INCLUDED
