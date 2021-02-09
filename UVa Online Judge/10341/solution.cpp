#include <iostream>
#include <cmath>
#include <cstdio>
#define FLOAT_COMPARISON_EPSILON 0.000000001;

using namespace std;

/*Compara dois doubles utilizando a precisão FLOAT_COMPARISON_EPSILON.
Um epsilon menor implica em uma corretude maior, mas, ao custo de uma execução
mais lenta.*/
bool fequals(double a, double b){
    return fabs(a-b) < FLOAT_COMPARISON_EPSILON;
}


class Problem{
    public:

        Problem (int p, int q, int r, int s, int t, int u){
            this->p = (double)p;
            this->q = (double)q;
            this->r = (double)r;
            this->s = (double)s;
            this->t = (double)t;
            this->u = (double)u;
        }


        /*Essa solução realiza uma espécie de "busca binária" (método da bisecção) com os valores 
        dentro do intervalo das respostas possíveis, até chegar no ponto onde a expressão vale 0.*/
        void solve(){

            if(!isSolvable()){
                cout << "No solution" << endl;
                return;
            }

            double min = 0,
                  max = 1,
                  mid;

            while(!fequals(max-min,0)){
                mid = (min+max)/2;
                double expValue = eval(mid);

                
                if(expValue > 0){
                    min = mid;
                }
                else{ //expValue < 0
                    max = mid;
                }
            }

            printf("%.4f\n",mid);
            
        }
    
    private:

        /*Define se existe raiz para a equação entre 0 e 1.
        Se f(0) e f(1) forem ambas positivas ou ambas negativas, o produto entre elas é maior que 0.
        Nesses casos, a função não passa por 0 nesse intervalo, logo, a não há raiz nele.*/
        bool isSolvable(){
            return eval(0) * eval(1) <= 0;
        }

        double eval (double x){
            return p*(exp(-x)) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
        }


        double p, q, r, s, t, u;
};

int main(int argc, char* argv[]){
    int p, q, r, s, t, u;
    while(cin >> p >> q >> r >> s >> t >> u){
        Problem pr = Problem(p,q,r,s,t,u);
        pr.solve();
    }
    return 0;
}