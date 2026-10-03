## 1. Introduction
The Municipal Financial Management System (MFMS) is a foundation C application developed for PAP521S – Programming in Practice. The system provides a simple menu-driven interface for managing municipal employees, budgets, suppliers and assets, and for producing basic reports.

The project demonstrates the programming concepts covered during the first part of the course, including variables, data types, input/output, operators, conditions, loops, arrays, strings and functions.

## 2. Problem Description
A municipality needs to maintain basic financial and administrative information. If employee, budget, supplier and asset information is handled manually, searching, calculating and reporting can become time-consuming.

The MFMS provides a single program where the user can enter records, search for information, perform calculations and display reports.

## 3. System Objectives
The objectives are to:
- Develop a menu-driven C application.
- Accept and validate user input.
- Store information using arrays and structures.
- Use conditions and loops for program control.
- Use string functions for searching and storing text.
- Use functions to divide the program into logical modules.
- Calculate employee salary and budget information.
- Generate basic reports.
- Demonstrate collaborative GitHub development.

## 4. System Features

### Employee Management
The employee module stores employee ID, name, department, basic salary and allowances. It supports adding, displaying, searching and calculating gross salary.

### Budget Management
The budget module stores department, allocated budget and expenditure. It calculates the remaining budget and identifies whether a department is within or over its budget.

### Supplier Management
The supplier module stores supplier ID, name, email, telephone number and town/location. Users can add, display and search suppliers.

### Asset Management
The asset module stores asset ID, name, type, purchase value, department and condition. Users can add, display and search assets.

### Reports
The reports module produces employee, budget, supplier and asset reports. Employee reports calculate average, highest and lowest gross salary. Budget reports calculate total allocation, expenditure, remaining budget and departments over budget.

## 5. Program Design
The application uses a main menu and separate submenus. Each major module is separated into `.c` and `.h` files.

The main program calls module functions instead of placing all code in `main()`.

Arrays store multiple records, structures group related information, loops process records, conditions validate and make decisions, and functions separate program responsibilities.

## 6. Challenges Encountered
Possible challenges during development include:
- Handling invalid numerical input.
- Mixing `scanf()` and `fgets()` input.
- Dividing the program into multiple files.
- Sharing data between modules.
- Avoiding duplicate IDs.
- Testing all menu paths.
- Coordinating GitHub contributions between group members.

## 7. Solutions Implemented
Input validation loops were used for non-negative financial values and required strings. Header files were used to declare structures, arrays and functions. Separate source files were used for the major modules. Search functions use string comparison and ID comparison. Reports use loops and calculations over stored records.

GitHub commits should be made throughout development so each member has identifiable work.

## 8. Conclusion
The MFMS provides a functional foundation for municipal financial management. It demonstrates the core C programming concepts required for Project A and provides a base that can be extended in Project B.
