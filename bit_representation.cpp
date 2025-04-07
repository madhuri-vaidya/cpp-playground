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

void bitShiftMethod(int num, string method) {
    //char method = 'q' for queue, 'd' for display as is
    bool leadingZeros = true;

    if(method == "queue") {
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

    else if(method == "stack") {
        stack<int> bits;
        while(num) {
            bits.push(num & 1);
            num = num >> 1;
        }

        while(!bits.empty()){
            cout << bits.top() << " ";
            bits.pop();
        }
    }

    else { cout << "Method not recognized. Please enter 'q' for queue or 'd' for display as is.." << endl; }
}

void leftRightShift(int dec_num, string direction) {
    cout << "Entered integer " << dec_num << endl;

    if(direction == "left") {
        int left_shit = dec_num << 1;
        cout << dec_num << " left shifted (<<) by 1 is " << left_shit << endl;
    }

    else if(direction == "right") {
        int right_shift = dec_num >> 1;
        cout << dec_num << " right shifted (>>) by 1 is " << right_shift << endl;
    }
    
    else { cout << "Direction not recognized. Please enter 'l' for left shift or 'r' for right shift.." << endl; }
}

int main(int argc, char *argv[]) {
    string method = argv[1];
    int dec_num = stoi(argv[2]);
    cout << "size of integer is " << sizeof(dec_num) << endl;
    
    if(method == "lrShift") { leftRightShift(dec_num, argv[3]); }
    
    else if(method == "division") { divisionMethod(dec_num); }

    else if(method == "bitShift") { bitShiftMethod(dec_num, argv[3]); }

    else {
        cout << "Usage: " << endl;
        cout << "Left-Right Shift: ./bit_wise lrShift <decimal_number> <left / right>" << endl;
        cout << "Decimal to Binary w/ division method: ./bit-wise division <decimal_number>" << endl;
        cout << "Decimal to Binary w/ bit shift method: ./bit-wise bitShift <decimal_number> <queue / stack>" << endl;
    }

    return 0;
}