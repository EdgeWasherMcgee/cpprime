#include <fstream>
#include <iostream>

class bits{
    public:
        explicit bits(const size_t& s){
            size = s;
            arr = new unsigned char[size/8 + 1];
            if (!arr){
                std::cerr << "Memory could not be allocated";
                std::exit (1);
            }
        }
        ~bits(){
            delete[] arr;
        }

        void clear(const int& pos){
            reassignVal(pos, false);
        }

        void set(const int& pos){
            reassignVal(pos, true);
        }
        void set(const int& pos, bool val){
            reassignVal(pos, val);
        }
        bool get(const int& pos){
            return readbit(pos);
        }

        void printArr(const int& pos1, const int& pos2){
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
        size_t size;
        unsigned char* arr;
        bool readbit(int pos){
            int cPos = pos / 8;
            int bPos = pos % 8;
            return ((1 << bPos) & arr[cPos]);
        }
        unsigned char* readbyte(const int& pos){
            int cPos = pos / 8;
            static unsigned char bitsInByte[8];
            for (int i = 0; i < 8; i++){
                bitsInByte[i] = readbit(cPos + i);
            }
            return bitsInByte;
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

void delChain(bits* checklist, unsigned int high, unsigned int cur){
    unsigned int start = cur * 2 + 3;
    for (unsigned int z = start; z < high; z = z + start * 2){
        checklist->clear((z - 3)/2);
    }
}
unsigned int next(bits* checklist,unsigned int cur){
    while (!checklist->get(cur)){
        cur++;
    }
    return cur;
}

unsigned int prime(unsigned int high){
    std::ofstream f;
    f.open ("primes.txt");
    f << 2 << std::endl;
    bits *checklist = new bits(high/2);
    for (unsigned int i = 0; i <= (high - 3)/2; i++){
        checklist->set(i, 1);
    }
    unsigned int cur;
    for (cur = 0; cur < (high - 3)/2;){
        f << cur * 2 + 3 << std::endl;
        delChain(checklist, high, cur);
        cur = next(checklist, cur);
    }
    f.close();
    delete checklist;
    return cur;
}

int main(int argc, char* argv[]){
    unsigned int high = 10000000;
    unsigned int highest;
    highest = prime(high);
    std::cout << highest << std::endl;
    return 0;
}
