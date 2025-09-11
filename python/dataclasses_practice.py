from dataclasses import dataclass

@dataclass
class Book:
    title: str
    author: str
    pages: int
    price: float

# create some instances
b1 = Book("1984", "George Orwell", 328, 10.99)
b2 = Book("To Kill a Mockingbird", "Harper Lee", 281, 8.99)

# access fields
print(b1.title)  # Output: 1984
print(b2.author) # Output: Harper Lee

print(b1)  # Output: Book(title='1984', author='George Orwell', pages=328, price=9.99)
print(b1 == b2)