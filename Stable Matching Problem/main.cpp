/*
Default test case:

2
4
1 4 3 1 2
2 2 1 3 4
3 1 3 4 2
4 4 3 1 2
1 3 2 4 1
2 2 3 1 4
3 3 1 2 4
4 3 2 4 1
7
1 3 4 2 1 6 7 5
2 6 4 2 3 5 1 7
3 6 3 5 7 2 4 1
4 1 6 3 2 4 7 5
5 1 6 5 3 4 7 2
6 1 7 3 4 5 6 2
7 5 6 2 4 3 7 1
1 4 5 3 7 2 6 1
2 5 6 4 7 3 2 1
3 1 6 5 4 3 7 2
4 3 5 6 7 2 4 1
5 1 7 6 4 3 5 2
6 6 3 7 5 2 4 1
7 1 7 4 2 6 5 3

*/

#include <iostream>
#include <cstring>
#include <list>
#include <map>
#include <queue>

using namespace std;

class StableMarriageProblem {
    public:

        StableMarriageProblem(){
            cin >> numMarriages;
            readWomenPreferences();
            readMenPreferences();
        }

        void solve(){
            int currentMan = getNextMan();
            while(currentMan != NO_MAN_REMAINING){
                int currentWoman = getNextWoman(currentMan);

                if(!isWomanMarried(currentWoman)){
                    engage(currentMan,currentWoman);
                }
                else if (womanPrefersManToCurrentHusband(currentWoman,currentMan)){
                    makeManSingle(womenMarriages[currentWoman]);
                    engage(currentMan,currentWoman);

                }

                currentMan = getNextMan();
            }
        }

        void printResults(){
            for(int i = 1; i<=numMarriages; i++){
                cout << i << " " << menMarriages[i] << endl;
            }
        }

    private:

        void readMenPreferences(){
            for(int i = 1; i<=numMarriages; i++){
                int currentMan, preference;
                cin >> currentMan;
                for (int j=1;j<numMarriages+1;j++){
                    cin >> preference;
                    menPreferences[currentMan].push(preference);
                }
            }
        }

        void readWomenPreferences(){
            for(int i = 1; i<=numMarriages; i++){
                int currentWoman, preference;
                cin >> currentWoman;
                for (int j=1;j<numMarriages+1;j++){
                    cin >> preference;
                    womenPreferences[currentWoman].push_back(preference);
                }
            }
        }

        int getNextMan(){
            for(int i = 1; i<=numMarriages; i++){
                if (!isManMarried(i) && !hasManProposedToEveryone(i)){
                    return i;
                }
            }
            return NO_MAN_REMAINING;
        }

        bool isManMarried(int currentMan){
            return !(menMarriages.find(currentMan) == menMarriages.end());
        }

        bool hasManProposedToEveryone(int currentMan){;
            return menPreferences[currentMan].empty();
        }

        int getNextWoman(int currentMan){
            int nextWoman = menPreferences[currentMan].front();
            menPreferences[currentMan].pop();
            return nextWoman;
        }

        bool isWomanMarried(int currentWoman){
            return !(womenMarriages.find(currentWoman) == womenMarriages.end());
        }

        void engage(int currentMan, int currentWoman){
            menMarriages[currentMan] = currentWoman;
            womenMarriages[currentWoman] = currentMan;
        }

        void makeManSingle(int currentMan){
            menMarriages.erase(currentMan);
        }

        bool womanPrefersManToCurrentHusband(int currentWoman, int currentMan){
            int currentHusband = womenMarriages[currentWoman];
            list<int>::iterator i;
            for (i = womenPreferences[currentWoman].begin(); i != womenPreferences[currentWoman].end(); i++){
                int currentManOption = *i;
                if (currentManOption == currentHusband){//Husband comes first in the preference list
                    return false;
                }
                else if (currentManOption == currentMan){//Current man comes first in the preference list
                     return true;
                }
            }
            return false;
        }

        int numMarriages;
        map<int,int> menMarriages;
        map<int,int> womenMarriages;
        map<int,queue<int>> menPreferences;
        map<int,list<int>> womenPreferences;
        static const int NO_MAN_REMAINING = -1;
};    


int main(int argc, char* argv[]){
    int numTestCases;
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; i++) {
        StableMarriageProblem* p = new StableMarriageProblem();
        p->solve();
        p->printResults();
        delete p;
    }
    return 0;
}
