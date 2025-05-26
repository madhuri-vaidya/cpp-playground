/* 
 * Function to calculate PI using the Leibniz formula
 * 1 - 1/3 + 15 - 1/7 + 1/9 - .... = pi/4
 * 
 * Experimenting with promises and futures, and packaged_tasks
 *
 * usage: ./calculate_pi <number_of_terms> <default / promise / packaged_task>
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <future>
#include <thread>
#include <exception>
#include <string>

using namespace std;


double calculatePi(int terms) {

  double pi_approximation = 0.0;

  if(terms < 1) { throw runtime_error("Terms cannot be less than 1"); }
  
  for(int i = 0; i < terms; i++) {
    int sign = pow(-1, i);
    double term = 1.0 / ((i * 2) + 1);
    pi_approximation += sign  * term;
  }

  return pi_approximation * 4;
}


void promiseAndFuture(int terms) {
  
  promise<double> promise;
  future<double> future = promise.get_future();

  auto do_calculation = [&] (int terms) {
    
    try { promise.set_value(calculatePi(terms)); }

    catch (...) { promise.set_exception(current_exception()); }
  };

  thread t1(do_calculation, terms);
  t1.join();

  try { cout << setprecision(15) << future.get() << endl; }
  catch(exception &e) { cout << e.what() << endl; }

  return;
}


void packagedTask(int terms) {
  
  packaged_task<double(int)> task(calculatePi);
  future<double> future = task.get_future();

  thread t1(move(task), terms);

  try { cout << setprecision(15) << future.get() << endl; }

  catch(exception &e) { cout << e.what() << endl; }

  t1.join();

  return;
}


int main(int argc, char *argv[]) {

  int terms = 5;
  string method = "default";

  auto usage = []() { cout << "Usage: ./calculate_pi <number_of_terms> <default / promise / packaged_task>" << endl; };
  
  if(argc == 3) {
    try {
      terms = stoi(argv[1]);
      method = argv[2];
    }

    catch(...) {
      usage();
      exit(1);
    }
  }

  else {
    usage();
    cout << "Calculating with 5 terms using default method.." << endl;
  }

  if(method == "default") { 
    try { cout << setprecision(15) << calculatePi(terms) << endl; }
    
    catch(exception &e) { cout << e.what() << endl; }
  }

  else if(method == "promise") { promiseAndFuture(terms); }

  else if(method == "packaged_task") { packagedTask(terms); }

  else { usage(); }
  
  return 0;
}
