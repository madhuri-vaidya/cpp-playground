# inventwithpython.com

import sys
import random

def fizzBuzz(command_line_args):
    num = int(input("Enter an integer: "))

    if num % 15 == 0: 
        print("FizzBuzz")
        return
    
    if num % 3 == 0:
        print("Fizz")
        return
    
    if num % 5 == 0:
        print("Buzz")
        return

    print(num)


def treePrinter(command_line_args):
    tree_size = int(input("Enter Tree Size: "))

    for i in range(tree_size):
        print(" " * (tree_size - i - 1) + "^" * (2 * i + 1))

    print(" " * (tree_size - 1) + "#")
    print(" " * (tree_size - 1) + "#")


def xmasTreePrinter(command_line_args): 
    tree_size = int(input("Enter Tree Size: "))
    
    for i in range(tree_size):
        print_line = " " * (tree_size - i - 1)
        
        for j in range(2 * i + 1):
            if random.randint(1, 4) == 1: print_line += "o"
            else: print_line += "^"

        print(print_line)

    print(" " * (tree_size - 1) + "#")
    print(" " * (tree_size - 1) + "#")


def collatz(command_line_args):
    try:
        num = int(command_line_args)

    except ValueError:
        print(command_line_args + " is not an integer. Please enter an integer.")
        sys.exit()

    print(str(num) + " ", end = '')

    if(num == 1) : return

    if num % 2 == 0: num = num // 2

    else: num = (3 * num) + 1

    collatz(num)


def raisingExceptions(command_line_args):
    name = input('Enter your name: ')

    if name == '': raise Exception('You did not enter a name')
    
    else: print('Hello ' + name)


def gradeAverageCalculator(command_line_args):
    calculate_grade_average = lambda grade_sum, number_of_grades: int(grade_sum / number_of_grades)

    counter = 0
    total = 0

    while True:
        grade = input('Enter a grade, or "done" if done entering grades: ')

        if grade == 'done':
            break

        counter += 1
        total += int(grade)
    
    print('total is ', total)
    print('counter is ', counter)

    print('The grade average is: ', calculate_grade_average(total, counter))


if __name__ == "__main__":
    command_line_args = sys.argv[:]

    print(command_line_args)

    gradeAverageCalculator(command_line_args)