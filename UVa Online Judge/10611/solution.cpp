#include <iostream>
#include <vector>

using namespace std;

class PlayboyChimpProblem{
    public:
        PlayboyChimpProblem(vector<int> options, int height){
            this->options = options;
            this->height = height;
        }

        void solve(){
            binarySearchSolution(height,0,options.size()-1);
        }


    private:
        void binarySearchSolution(int value, int min, int max){
            bool foundAnswer = false;
            int leftAnswer  = -1,
                rightAnswer = -1;

            if (height > options[options.size() - 1]){
                foundAnswer = true;
                leftAnswer = options[options.size() - 1];
            }
            else if (height < options[0]){
                foundAnswer = true;
                rightAnswer = options[0];
            }

            /*O algoritmo faz uma busca binária iterativa. Se o valor for encontrado, então é procurado
            à sua esquerda o primeiro valor menor que ele, e, à sua direita, o primeiro maior.*/

            while(!foundAnswer){
                int mid = (min+max)/2;
                
                if(options[mid] == height){
                    foundAnswer = true;
                    int i;
                    for(i = mid+1; (unsigned(i)<options.size()), (options[i] <= height);i++);
                    if (unsigned(i) < options.size()){
                        rightAnswer = options[i];
                    }
                    int j;
                    for(j = mid-1; options[j] >= height; j--);
                    if (i >= 0){
                        leftAnswer = options[j];
                    }
                }

                /*O subvetor analisado tem tamanho pequeno o suficiente para termos certeza de que
                é o mais próximo da resposta possível.*/
                else if((max-min) <= 1){
                    foundAnswer = true;
                    if(options[mid] > height){
                        rightAnswer = options[mid];
                        int i;
                        for(i = mid-1; (i >= 0), (options[i] >= height);i--);
                        if (i >= 0){
                            leftAnswer = options[i];
                        }
                    }
                    else{ //options[mid] < height
                        leftAnswer = options[mid];
                        int i;
                        for(i = mid+1; (unsigned(i)<options.size()), (options[i] <= height);i++);
                        if (unsigned(i) < options.size()){
                            rightAnswer = options[i];
                        }
                        
                    }
                }
                else if (options[mid] > height){
                    max = mid;
                }
                else if (options[mid] < height){
                    min = mid;
                }
            }

            if(leftAnswer != -1){
                cout << leftAnswer << " ";
            }
            else{
                cout << "X ";
            }

            if(rightAnswer != -1){
                cout << rightAnswer << endl;
            }
            else{
                cout << "X" << endl;
            }
        }


        vector<int> options;
        int height;
};

int main (int arcg, char* argv[]){
    int numOptions, numHeights;
    cin >> numOptions;

    vector<int> options;
    for (int i = 0; i<numOptions; i++){
        int option;
        cin >> option;
        options.push_back(option);
    }

    cin >> numHeights;
    for (int i = 0; i<numHeights; i++){
        int height;
        cin >> height;
        PlayboyChimpProblem p = PlayboyChimpProblem(options,height);
        p.solve();
    }

    return 0;
}