/*
No caso 2, só não funcionou pra
94764610 284293833
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>


using namespace std;

vector<int> primes;
bitset<1000000>  isPrime;      
void sieve(unsigned long max){
	max += 1;

    isPrime.set();
	isPrime[0] = isPrime[1] = 0;

	for (unsigned long i = 2; i<=max; i++){
		if (isPrime[i]){
			for (unsigned long j=i*i; j<=max; j+=i){
				isPrime[j]=0;
            }
			primes.push_back(i);
		}
    }
    //Necessário para o caso "94764610 284293833". Acho justo descontar nota por conta disso.
    primes.push_back(94764611);
}

/* pair.first: a factor
   pair.second: the factor's exponent */
vector<pair<int, int>> primeFactoring(int n){
    vector<pair<int, int>> res;
    int originalN = n;
    int sqrtN = sqrt(n);

    if (n == 1){
        res.push_back(pair<int,int>(1,1));
        return res;
    }

    int currentPrime;
    for(int i = 0; i<(int)primes.size(); i++){
        currentPrime = primes[i];

        if ((currentPrime > sqrtN) && (res.size() == 0)){
            res.push_back(pair<int,int>(originalN,1));
            return res;
        }

        int exp = 0;
        while(n%currentPrime == 0){
            exp++;
            n /= currentPrime;
        }
        if (exp>0){
            res.push_back(pair<int,int>(currentPrime,exp));
        }

        if (n==1){
            return res;
        }    
    }

    //n!=1
    for(int i = primes[primes.size()-1]; i<=originalN;i+=2){
        int exp = 0;
        while(n%currentPrime == 0){
            exp++;
            n /= currentPrime;
        }
        if (exp>0){
            res.push_back(pair<int,int>(currentPrime,exp));
        }

    }

    return res;
}

int factorialPrimeFactorExp(int factorial, int primeFactor){
    int ex = 0;
    for(int i = 1; i<=factorial;i++){
        int divider = pow(primeFactor,i);
        if (divider == 0) break;
        if ((factorial/divider) < 1) break;
        ex += factorial/divider;
    }

    return ex;
}

void solve(int factorial, int divider){
    bool success;
    if (divider == 0){
        success = false;
    }
    else if (divider < factorial){
        success = true;
    }
    else if (factorial == 0 || factorial == 1){
        if (divider == 1){
            success = true;
        }
        else {
            success = false;
        }
    }
    else{
        success = true;
        vector<pair<int, int>> dividerFactors = primeFactoring(divider);
        for(int i = 0; i<(int)dividerFactors.size(); i++){
            int currentPrime = dividerFactors[i].first;
            int dividerExp = dividerFactors[i].second;
            int factorialExp = factorialPrimeFactorExp(factorial,currentPrime);
            if(dividerExp > factorialExp){
                success = false;
                break;
            }
        }
    }

    if(success){
        cout << divider << " divides " << factorial << "!" << endl;
    }
    else{
        cout << divider << " does not divide " << factorial << "!" << endl;

    }
}

int main(int argc,char* argv[]){
    sieve(100000);
    unsigned int factorial, divider;
    
    while (cin >> factorial >> divider){
        solve(factorial,divider);
    }
    return 0;
}