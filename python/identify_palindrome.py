'''
Function to identify whether a given string is a palindrome or not.

* Input: String to evaluate
* Output: Boolean value
* Only consider letters (A - Z)
* Ignore case ('A' == 'a')
'''

import re

def isPalindromeTwoPointer(sentence):

    left, right = 0, len(sentence) - 1

    while(left < right):
        while(not sentence[left].isalpha()): left += 1

        while(not sentence[right].isalpha()): right -= 1

        if(sentence[left].lower() != sentence[right].lower()) : return False

        left += 1
        right -= 1

    return True


def isPalindromeRegex(sentence):
    
    forwards = ''.join(re.findall(r'[a-z]+', sentence.lower()))
    backwards = forwards[::-1]

    return forwards == backwards


if __name__ == "__main__":
    inputs = ["hello world.",
              "Go hang a salami - I'm a lasagna hog!",
              "rac21e car32"]
    
    for sentence in inputs:
        print(isPalindromeTwoPointer(sentence))
        print(isPalindromeRegex(sentence))
        print("\n")