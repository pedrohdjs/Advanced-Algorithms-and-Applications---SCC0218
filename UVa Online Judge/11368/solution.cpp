#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <map>

using namespace std;

/*
4
3
20 30 40 50 30 40
4
20 30 10 10 30 20 40 50
3
10 30 20 20 30 10
4
10 10 20 30 40 50 39 51
*/

struct doll {
    int width, height;

    bool operator==(const doll &b) const{
        return (width == b.width && height == b.height);
    }

    bool operator<(const doll &b) const{
        return (width < b.width) && (height < b.height);//doll fits into the other
    }

    doll& operator=(const doll& b){
        width= b.width;
        height= b.height;
        return *this;
    }


};

//Order dolls with crescent width and decrescent height if tied in width
bool compareDoll(const doll &a, const doll &b)
{
    return (a.width != b.width) ? (a.width < b.width) : (a.height > b.height);
}


class Problem{
    public:
        Problem(vector<int> widths, vector<int> heights){
            this->numDolls = heights.size();
            for (int i = 0; i<numDolls;i++){
                doll currentDoll;
                currentDoll.height = heights[i];
                currentDoll.width = widths[i];
                this->dolls.push_back(currentDoll);
            }
            sort(this->dolls.begin(),this->dolls.end(),compareDoll);
            mem.push_back(this->dolls[0]);
        }

        void solve(){
            for (int i = 1; i<numDolls;i++){//Doll 0 was already placed
                doll currentDoll = dolls[i];
                placeIntoBestAnswer(currentDoll);
            }
            cout << mem.size() << endl;

        }

    private:
        void placeIntoBestAnswer(doll currentDoll){
            int memIndex = 0;
            while (memIndex < (int)mem.size()){
                if (mem[memIndex] < currentDoll){//The doll in mem[memIndex] fits in the current doll
                    mem[memIndex] = currentDoll;
                    return;
                }
                else{ //The doll in mem[memIndex] does not fit in the current doll
                    memIndex++;
                }
            }
            mem.push_back(currentDoll);
            
        }

        
        vector<doll> dolls;
        vector<doll> mem;
        int numDolls;
};

int main(int argc, char* argv[]){
    int numTestCases;
    cin >> numTestCases;

    for (int i = 0; i<numTestCases;i++){
        int numDolls;
        cin >> numDolls;
        vector<int> dollsWidths;
        vector<int> dollsHeights;
   
        for(int j = 0; j<numDolls;j++){
            int width, height;
            cin >> width >> height;
            dollsWidths.push_back(width);
            dollsHeights.push_back(height);
        }
        Problem p = Problem(dollsWidths, dollsHeights);
        p.solve();
    }
    return 0;
}