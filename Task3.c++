#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

// Define the threshold for low stock alert
const int LOW_STOCK_THRESHOLD = 5;

// Product class
class Product {
    string id;
    string name;
    int price;
    int quantity;

public:
    Product() {}

    Product(string pid, string pname, int pprice, int pquantity)
        : id(pid), name(pname), price(pprice), quantity(pquantity) {}

    // Getter methods
    string getId() const { return id; }
    string getName() const { return name; }
    int getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Update quantity
    void updateQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    // Serialize product to a CSV line
    string toCSV() const {
        return id + ";" + name + ";" + to_string(price) + ";" + to_string(quantity) + "\n";
    }

    // Display product info
    void display() const {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Price: " << price
             << " | Quantity: " << quantity;
        if (quantity < LOW_STOCK_THRESHOLD) {
            cout << " [LOW STOCK!]";
        }
        cout << endl;
    }

    // Create product from CSV line
    static Product fromCSV(const string& line) {
        stringstream ss(line);
        string id, name, priceStr, quantityStr;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');
        return Product(id, name, stoi(priceStr), stoi(quantityStr));
    }
};

// Inventory class to manage products
class Inventory {
    vector<Product> products;

    // Load products from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Could not open file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                Product p = Product::fromCSV(line);
                products.push_back(p);
            }
        }

        file.close();
    }

    // Save all products to file
    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& p : products) {
            file << p.toCSV();
        }
        file.close();
    }

public:
    Inventory(const string& filename) {
        loadFromFile(filename);
    }

    ~Inventory() {
        saveToFile("product.csv");
    }

    // Add new product
    void addProduct() {
        string id, name;
        int price, quantity;
        cout << "Enter Product ID: ";
        cin >> id;

        // Check for duplicate
        for (const auto& p : products) {
            if (p.getId() == id) {
                cout << "Product with this ID already exists.\n";
                return;
            }
        }

        cout << "Enter Product Name: ";
        cin >> name;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> quantity;

        Product newProduct(id, name, price, quantity);
        products.push_back(newProduct);
        cout << "Product added successfully.\n";
    }

    // View all products
    void viewProducts() const {
        if (products.empty()) {
            cout << "No products available.\n";
            return;
        }

        cout << "\n--- Product List ---\n";
        for (const auto& p : products) {
            p.display();
        }
    }

    // Update stock quantity
    void updateStock() {
        string id;
        cout << "Enter Product ID to update: ";
        cin >> id;

        for (auto& p : products) {
            if (p.getId() == id) {
                int newQuantity;
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                p.updateQuantity(newQuantity);
                cout << "Stock updated.\n";
                return;
            }
        }

        cout << "Product not found.\n";
    }

    // Search product by ID
    void searchProduct() const {
        string id;
        cout << "Enter Product ID to search: ";
        cin >> id;

        for (const auto& p : products) {
            if (p.getId() == id) {
                cout << "Product found:\n";
                p.display();
                return;
            }
        }

        cout << "Product not found.\n";
    }

    // Show low-stock alert
    void showLowStock() const {
        cout << "\n--- Low Stock Products ---\n";
        bool found = false;
        for (const auto& p : products) {
            if (p.getQuantity() < LOW_STOCK_THRESHOLD) {
                p.display();
                found = true;
            }
        }

        if (!found) {
            cout << "All products have sufficient stock.\n";
        }
    }
};

// Main menu
int main() {
    Inventory inventory("product.csv");

    int choice;
    do {
        cout << "\n===== Inventory Menu =====\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Update Stock\n";
        cout << "4. Search Product\n";
        cout << "5. Show Low Stock Alerts\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: inventory.addProduct(); break;
            case 2: inventory.viewProducts(); break;
            case 3: inventory.updateStock(); break;
            case 4: inventory.searchProduct(); break;
            case 5: inventory.showLowStock(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}