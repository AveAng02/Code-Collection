import sqlite3
from PIL import Image

# Connect to the SQLite database
conn = sqlite3.connect('inventory5.db')
cursor = conn.cursor()

# Create the Products table
cursor.execute('''CREATE TABLE IF NOT EXISTS Products (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL,
                    description TEXT NOT NULL,
                    price REAL NOT NULL,
                    quantity INTEGER NOT NULL,
                    supplier TEXT,
                    category TEXT,
                    image_path TEXT
                )''')

# Function to add a new product to the inventory
def add_product(name, description, price, quantity, supplier=None, category=None, image_path=None):
    cursor.execute('''INSERT INTO Products (name, description, price, quantity, supplier, category, image_path)
                    VALUES (?, ?, ?, ?, ?, ?, ?)''', (name, description, price, quantity, supplier, category, image_path))
    conn.commit()
    print("Product added successfully!")

# Function to update the quantity of a product
def update_quantity(product_id, new_quantity):
    cursor.execute('''UPDATE Products SET quantity = ?
                    WHERE id = ?''', (new_quantity, product_id))
    conn.commit()
    print("Quantity updated successfully!")

# Function to get the list of all products
def get_all_products():
    cursor.execute("SELECT * FROM Products")
    products = cursor.fetchall()
    return products

# Function to search for a product by name
def search_product_by_name(name):
    cursor.execute("SELECT * FROM Products WHERE name LIKE ?", ('%' + name + '%',))
    products = cursor.fetchall()
    return products

# Function to display the image of a product
def display_product_image(product_id):
    cursor.execute("SELECT image_path FROM Products WHERE id = ?", (product_id,))
    result = cursor.fetchone()
    if result:
        image_path = result[0]
        try:
            print(image_path)
            image = Image.open(image_path)
            image.show()
        except FileNotFoundError:
            print("Image not found!")
    else:
        print("Product not found!")

# Function to create a shopping list for customers
def create_shopping_list():
    shopping_list = []
    while True:
        product_id = int(input("Enter product ID (0 to finish shopping): "))
        if product_id == 0:
            break
        quantity = int(input("Enter quantity: "))
        shopping_list.append((product_id, quantity))
    return shopping_list

# Function to generate the total bill for the shopping list
def generate_bill(shopping_list):
    total = 0
    for item in shopping_list:
        product_id, quantity = item
        cursor.execute("SELECT price FROM Products WHERE id = ?", (product_id,))
        result = cursor.fetchone()
        if result:
            price = result[0]
            total += price * quantity
    return total

# Main menu function
def main_menu():
    while True:
        print("\n---- Inventory Management System ----")
        print("1. Add Product")
        print("2. Update Quantity")
        print("3. View All Products")
        print("4. Search Product by Name")
        print("5. Display Product Image")
        print("6. Create Shopping List")
        print("7. Generate Total Bill")
        print("8. Exit")
        choice = input("Enter your choice (1-8): ")

        if choice == '1':
            name = input("Enter product name: ")
            description = input("Enter product description: ")
            price = float(input("Enter product price: "))
            quantity = int(input("Enter product quantity: "))
            supplier = input("Enter supplier information (optional): ")
            category = input("Enter product category (optional): ")
            image_path = input("Enter path to product image (optional): ")
            add_product(name, description, price, quantity, supplier, category, image_path)

        elif choice == '2':
            product_id = int(input("Enter product ID: "))
            new_quantity = int(input("Enter new quantity: "))
            update_quantity(product_id, new_quantity)

        elif choice == '3':
            products = get_all_products()
            for product in products:
                print(product)

        elif choice == '4':
            search_name = input("Enter product name to search: ")
            products = search_product_by_name(search_name)
            for product in products:
                print(product)

        elif choice == '5':
            product_id = int(input("Enter product ID: "))
            display_product_image(product_id)

        elif choice == '6':
            shopping_list = create_shopping_list()
            print("Shopping List:")
            for item in shopping_list:
                product_id, quantity = item
                print(f"Product ID: {product_id}, Quantity: {quantity}")

        elif choice == '7':
            shopping_list = create_shopping_list()
            total_bill = generate_bill(shopping_list)
            print("Total Bill:", total_bill)

        elif choice == '8':
            break

        else:
            print("Invalid choice. Please try again.")

    # Close the database connection
    conn.close()

# Run the main menu
main_menu()