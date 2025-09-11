'''
Function to sort the words in a string

Input: String of words separated by spaces
Output: String of words sorted alphabetically

Constraints:
Ignore case while sorting, i.e. 'The' is same as 'the'
Words in output string should have same case as input
'''


def sort_string(string):
    
    words = string.split(' ')
    
    words = [word.lower() for word in words]
    
    words.sort()

    for word in string.split(' '):
        index = words.index(word.lower())
        words[index] = word        

    return words



if __name__ == "__main__":

    list_of_strings = ['string of words',
                       'The castle is mine',
                       'banana ORANGE Apple']

    for string in list_of_strings:
        print(sort_string(string))