/*
This is an attempt to showcase the time difference between doing vector multiplications in CPU on single thread, multi-thread, GPU single thread, and GPU multi-thread 
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
#include <cstdlib>

using namespace std;

// Function to initialize vectors to different values.
void initializeBigMatrix(vector<vector<float>>& a) {

}

void initializeSmallMatrix(vector<vector<float>>& a){
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < a[0].size(); j++) { a[i][j] = rand() % 101;}
    }
}

void cpuSingleThread(vector<vector<float>>& a, vector<vector<float>>& b, vector<vector<float>>& c) {
    int row_a = a.size(), col_a = a[0].size(), row_b = b.size(), col_b = b[0].size();

    for(int i = 0; i < row_a; i++) {
        for(int j = 0; j < col_b; j++) {
            for(int k = 0; k < row_b; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void cpuMultiThread1(int i, vector<float>& a, vector<vector<float>>& b, vector<vector<float>>& c) {
    int row_b = b.size(), col_b = b[0].size();

    for(int j = 0; j < col_b; j++) {
        for(int k = 0; k < row_b; k++) {
            c[i][j] += a[k] * b[k][j];
        }
    }
}


int main(int argc, char *argv[]) {
    int row_1, col_1, row_2, col_2;
    char mat_type = *argv[1];

    //for(int i = 0; i < argc; i++) { cout << typeid(*argv[i]).name() << " ";}
    //cout << endl;

    if(mat_type == 's') { 
        row_1 = stoi(argv[2]);
        col_1 = stoi(argv[3]);
        row_2 = stoi(argv[4]);
        col_2 = stoi(argv[5]); 
    }
    
    else if(mat_type == 'b') {
        row_1 = stoi(argv[2]);
        col_1 = stoi(argv[2]);
        row_2 = stoi(argv[2]);
        col_2 = stoi(argv[2]);
    }

    else {
        cout << "Incorrect matrix type. Please input b for big / s for small" << endl;
        cout << "Usage: ./mat-mul <s/b> <matrix_A rows> <matrix_A columns> <matrix_B rows> <matrix_B columns>" << endl;
        throw exception();
    }
    
    if(row_1 != col_2) {
        cout << "Dimension mis-match. Cannot compute vector product..." << endl;
        cout << "Usage: ./mat-mul <s/b> <matrix_A rows> <matrix_A columns> <matrix_B rows> <matrix_B columns>" << endl;
        throw exception();
    }

    vector<vector<float>> mat_A(row_1, vector<float> (col_1));
    vector<vector<float>> mat_B(row_2, vector<float> (col_2));
    vector<vector<float>> result(row_1, vector<float> (col_2));

    srand(time(NULL));

    if(argv[1] == "small") {
        initializeSmallMatrix(mat_A);
        initializeSmallMatrix(mat_B);
    }

    else if(argv[1] == "big") {
        initializeBigMatrix(mat_A);
        initializeBigMatrix(mat_B);
    }

    /*cout << "Matrix A is " << endl;
    for(int i = 0; i < mat_A.size(); i++) {
        for(int j = 0; j < mat_A[0].size(); j++) { cout << mat_A[i][j] << "  ";}
        cout << endl;
    }

    cout << "Matrix B is " << endl;
    for(int i = 0; i < mat_B.size(); i++) {
        for(int j = 0; j < mat_B[0].size(); j++) { cout << mat_B[i][j] << "  ";}
        cout << endl;
    }*/

    // CPU Single Thread
    auto start = chrono::system_clock::now();
    cpuSingleThread(mat_A, mat_B, result);
    auto stop = chrono::system_clock::now();

    /*cout << "Result of CPU single thread multiplication is " << endl;
    for(int i = 0; i < result.size(); i++) {
        for(int j = 0; j < result[0].size(); j++) { cout << result[i][j] << "  ";}
        cout << endl;
    }*/

    chrono::duration<double> total_time = stop - start;
    cout << "Time taken for CPU with single thread: " << total_time.count() * 1000000 << " microseconds" << endl << endl;


    // CPU Multi-Thread
    //Resetting results vector to 0.0
    for(int i = 0; i < result.size(); i++) {
        for(int j = 0; j < result[0].size(); j++) { result[i][j] = 0.0;}
    }

    // Evaluate with one thread evaluating one row of mat_A
    vector<thread> mat_A_rows;

    start = chrono::system_clock::now();
    for(int i = 0; i < mat_A.size(); i++) { mat_A_rows.push_back(thread(cpuMultiThread1, i, ref(mat_A[i]), ref(mat_B), ref(result))); }
    for(int i = 0; i < mat_A.size(); i++) { mat_A_rows[i].join(); }
    stop = chrono::system_clock::now();

    /*cout << "Result of multiplication with " << mat_A.size() << " threads is " << endl;
    for(int i = 0; i < result.size(); i++) {
        for(int j = 0; j < result[0].size(); j++) { cout << result[i][j] << "  ";}
        cout << endl;
    }*/

    total_time = stop - start;
    cout << "Time taken for CPU with " << mat_A.size() << " threads: " << total_time.count() * 1000000 << " microseconds" << endl << endl;

    return 0;
}