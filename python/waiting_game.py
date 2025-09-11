'''
Create a waiting game

Assign a random number of seconds to the user and user has to press enter after precisely those many seconds
'''

import time
import random

def waiting_game():

    waiting_time = random.randint(1, 10)

    input(f"Your target time is {waiting_time} seconds. Press Enter to begin\n")
    start_time = time.time()
    
    input(f"Press Enter again after {waiting_time} seconds...\n")
    end_time = time.time()

    if end_time - start_time == waiting_time: print("Congratulations! You were spot on!")
    elif end_time - start_time < waiting_time: print(f"Oops, you were {waiting_time - end_time + start_time : .2f} seconds early..")
    elif end_time - start_time > waiting_time: print(f"Oops, you were {end_time - start_time - waiting_time : .2f} seconds late..")

if __name__ == "__main__":
    waiting_game()