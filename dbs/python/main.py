import sqlite3
from sqlite3 import Error

def get_all_orders(conn):
    cursor = conn.cursor()
    cursor.execute("SELECT OrderId, CustomerId, OrderDate FROM Orders LIMIT 10")

    rows = cursor.fetchall()
    for row in rows:
        for columnName in row.keys():
            print(f"{row['CustomerID']}")
        print()

def count_orders_from_a_customer(conn, customerId):
    customer_sql = """
        SELECT COUNT(*) AS numOrders
        FROM Orders
        WHERE CustomerId = ?
    """
    cursor = conn.cursor()
    cursor.execute(customer_sql, (customerId, ))

    row = cursor.fetchone()
    print(f"The customer {customerId} has {row['numOrders']} orders in the database")

def main():
    conn = None
    try:
        conn = sqlite3.connect("/home/ryan/northwind/NorthwindLimited.sqlite")
        conn.text_factory = lambda b: b.decode(errors = 'ignore')
        conn.row_factory = sqlite3.Row

        get_all_orders(conn)

        print("Enter in a customer name: ")
        customerName = input()
        count_orders_from_a_customer(conn, customerName)
        
    except Error as e:
        print(f"Error opening the database {e}")

    finally:
        if conn:
            conn.close()
main()