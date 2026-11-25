# Screenshots Directory

This directory should contain the following screenshots for the GitHub repository:

## Required Screenshots

1. **food_menu.png** - Screenshot of Option 1 (Display Food Menu)
   - Show the formatted table with all 12 food items
   - Columns: ID, Food Item, Price, Quantity

2. **billing_output.png** - Screenshot of Option 4 (Generate Bill)
   - Show a complete bill receipt with multiple items
   - Include: Item names, quantities, unit prices, subtotals, grand total
   - Show "Order Confirmed!" message
   - Show updated stock after confirmation

3. **inventory_update.png** - Screenshot of Option 5 (View Available Stock)
   - Show inventory before and after an order
   - Highlight the stock reduction (e.g., Burger: 20 → 18)

## How to Take Screenshots

### Windows:
1. Run the program: `compile_and_run.bat` or `canteen_billing.exe`
2. Navigate to each menu option
3. Press `Win + Shift + S` to capture the terminal window
4. Save as PNG in this folder

### Linux/Mac:
1. Run the program: `./compile_and_run.sh` or `./canteen_billing`
2. Navigate to each menu option
3. Use your OS screenshot tool (e.g., `gnome-screenshot`, `Shift+Cmd+4` on Mac)
4. Save as PNG in this folder

## Example Test Sequence for Screenshots

```
# For food_menu.png:
1. Run program
2. Enter: 1 (Display Food Menu)
3. Take screenshot
4. Enter: 6 (Exit)

# For billing_output.png:
1. Run program
2. Enter: 3 (Place Order)
3. Enter Food ID: 101
4. Enter Quantity: 2
5. Enter Food ID: 104
6. Enter Quantity: 3
7. Enter Food ID: 0 (finish)
8. Enter: 4 (Generate Bill)
9. Enter: y (Confirm)
10. Take screenshot of bill and updated stock
11. Enter: 6 (Exit)

# For inventory_update.png:
1. Run program
2. Enter: 5 (View Available Stock) - BEFORE order
3. Take screenshot
4. Place order (as above)
5. Enter: 5 (View Available Stock) - AFTER order
6. Take screenshot showing reduced quantities
```

## Naming Convention
- Use exactly: `food_menu.png`, `billing_output.png`, `inventory_update.png`
- Format: PNG
- Resolution: Clear enough to read text (at least 800x600)