// Playing around with bit representations

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

void divisionMethod(int num) {
    string binary = "";

    cout << "Binary of " << num << " is ";

    while(num) {
        if(num % 2) { binary += '1'; }
        else { binary += '0'; }
        num /= 2;
    }

    reverse(binary.begin(), binary.end());

    cout << binary << endl;
}

void bitShiftMethod(int num, char method) {
    //char method = 'q' for queue, 'd' for display as is
    bool leadingZeros = true;

    if(method == 'q') {
        queue<int> bits;

        for(int i = sizeof(num) * 8 - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if(bit) { leadingZeros = false; }
            if(!leadingZeros) {
                bits.push(bit);
            }
        }

        while(!bits.empty()) {
            cout << bits.front() << " ";
            bits.pop();
        }
    }

    else if(method == 'd') {
        for(int i = sizeof(num) * 8 - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if(bit) { leadingZeros = false; }
            if(!leadingZeros) { cout << bit << " "; }
        }
    }

    else { cout << "Method not recognized. Please enter 'q' for queue or 'd' for display as is.." << endl; }
}


int main(int argc, char *argv[]) {

    int dec_num = stoi(argv[1]);

    /*
    cout << "Entered integer " << dec_num << endl;
    int left_shit = dec_num << 1;
    cout << dec_num << " left shifted (<<) by 1 is " << left_shit << endl;
    int right_shift = dec_num >> 1;
    cout << dec_num << " right shifted (>>) by 1 is " << right_shift << endl;
    */
    
    cout << "size of integer is " << sizeof(dec_num) << endl;
    
    //divisionMethod(dec_num);
    bitShiftMethod(dec_num, argv[2][0]);

    return 0;
}