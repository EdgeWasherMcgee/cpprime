#include <iostream>
#include <math.h>


class bits{
    public:
        bits(int s){
            size = s;
            arr = (unsigned char*)std::malloc(size/8 + 1);
            if (!arr){
                std::cerr << "Memory could not be allocated";
                std::exit (1);
            }
        }
        ~bits(){
            free(arr);
        }

        void clear(int pos){
            reassignVal(pos, false);
        }

        void set(int pos){
            reassignVal(pos, true);
        }
        void set(int pos, bool val){
            reassignVal(pos, val);
        }
        bool get(int pos){
            return readbit(pos);
        }

        void printArr(int pos1, int pos2){
            for (int i = pos1; i <= pos2; ++i){
                std::cout << readbit(i);
            }
            std::cout << std::endl;
        }
        void printArr(int pos){
            printArr(0, pos);
        }

        void printArr(){
            printArr(0, size - 1);
        }

    private:
        int size;
        unsigned char* arr;
        bool readbit(int pos){
            int cPos = pos / 8;
            int bPos = pos % 8;
            return ((1 << bPos) & arr[cPos]);
        }
        void reassignVal(int pos, bool val){
            int cPos = pos / 8;
            int bPos = pos % 8;
            if (val){
                arr[cPos] |= (1 << bPos);
            }
            else{
                arr[cPos] &= ~(1 << bPos);
            }
        }
};

void firstTest(){
    bits barr(30);
    barr.printArr();
    barr.set(3);
    barr.set(5, 1);
    barr.printArr();
    barr.clear(3);
    barr.printArr();
}

void secondTest(){
    bits barr(100);
    for (int i = 0; i < 100; i++){
        barr.set(i);
        barr.printArr();
    }
    for (int i = 0; i < 100; i++){
        barr.clear(i);
        barr.printArr();
    }
}

int main(){
    secondTest();
    return 0;
}
