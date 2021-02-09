#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int numDigits(int n){
    int res = 0;
    int aux = n;
    while(aux != 0){
        aux /= 10;
        res++;
    }
    return res;
}

vector<int> sieve(int n){
    vector<bool> isNumberPrime;//isNumberPrime[i] is true if i is prime
    for(int i = 0; i<= n; i++) isNumberPrime.push_back(true);
    for(int i = 2; i*i<=n;i++){
        if (isNumberPrime[i]){
            for(int j = i*i; j<=n;j+=i){
                isNumberPrime[j]=false;
            }
        }
    }
    vector<int> res;
    for(int i = 2;i<= n; i++){
        if(isNumberPrime[i]) res.push_back(i);
    }
    return res;
}

void printFormattedNumber(int n){
    int digits = numDigits(n);
    if (digits == 2) cout << ' ';
    else if (digits == 1) cout << ' ' << ' ';
    cout << n;
}

void printAnswer(int n,vector<int> numPrimes){
    printFormattedNumber(n);
    cout << "! =";
    int count = 0;
    for (int i = 0; i<=(int)numPrimes.size();i++){
        if (numPrimes[i] == 0) break;
        if (count == 15){
            cout << endl << "      ";
            count = 0;
        }
        printFormattedNumber(numPrimes[i]);
        count++;
    }
    cout << endl;

}


void solve(int n, vector<int> primes){
        vector<int> numPrimes;
        for(int i = 0; i<(int)primes.size();i++) numPrimes.push_back(0);
        for(int i = 2; i<=n; i++){
            int aux = i;
            int primeIndex = 0;
            while (aux != 1){
                if(aux%primes[primeIndex] == 0){
                    numPrimes[primeIndex]++;
                    aux = aux/primes[primeIndex];
                }
                else{
                    primeIndex++;
                }
            }
        }
        printAnswer(n,numPrimes);
}

int main(int argc, char* argv[]){
    int n;
    vector<int> inputs;
    int largestInput = 0;
    while (cin >> n){
        if (n == 0) break;
        if (n>largestInput) largestInput = n;
        inputs.push_back(n);
    }
    vector<int> primes = sieve(largestInput);
    for(int i = 0; i<(int)inputs.size();i++){
        solve(inputs[i],primes);
    }
    return 0;
}