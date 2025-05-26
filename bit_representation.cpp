/* 
* Playing around with bit representations
* 
* Compilation command: g++ .\bit_representation.cpp -o bit-wise
* 
* Usage:
*     Left-Right Shift: ./bit_wise lrShift <decimal_number> <left / right>
*     Decimal to Binary w/ division method: ./bit-wise division <decimal_number>
*     Decimal to Binary w/ bit shift method: ./bit-wise bitShift <decimal_number> <queue / stack>
*/ 

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;


// The 'divisionMethod' function converts decimal to binary by
// dividing by 2 and adding the remainder (either 0 or 1) to a
// string. That string is then reversed to get binary representation.
void divisionMethod(int num) {
    string binary = "";

    cout << "Binary of " << num << " is ";

    while(num) {
        //if(num % 2) { binary += '1'; }
        //else { binary += '0'; }

        binary += (num % 2) + '0';

        num /= 2;
    }

    reverse(binary.begin(), binary.end());

    cout << binary << endl;
}


// Convert decimal to binary by shifting bits.
//
// While using stack, getting each LSB works, 
// as popping from top gives bits in correct order. 
//
// While using queue, need to get MSB first to get
// bits in correct order when popping from the front.
void bitShiftMethod(int num, string method) {
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

    else { cout << "Method not recognized. Please enter 'queue' for queue or 'stack' for stack.." << endl; }
}


// Function to showcase what left-shifting and 
// right-shifting binary numbers does
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
    
    else { cout << "Direction not recognized. Please enter 'left' for left shift or 'right' for right shift.." << endl; }
}


int main(int argc, char *argv[]) {

    auto print_usage = []() {
        cout << "Usage: " << endl;
        cout << "Left-Right Shift: ./bit_wise lrShift <decimal_number> <left / right>" << endl;
        cout << "Decimal to Binary w/ division method: ./bit-wise division <decimal_number>" << endl;
        cout << "Decimal to Binary w/ bit shift method: ./bit-wise bitShift <decimal_number> <queue / stack>" << endl;
    };

    if(argc < 3) { 
        cout << "Please provide all the necessary arguments.." << endl;
        print_usage();
        return 1;
    }

    string method = argv[1];
    int dec_num = stoi(argv[2]);
    
    if(method == "lrShift") {
        if(argc < 4) {
            cout << "Please specify left shift or right shift.." << endl;
            print_usage();
            return 1;
        }

        leftRightShift(dec_num, argv[3]);
    }
    
    else if(method == "division") { divisionMethod(dec_num); }

    else if(method == "bitShift") { 
        if(argc < 4) {
            cout << "Please specify division using queue or stack.." << endl;
            print_usage();
            return 1;
        }

        bitShiftMethod(dec_num, argv[3]);
    }

    else {
        cout << "Method not recognized. Please enter 'lrShift', 'division', or 'bitShift'.." << endl;
        print_usage();
    }

    return 0;
}