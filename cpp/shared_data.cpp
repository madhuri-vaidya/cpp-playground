/*
* This is an experiment with different multi-threading techniques: atomic variable, lock guard, and mutex.
*
* Compilation command: g++ ./shared_data.cpp -o shared_data
*
* Usage: ./shared_data <basic / atomic / mutex> <num_threads>
*   basic: Spawn threads and display message from them
*   atomic: Spawn threads and update shared normal_int and a shared atomic_int
*   mutex: Spawn threads and update shared int with mutex
*   lock_guard: Spawn threads and update shared int with lock_guard
*/

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>
#include <vector>

using namespace std;

class ThreadApp {
  
  private:
    const int ITERATIONS = 1E6;

    int general_counter = 0;
    atomic<int> atomic_counter = 0;
    
    mutex mtx;
	
  public:
    void operator()() { cout << "Hello, ThreadApp instance created..." << endl; }

    int getCounter() { return general_counter; }

    int getAtomicCounter() { return atomic_counter.load(); }

    // Display message from each thread
    void workBasicMultithreading(int id, int iter) {
      for(int i = 0; i < iter; i++) {
        cout << "Thread " << id << " loop " << i << endl;
	      this_thread::sleep_for(chrono::milliseconds(500));
      }
    }

    // Update shared normal_int and atomic_int
    void workAtomic(){
      for(int i = 0; i < ITERATIONS; i++) {
        general_counter++;
	      atomic_counter++;
      } 
    }

    // Update shared int with mutex
    void workMutex() {
     for(int i = 0; i < ITERATIONS; i++) {
       mtx.lock();
       general_counter++;
       mtx.unlock();
     } 
    }

    // Update shared int with lock_guard
    void workLockGuard() {
      for(int i = 0; i < ITERATIONS; i++) {
        lock_guard<mutex> guard(mtx);
	      general_counter++;
      }
    }
};


void basicMultithreading(ThreadApp& app, vector<thread>& threads, int& num_threads) {

  int num_iterations = 10;
  
  for(int i = 0; i < num_threads; i++) {
    threads.push_back(thread(&ThreadApp::workBasicMultithreading, &app, i, num_iterations));
  }

  for(int i = 0; i < num_threads; i++) {
    threads[i].join();
  }

}


void atomicCounter(ThreadApp& app, vector<thread>& threads, int& num_threads) {
  
  for(int i = 0; i < num_threads; i++) { threads.push_back(thread(&ThreadApp::workAtomic, &app)); }

  for(int i = 0; i < num_threads; i++) { threads[i].join(); }

  cout << "general_counter " << app.getCounter() << endl;
  cout << "atomic_counter " << app.getAtomicCounter() << endl;

}


void mutexCounter(ThreadApp& app, vector<thread>& threads, int& num_threads) {
  
  for(int i = 0; i < num_threads; i++) { threads.push_back(thread(&ThreadApp::workMutex, &app)); }

  for(int i = 0; i < num_threads; i++) { threads[i].join(); }

  cout << "counter with mutex " << app.getCounter() << endl;

}


void lockGuardCounter(ThreadApp& app, vector<thread>& threads, int& num_threads) {
  
  for(int i = 0; i < num_threads; i++) { threads.push_back(thread(&ThreadApp::workLockGuard, &app)); }

  for(int i = 0; i < num_threads; i++) { threads[i].join(); }

  cout << "counter with lock_guard " << app.getCounter() << endl;
}


int main(int argc, char *argv[] ) {

  auto print_usage = []() {
    cout << "Usage: ./shared_data <basic / atomic / mutex> <num_threads>" << endl;
    cout << "basic: Spawn threads and display message from them" << endl;
    cout << "atomic: Spawn threads and update shared normal_int and a shared atomic_int" << endl;
    cout << "mutex: Spawn threads and update shared int with mutex" << endl;
    cout << "lock_guard: Spawn threads and update shared int with lock_guard" << endl;
  };

  if(argc == 1) { print_usage(); return 1; }

  string mode = argv[1];
  int num_threads;

  ThreadApp app;
  app();

  if(!argv[2]) { num_threads = 2; }
  else { num_threads = stoi(argv[2]); }

  vector<thread> threads;

  if(mode == "basic") { basicMultithreading(app, threads, num_threads); }

  else if(mode == "atomic") { atomicCounter(app, threads, num_threads); }

  else if(mode == "mutex") { mutexCounter(app, threads, num_threads); }

  else if(mode == "lock_guard") { lockGuardCounter(app, threads, num_threads); }

  else { print_usage(); return 1; }

  return 0;
}
