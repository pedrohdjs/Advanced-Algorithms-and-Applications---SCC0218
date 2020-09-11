#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

namespace myFunctions {

    float abs(float value){
        if (value >= 0) return value;
        return -(value);
    }

}
using namespace std;

class StationBalanceProblem{
    public:
        StationBalanceProblem(int numChambers, vector<int> specimens){
            this->numChambers = numChambers;
            numSpecimens = 2*numChambers;
            this->specimens = specimens;
            
            for (int i = 0; i<numChambers; i++){
                vector<int> newVector;
                chambers.push_back(newVector);//Initialize chambers vector
                chambersMass.push_back(0);//Initialize chambers mass
            }

            float totalMass = 0;
            for (int i = 0; i<numSpecimens;i++){
                totalMass += specimens[i];
            }
            averageMass = totalMass/(float)numChambers;
        }

        void showAnswer(int numSet){
            cout << "Set #" << numSet << endl;
            for(int i = 0;i<numChambers;i++){
                cout << " " << i << ": ";
                for(int j = 0; j<(int)chambers[i].size(); j++)
                    cout << chambers[i][j] << " ";
                cout << endl;
            }
            printf("IMBALANCE = %.5f\n\n",imbalance());
        }

        
        void solve(){
            /*Since the specimens are sorted, the greedy approach to get the smalles inbalance 
            is pairing them like this (iterating from start to mid and from end to mid at the
            same time, creating pairs with a mass sum close to the chamber average). */
            for(int i = 0; i<numChambers; i++){
                /*This validation is important since "invalid" (mass=0) specimens are added
                in order to make the number of specimens equal to 2 times the number of chambers
                and prevent segmentation fault errors.*/
                if (isValidSpecimen(specimens[i])){
                    assignSpecimenToChamber(specimens[i],i);
                }
                if (isValidSpecimen(specimens[numSpecimens-1-i])){
                assignSpecimenToChamber(specimens[numSpecimens-1-i],i);
                }
            }
        }

    private:

        bool isValidSpecimen(int specimen){
            return specimen>0;
        }

        void assignSpecimenToChamber(int specimen, int chamber){
            chambers[chamber].push_back(specimen);
            chambersMass[chamber] += specimen;
        }

        float imbalance(){
            float imbalance = 0;
            for(int i = 0;i<numChambers;i++){
                imbalance += myFunctions::abs(chambersMass[i] - averageMass);
            }
            return imbalance;
        }
    
        int numChambers, numSpecimens;
        vector<int> specimens;
        vector<float> chambersMass;
        vector<vector<int>> chambers;
        float averageMass;
};

int main(int argc, char *argv[]){
    int numChambers, numSpecimens;
    vector<int> specimens;
    int currentSet = 1;
    while(cin >> numChambers >> numSpecimens){
        for (int i = 0; i<numSpecimens; i++){
            int currentSpecimen;
            cin >> currentSpecimen;
            specimens.push_back(currentSpecimen);
        }
        //Make the number of specimens equal to 2*numChambers, by adding "empty" specimens
        while((int)specimens.size()<2*numChambers) specimens.push_back(0);
        sort(specimens.begin(),specimens.end());
        StationBalanceProblem* p = new StationBalanceProblem(numChambers,specimens);
        p->solve();
        p->showAnswer(currentSet);
        delete p;
        specimens.clear();
        currentSet++;
    }
    return 0;
}