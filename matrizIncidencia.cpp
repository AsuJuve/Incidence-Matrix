#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
using std::vector;

int r,c,v1,v2, contLazos = 0, contLadosP = 0, contMatriz = 0;
int mI[100][100], mA[100][100];
int valencias[100];
bool nulo = true, simple = true, completo = false;
vector<int> nodosCaminoS, aristasCamino, nodosCamino;

void menuCaminos();
void mostrarMatrizIncidencia(){
    cout << "\n----------Matriz Incidencia----------\n   ";
    for (int k = 0; k < c; k++)
    {
        cout << "E" << k + 1 << " ";
    }
    cout << "\n";
    for (int i = 0; i < r; i++)
    {
        cout << "V" << i + 1 << " ";
        for (int j = 0; j < c; j++)
        {
            cout << mI[i][j] << "  ";
        }
        cout << "\n";
    }
}
void generarMatrizAdyacencia(){
    for (int i = 0; i < c; i++)
    {
        v1 = -1;
        v2 = -1;
        for (int j = 0; j < r; j++)
        {
            //Si se encuantra un uno, se igual a i o j 
            if (mI[j][i] == 1)
            {
                if (v1 == (-1))
                {
                    v1 = j;
                }
                else
                {
                    v2 = j;
                }
            }
        }

        if (v1 != -1)
        {
            if (v2 != -1)
            {
                mA[v1][v2] += 1;
                valencias[v1] += 1;
                mA[v2][v1] += 1;
                valencias[v2] += 1;
                nulo = false;
                contMatriz +=2;

                if (mA[v1][v2] > 1 or mA[v2][v1] > 1)
                {
                    contLadosP += 1;
                    if (mA[v1][v2] == 2){contLadosP += 1;}
                }
            }
            else
            {
                mA[v1][v1] += 1;
                valencias[v1] += 1;
                nulo = false;
                simple = false;
                contLazos += 1;
                contMatriz += 1;

                if (mA[v1][v1] > 1)
                {
                    contLadosP += 1;
                    if (mA[v1][v1] == 2){contLadosP += 1;}
                }
            }
        }
        else
        {
            if (v2 != -1)
            {
                mA[v2][v2] +=1;
                valencias[v2] += 1;
                nulo = false;
                simple = false;
                contLazos += 1;
                contMatriz += 1;

                if (mA[v2][v2] > 1)
                {
                    contLadosP += 1;
                    if (mA[v2][v2] == 2){contLadosP += 1;}
                }
            }
        }
    }
    if (simple == true and (r*(r-1)) == contMatriz )
    {
        completo = true;
    }

    cout << "\n----------Datos de la Matriz----------\n\n";
    cout << "Grafo Nulo: "; if(nulo){cout<<"Es nulo"<<endl;}else{cout<<"No es nulo"<<endl;}
    if(contLadosP!=0){simple = false;}
    cout << "Grafo Simple: "; if(simple){cout<<"Es simple"<<endl;}else{cout<<"No es simple"<<endl;}
    cout << "Grafo Completo: ";  if(completo){cout<<"Es completo"<<endl;}else{cout<<"No es completo"<<endl;}
    cout << "Lazos: " << contLazos << endl;
    cout << "Lados Paralelos: " << contLadosP << endl;
    cout << "Valencia de cada Vertice: "<<endl;
    for (int i = 0; i < r; i++)
    {
        cout<<" V"<<i+1<<": "<<valencias[i]<<endl;
    }
}
void mostrarMatrizAdyacencia(){
    cout << "\n----------Matriz Adyacencia----------\n   ";
    for (int k = 0; k < r; k++)
    {
        cout << "V" << k + 1 << " ";
    }
    cout << "\n";
    for (int i = 0; i < r; i++)
    {
        cout << "V" << i + 1 << " ";
        for (int j = 0; j < r; j++)
        {
            cout << mA[i][j] << "  ";
        }
        cout << "\n";
    }
}
void imprimirCaminoV(vector<int> &vimprimir){
    cout << " Representado en Vertices\n\t";
    for (int i = 0; i < vimprimir.size(); ++i)
    {
        if (i!=0){cout<<"->";}
        cout<<"V"<<vimprimir[i]+1;
    }
    cout<<endl;
}
void imprimirCaminoA(vector<int> &vimprimir)
{
    cout<<" Representado en Aristas\n\t";
    for (int i = 0; i < vimprimir.size(); ++i)
    {
        if (i!=0){cout<<"->";}
        cout<<"A"<<vimprimir[i]+1;
    }
}
void generarCaminos(int aristaA, int actual, int final, vector<int> &caminosAT, vector<int> &caminosT)
{
    vector<int> posibleA = caminosAT;
    //Esto para que no agregue el primer valor de arista 
    if(aristaA != -1){
        posibleA.push_back(aristaA);
    }

    vector<int> posible = caminosT;
    posible.push_back(actual);

    if (actual == final)
    {
        imprimirCaminoV(posible);
        imprimirCaminoA(posibleA);
        cout << "\n=========================\n";
        return;
    }

    for (int i = 0; i < c; i++)
    {
        if ( mI[actual][i] == 1)
        {
            for (int j = 0; j < r; j++)
            {
                auto it = find(posibleA.begin(), posibleA.end(), i);
                //Ver si en la posicion hay un 1 (indica que la arista es entre ese nodo y otro)
                //Comprobar que el nodo no sea el mismo desde el cual queremos salir
                //Ver que esa arista no a sido agregada
                if (mI[j][i] == 1 and j != actual and (it == posibleA.end()))
                {
                    generarCaminos(i,j,final,posibleA,posible);
                    //i Sera nuestra arista que sera agregada a el vector
                    //j es la columna en la que nos fijaremos ahora
                }
            }
        }
    }
    return;
}
void generarCircuito(int aristaA, int actual, int final, vector<int> &caminosAT, vector<int> &caminosT)
{
    vector<int> posibleA = caminosAT;
    if (aristaA != -1)
    {
        posibleA.push_back(aristaA);
    }

    vector<int> posible = caminosT;
    posible.push_back(actual);

    //Se agrega lo de la aristaA -1, porque al inicio actul y final seran iguales
    if (actual == final and aristaA!= -1)
    {
        imprimirCaminoV(posible);
        imprimirCaminoA(posibleA);
        cout << "\n=========================\n";
        return;
    }

    for (int i = 0; i < c; i++)
    {
        if (mI[actual][i] == 1)
        {
            for (int j = 0; j < r; j++)
            {
                //Verificamos que tenga un 1 (indica arista con ese nodo)
                //Verificamos que no sea el mismo renglon del nodo
                //Verificamos que la arista no este en el vector
                auto it = find(posibleA.begin(), posibleA.end(), i);
                if (mI[j][i] == 1 and j != actual and (it == posibleA.end()))
                {
                    generarCircuito(i, j, final, posibleA, posible);
                }
            }
        }
    }
    return;
}
void generarCaminosSimple(int actual, int final, vector<int> &caminosST)
{
    vector<int> posible = caminosST;
    posible.push_back(actual);

    if (actual == final)
    {
        imprimirCaminoV(posible);
        cout << "\n=========================\n";
        return;
    }
    for (int i = 0; i < r; i++)
    {
        auto it = find(posible.begin(), posible.end(), i);
        //Ver que en la posicion haya un 1 (indica arista entre esos nodos)
        //Ver que el nodo no haya sido agregado a el vector
        if (mA[actual][i] != 0 and (it == posible.end()))
        {
            generarCaminosSimple(i,final,posible);
        }
    }
    return;
}
void generarCircuitoSimple(int aristaA, int anterior, int actual, int final, vector<int> &caminosST)
{
    vector<int> posible = caminosST;
    posible.push_back(actual);

    if (actual == final and aristaA != -1)
    {
        imprimirCaminoV(posible);
        cout << "\n=========================\n";
        return;
    }
    for (int i = 0; i < r; i++)
    {
        auto it = find(posible.begin(), posible.end(), i);
        //Verificar que haya un 1 en la casilla (indica arista entre esos nodos)
        //Indica que al nodo que se quiera ir no sea el anterior
        //Que sea el final o que no se haya aniadido en el vector
        if (mA[actual][i] != 0 and i!= anterior and (i == final or (it == posible.end())) )
        {
            generarCircuitoSimple(aristaA+1,actual,i, final, posible);
        }
    }
    return;
}
void menuPrincipal()
{
    system("cls");
    mostrarMatrizIncidencia();
    generarMatrizAdyacencia();
    mostrarMatrizAdyacencia();
    int opt = -1;
    cout << "\n\nSeleccione una opcion:\n 0.Generar caminos y circuitos\n 1.Salir" << endl;
    cout<<"Opcion: ";cin>>opt;
    switch (opt)
    {
    case 0:
        menuCaminos();
        break;
    case 1:
        return ;
    default:
        menuPrincipal();
        break;
    }
}
void menuCaminos(){
    int opt = -1, v1, v2;
    system("cls");
    cout<<"-----Generar Caminos o Circuitos-----\nQue desea generar:"<<endl;
    cout<<"\t1.Caminos\n\t2.Circuitos\n\t0. Volver al Menu Principal"<<endl;
    cout<<"Opcion: ";cin>>opt;
    cout<<endl;
    switch (opt)
    {
    case 0:
        menuPrincipal();
        break;
    case 1:
        cout<<"Ingrese los Vectores entre los cuales se generarán caminos:"<<endl;
        cout<<"Vector 1: "; cin>>v1;
        cout<<"Vector 2: "; cin>>v2;
        system("cls");
        cout<<"-----Caminos entre V"<<v1+1<<" y V"<<v2+1<<"-----"<<endl;
        cout << "\n----------Caminos----------" << endl;
        generarCaminos(-1, v1-1, v2-1, aristasCamino, nodosCamino);
        cout << "\n----------Caminos Simples----------" << endl;
        generarCaminosSimple(v1-1,v2-1,nodosCaminoS);
        cout << "Ingrese cualquier numero para al menu anterior: ";
        cin.ignore(10, '\n');
        cin.get(); 
        menuCaminos();
        break;
    case 2:
        cout << "Ingrese el Vector desde donde se generaran circuitos:" << endl;
        cout << "Vector: ";
        cin >> v1;
        system("cls");
        cout << "-----Circuitos desde V" << v1 + 1<< "-----" << endl;
        cout << "\n----------Circuitos----------" << endl;
        generarCircuito(-1, v1-1, v1-1, aristasCamino, nodosCamino);
        cout << "\n----------Circuitos Simples----------" << endl;
        generarCircuitoSimple(-1, -1, v1-1, v1-1, nodosCamino);
        cout << "Ingrese cualquier numero para al menu anterior: ";
        cin.ignore(10, '\n');
        cin.get(); 
        menuCaminos();
        break;
    default:
        system("cls");
        menuCaminos();
        break;
    }
}
int main(){
    //Leer datos
    system("cls");
    cout<<"-----MATRICES DE INCIDENCIA Y ADYACENCIA-----"<<endl;
    cout<<" Ingrese los renglones de la Matriz: ";
    cin>>r;
    cout<<" Ingrese las columnas de la Matriz: ";
    cin>>c;
    cout<<" Ingrese la Matriz de Incidencia: \n";
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin>>mI[i][j];
        }
    }
    system("cls");
    menuPrincipal();
    return 0;
}