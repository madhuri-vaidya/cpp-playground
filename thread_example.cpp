#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

mutex g_lock;
static int shared_value = 0;

void test(int x) {
    cout << "Hello from thread!" << endl;
    cout << "Argument passed in " << x << endl;
}

void shared_value_increment() {
    lock_guard<mutex> lock_guard(g_lock);
    //g_lock.lock();
        shared_value++;
    //g_lock.unlock();
}

int main() {

    auto lambda=[](int x) {
        cout << "Hello from thread " << this_thread::get_id() << endl;
        cout << "Argument passed in " << x << endl << endl;
    };

    //thread my_thread(lambda, 100);
    //thread my_thread(test, 100);
    //my_threads.join();

    vector<thread> my_threads;
    int num_threads = 1000;

    for(int i = 0; i < num_threads; i++) { my_threads.push_back(thread(shared_value_increment)); }

    for(int i = 0; i < num_threads; i++) { my_threads[i].join(); }

    cout << shared_value << endl;

    return 0;
}