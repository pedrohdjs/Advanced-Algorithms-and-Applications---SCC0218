#include <iostream>
#include <vector>

using namespace std;

class CoinCollectorProblem{

    public:
        CoinCollectorProblem(){
            coinsUsed = 2;//First and last coins are always used
            cin >> numCoins;
            for (int i = 0; i < numCoins; i++){
                int newCoin;
                cin >> newCoin;
                coins.push_back(newCoin);
            }
        }

        void solve(){
            int s = coins[0];//First coin is already included in the answer
            for (int i = 1; i < numCoins - 1; i++){
                /*if s + coins[i] >= coins i+1, coin i+1 will be given and all or most of the coins already
                included will be discarded, so, coin i is not in the answer*/
                if(s + coins[i] < coins[i+1]){//Coin is included in the answer
                    s += coins[i];
                    coinsUsed++;
                }
            }
        }

        void printResults (){
            cout << coinsUsed << endl;
        }

    private:
        int numCoins;
        int coinsUsed;
        vector<int> coins;
        
};

int main(int argc, char* argv[]){
    int numTestCases;
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; i++) {
        CoinCollectorProblem* p = new CoinCollectorProblem();
        p->solve();
        p->printResults();
        delete p;
    }
    return 0;
}