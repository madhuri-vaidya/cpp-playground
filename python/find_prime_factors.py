# Function to get prime factors of a given number

import sys

def get_prime_factors(n):
    # Return a list of prime factors of the given number n
    
    # Check for number less than 2
    if n < 2: return "Prime numbers begin from 2 onwards.."

    prime_factors = []

    for factor in range(2, n // 2 + 1):

        # First check if 'factor' is a factor of n
        if not n % factor:
            is_prime = True

            # Check if 'factor' is prime by checking against existing prime numbers
            for prime in prime_factors:
                if not factor % prime: break

            else: prime_factors.append(factor)

    # Check if the number itself is prime
    for prime in prime_factors:
        if not n % prime: break
    else: prime_factors.append(n)
    
    return prime_factors


def get_prime_factorial_expansion(n):
    # Return the prime factorial expansion of the given number n
    
    # Check for number less than 2
    if n < 2: return "Prime numbers begin from 2 onwards.."

    prime_factorial_expansion = []
    num = n

    for factor in range(2, n // 2 + 1):
        while(not num % factor): 
            prime_factorial_expansion.append(factor)
            num = int(num / factor)

    # Check if n is prime
    for prime in prime_factorial_expansion:
        if not n % prime: break
    else: prime_factorial_expansion.append(n)

    return prime_factorial_expansion



if __name__ == "__main__":
    test_numbers = [777, 10000, 4173, 3598, 2900]

    # test_numbers = [int(sys.argv[1])]

    for num in test_numbers:
        # print(get_prime_factors(num))
        print(get_prime_factorial_expansion(num))