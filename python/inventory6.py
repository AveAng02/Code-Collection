import sqlite3
from PIL import Image
from PyQt5 import QtCore, QtGui, QtWidgets

# Connect to the SQLite database
conn = sqlite3.connect('inventory.db')
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

class InventoryManagement(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Inventory Management System')
        self.setMinimumSize(400, 300)
        self.setup_ui()

    def setup_ui(self):
        self.layout = QtWidgets.QVBoxLayout(self)

        self.add_product_btn = QtWidgets.QPushButton('Add Product')
        self.update_quantity_btn = QtWidgets.QPushButton('Update Quantity')
        self.view_products_btn = QtWidgets.QPushButton('View All Products')
        self.search_product_btn = QtWidgets.QPushButton('Search Product by Name')
        self.display_image_btn = QtWidgets.QPushButton('Display Product Image')
        self.create_shopping_list_btn = QtWidgets.QPushButton('Create Shopping List')
        self.generate_bill_btn = QtWidgets.QPushButton('Generate Total Bill')
        self.exit_btn = QtWidgets.QPushButton('Exit')

        self.layout.addWidget(self.add_product_btn)
        self.layout.addWidget(self.update_quantity_btn)
        self.layout.addWidget(self.view_products_btn)
        self.layout.addWidget(self.search_product_btn)
        self.layout.addWidget(self.display_image_btn)
        self.layout.addWidget(self.create_shopping_list_btn)
        self.layout.addWidget(self.generate_bill_btn)
        self.layout.addWidget(self.exit_btn)

        self.add_product_btn.clicked.connect(self.add_product)
        self.update_quantity_btn.clicked.connect(self.update_quantity)
        self.view_products_btn.clicked.connect(self.view_all_products)
        self.search_product_btn.clicked.connect(self.search_product_by_name)
        self.display_image_btn.clicked.connect(self.display_product_image)
        self.create_shopping_list_btn.clicked.connect(self.create_shopping_list)
        self.generate_bill_btn.clicked.connect(self.generate_bill)
        self.exit_btn.clicked.connect(QtCore.QCoreApplication.instance().quit)

    def add_product(self):
        dialog = AddProductDialog()
        if dialog.exec_() == QtWidgets.QDialog.Accepted:
            name = dialog.name_input.text()
            description = dialog.description_input.text()
            price = float(dialog.price_input.text())
            quantity = int(dialog.quantity_input.text())
            supplier = dialog.supplier_input.text()
            category = dialog.category_input.text()
            image_path = dialog.image_path_input.text()
            add_product(name, description, price, quantity, supplier, category, image_path)

    def update_quantity(self):
        dialog = UpdateQuantityDialog()
        if dialog.exec_() == QtWidgets.QDialog.Accepted:
            product_id = int(dialog.product_id_input.text())
            new_quantity = int(dialog.new_quantity_input.text())
            update_quantity(product_id, new_quantity)

    def view_all_products(self):
        products = get_all_products()
        for product in products:
            print(product)

    def search_product_by_name(self):
        dialog = SearchProductDialog()
        if dialog.exec_() == QtWidgets.QDialog.Accepted:
            search_name = dialog.search_name_input.text()
            products = search_product_by_name(search_name)
            for product in products:
                print(product)

    def display_product_image(self):
        dialog = DisplayImageDialog()
        if dialog.exec_() == QtWidgets.QDialog.Accepted:
            product_id = int(dialog.product_id_input.text())
            display_product_image(product_id)

    def create_shopping_list(self):
        dialog = CreateShoppingListDialog()
        if dialog.exec_() == QtWidgets.QDialog.Accepted:
            shopping_list = dialog.get_shopping_list()
            print("Shopping List:")
            for item in shopping_list:
                product_id, quantity = item
                print(f"Product ID: {product_id}, Quantity: {quantity}")

    def generate_bill(self):
        dialog = CreateShoppingListDialog()
        if dialog.exec_() == QtWidgets.QDialog.Accepted:
            shopping_list = dialog.get_shopping_list()
            total_bill = generate_bill(shopping_list)
            print("Total Bill:", total_bill)

class AddProductDialog(QtWidgets.QDialog):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Add Product')
        self.layout = QtWidgets.QFormLayout(self)
        self.name_input = QtWidgets.QLineEdit()
        self.description_input = QtWidgets.QLineEdit()
        self.price_input = QtWidgets.QLineEdit()
        self.quantity_input = QtWidgets.QLineEdit()
        self.supplier_input = QtWidgets.QLineEdit()
        self.category_input = QtWidgets.QLineEdit()
        self.image_path_input = QtWidgets.QLineEdit()
        self.image_path_btn = QtWidgets.QPushButton('Browse')

        self.layout.addRow('Name:', self.name_input)
        self.layout.addRow('Description:', self.description_input)
        self.layout.addRow('Price:', self.price_input)
        self.layout.addRow('Quantity:', self.quantity_input)
        self.layout.addRow('Supplier:', self.supplier_input)
        self.layout.addRow('Category:', self.category_input)
        self.layout.addRow('Image Path:', self.image_path_input)
        self.layout.addRow('', self.image_path_btn)

        self.image_path_btn.clicked.connect(self.browse_image_path)

        self.button_box = QtWidgets.QDialogButtonBox(self)
        self.button_box.addButton(QtWidgets.QDialogButtonBox.Ok)
        self.button_box.addButton(QtWidgets.QDialogButtonBox.Cancel)
        self.layout.addWidget(self.button_box)

        self.button_box.accepted.connect(self.accept)
        self.button_box.rejected.connect(self.reject)

    def browse_image_path(self):
        file_dialog = QtWidgets.QFileDialog()
        file_path, _ = file_dialog.getOpenFileName(self, 'Select Image')
        if file_path:
            self.image_path_input.setText(file_path)

class UpdateQuantityDialog(QtWidgets.QDialog):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Update Quantity')
        self.layout = QtWidgets.QFormLayout(self)
        self.product_id_input = QtWidgets.QLineEdit()
        self.new_quantity_input = QtWidgets.QLineEdit()

        self.layout.addRow('Product ID:', self.product_id_input)
        self.layout.addRow('New Quantity:', self.new_quantity_input)

        self.button_box = QtWidgets.QDialogButtonBox(self)
        self.button_box.addButton(QtWidgets.QDialogButtonBox.Ok)
        self.button_box.addButton(QtWidgets.QDialogButtonBox.Cancel)
        self.layout.addWidget(self.button_box)

        self.button_box.accepted.connect(self.accept)
        self.button_box.rejected.connect(self.reject)

class SearchProductDialog(QtWidgets.QDialog):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Search Product')
        self.layout = QtWidgets.QFormLayout(self)
        self.search_name_input = QtWidgets.QLineEdit()

        self.layout.addRow('Product Name:', self.search_name_input)

        self.button_box = QtWidgets.QDialogButtonBox(self)
        self.button_box.addButton(QtWidgets.QDialogButtonBox.Ok)
        self.button_box.addButton(QtWidgets.QDialogButtonBox.Cancel)
        self.layout.addWidget(self.button_box)

        self.button_box.accepted.connect(self.accept)
        self.button_box.rejected.connect(self.reject)

class DisplayImageDialog(QtWidgets.QDialog):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Display Product Image')
        self.layout = QtWidgets.QFormLayout(self)
        self.product_id_input = QtWidgets.QLineEdit()

        self.layout.addRow('Product ID:', self.product_id_input)

        self.button_box = QtWidgets.QDialogButtonBox(self)
        self.button_box.addButton(QtWidgets.QDialogButtonBox.Ok)
        self.button_box.addButton(QtWidgets.QDialogButtonBox.Cancel)
        self.layout.addWidget(self.button_box)

        self.button_box.accepted.connect(self.accept)
        self.button_box.rejected.connect(self.reject)

class CreateShoppingListDialog(QtWidgets.QDialog):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Create Shopping List')
        self.layout = QtWidgets.QVBoxLayout(self)
        self.shopping_list = QtWidgets.QTableWidget()
        self.shopping_list.setColumnCount(2)
        self.shopping_list.setHorizontalHeaderLabels(['Product ID', 'Quantity'])
        self.add_product_btn = QtWidgets.QPushButton('Add Product')
        self.clear_btn = QtWidgets.QPushButton('Clear List')
        self.button_box = QtWidgets.QDialogButtonBox(QtWidgets.QDialogButtonBox.Ok | QtWidgets.QDialogButtonBox.Cancel)

        self.layout.addWidget(self.shopping_list)
        self.layout.addWidget(self.add_product_btn)
        self.layout.addWidget(self.clear_btn)
        self.layout.addWidget(self.button_box)

        self.add_product_btn.clicked.connect(self.add_product_to_list)
        self.clear_btn.clicked.connect(self.clear_list)
        self.button_box.accepted.connect(self.accept)
        self.button_box.rejected.connect(self.reject)

    def add_product_to_list(self):
        product_id, ok = QtWidgets.QInputDialog.getInt(self, 'Add Product', 'Product ID:')
        if ok:
            quantity, ok = QtWidgets.QInputDialog.getInt(self, 'Add Product', 'Quantity:')
            if ok:
                row_count = self.shopping_list.rowCount()
                self.shopping_list.setRowCount(row_count + 1)
                self.shopping_list.setItem(row_count, 0, QtWidgets.QTableWidgetItem(str(product_id)))
                self.shopping_list.setItem(row_count, 1, QtWidgets.QTableWidgetItem(str(quantity)))

    def clear_list(self):
        self.shopping_list.clearContents()
        self.shopping_list.setRowCount(0)

    def get_shopping_list(self):
        shopping_list = []
        for row in range(self.shopping_list.rowCount()):
            product_id = int(self.shopping_list.item(row, 0).text())
            quantity = int(self.shopping_list.item(row, 1).text())
            shopping_list.append((product_id, quantity))
        return shopping_list

if __name__ == '__main__':
    app = QtWidgets.QApplication([])
    inventory_management = InventoryManagement()
    inventory_management.show()
    app.exec_()
