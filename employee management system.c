
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Employee structure
struct Employee {
    int id;
    char name[50];
    char department[50];
    double salary;
    char joiningDate[20];
};

struct Employee emp[MAX];
int count = 0;

// Function to read a string
void readString(char str[], int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}

// Function to read an integer safely
int readInt() {
    char line[100];
    char *end;
    long value;

    while (1) {
        if (!fgets(line, sizeof(line), stdin))
            exit(0);

        value = strtol(line, &end, 10);

        while (isspace((unsigned char)*end))
            end++;

        if (end != line && *end == '\0' &&
            value >= -2147483647L - 1 &&
            value <= 2147483647L)
            return (int)value;

        printf("Invalid input! Enter an integer: ");
    }
}

// Function to read salary
double readSalary() {
    char line[100];
    char *end;
    double value;

    while (1) {
        if (!fgets(line, sizeof(line), stdin))
            exit(0);

        value = strtod(line, &end);

        while (isspace((unsigned char)*end))
            end++;

        if (end != line && *end == '\0' &&
            value >= 0 && value < 1e12)
            return value;

        printf("Invalid salary! Enter again: ");
    }
}

// Display employee details
void displayEmployee(struct Employee e) {
    printf("\nID: %d", e.id);
    printf("\nName: %s", e.name);
    printf("\nDepartment: %s", e.department);
    printf("\nSalary: %.2lf", e.salary);
    printf("\nJoining Date: %s\n", e.joiningDate);
}

// Check whether ID already exists
int findEmployeeID(int id) {
    for (int i = 0; i < count; i++) {
        if (emp[i].id == id)
            return i;
    }
    return -1;
}

// Module 1: Add Employee
void addEmployee() {
    if (count >= MAX) {
        printf("\nEmployee limit reached!\n");
        return;
    }

    int id;

    printf("\nEnter Employee ID: ");
    id = readInt();

    if (id <= 0 || findEmployeeID(id) != -1) {
        printf("Invalid or duplicate Employee ID!\n");
        return;
    }

    emp[count].id = id;

    printf("Enter Employee Name: ");
    readString(emp[count].name, 50);

    printf("Enter Department: ");
    readString(emp[count].department, 50);

    printf("Enter Salary: ");
    emp[count].salary = readSalary();

    printf("Enter Joining Date (DD-MM-YYYY): ");
    readString(emp[count].joiningDate, 20);

    count++;

    printf("\nEmployee added successfully!\n");
}

// Module 1: Modify Employee
void modifyEmployee() {
    int id;

    printf("\nEnter Employee ID to modify: ");
    id = readInt();

    int index = findEmployeeID(id);

    if (index == -1) {
        printf("\nEmployee not found!\n");
        return;
    }

    printf("\nEnter New Name: ");
    readString(emp[index].name, 50);

    printf("Enter New Department: ");
    readString(emp[index].department, 50);

    printf("Enter New Salary: ");
    emp[index].salary = readSalary();

    printf("Enter New Joining Date: ");
    readString(emp[index].joiningDate, 20);

    printf("\nEmployee updated successfully!\n");
}

// Module 1: Delete Employee
void deleteEmployee() {
    int id;

    printf("\nEnter Employee ID to delete: ");
    id = readInt();

    int index = findEmployeeID(id);

    if (index == -1) {
        printf("\nEmployee not found!\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        emp[i] = emp[i + 1];
    }

    count--;

    printf("\nEmployee deleted successfully!\n");
}

// Module 2: Display All Employees
void displayAllEmployees() {
    if (count == 0) {
        printf("\nNo employee records found!\n");
        return;
    }

    printf("\n========== EMPLOYEE LIST ==========\n");

    for (int i = 0; i < count; i++) {
        printf("\nEmployee %d", i + 1);
        printf("\n----------------------");
        displayEmployee(emp[i]);
    }
}

// Module 2: Department-wise Listing
void departmentReport() {
    char dept[50];
    int found = 0;

    printf("\nEnter Department Name: ");
    readString(dept, 50);

    printf("\nEmployees in %s Department:\n", dept);

    for (int i = 0; i < count; i++) {
        if (strcasecmp(emp[i].department, dept) == 0) {
            displayEmployee(emp[i]);
            found++;
        }
    }

    if (!found)
        printf("\nNo employees found in this department!\n");
}

// Module 2: Salary Report
void salaryReport() {
    if (count == 0) {
        printf("\nNo employee records available!\n");
        return;
    }

    double total = 0;

    for (int i = 0; i < count; i++) {
        total += emp[i].salary;
    }

    printf("\n========== SALARY REPORT ==========\n");
    printf("Total Employees: %d\n", count);
    printf("Total Salary: %.2lf\n", total);
    printf("Average Salary: %.2lf\n", total / count);
}

// Case-insensitive substring search
int containsIgnoreCase(const char *str, const char *key) {
    int n = strlen(str);
    int m = strlen(key);

    if (m == 0)
        return 1;

    for (int i = 0; i <= n - m; i++) {
        int j;

        for (j = 0; j < m; j++) {
            if (tolower((unsigned char)str[i + j]) !=
                tolower((unsigned char)key[j]))
                break;
        }

        if (j == m)
            return 1;
    }

    return 0;
}

// Module 3: Linear Search by Name
void linearSearchName() {
    char name[50];
    int found = 0;

    printf("\nEnter Employee Name to search: ");
    readString(name, 50);

    printf("\nSearch Results:\n");

    for (int i = 0; i < count; i++) {
        if (containsIgnoreCase(emp[i].name, name)) {
            displayEmployee(emp[i]);
            found++;
        }
    }

    if (!found)
        printf("\nEmployee not found!\n");
}

// Module 3: Linear Search by Department
void linearSearchDepartment() {
    char dept[50];
    int found = 0;

    printf("\nEnter Department to search: ");
    readString(dept, 50);

    for (int i = 0; i < count; i++) {
        if (containsIgnoreCase(emp[i].department, dept)) {
            displayEmployee(emp[i]);
            found++;
        }
    }

    if (!found)
        printf("\nNo employee found!\n");
}

// Compare employees by ID for qsort
int compareID(const void *a, const void *b) {
    const struct Employee *e1 = a;
    const struct Employee *e2 = b;

    if (e1->id < e2->id) return -1;
    if (e1->id > e2->id) return 1;
    return 0;
}

// Linear search by ID with comparison count
int linearSearchID(int id, int *comparisons) {
    *comparisons = 0;

    for (int i = 0; i < count; i++) {
        (*comparisons)++;

        if (emp[i].id == id)
            return i;
    }

    return -1;
}

// Binary Search by ID
int binarySearchID(struct Employee sorted[], int n,
                   int id, int *comparisons) {
    int low = 0;
    int high = n - 1;

    *comparisons = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        (*comparisons)++;

        if (sorted[mid].id == id)
            return mid;

        if (id < sorted[mid].id)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}

// Module 4: Binary Search and Comparison
void binarySearchModule() {
    if (count == 0) {
        printf("\nNo employee records available!\n");
        return;
    }

    struct Employee sorted[MAX];

    // Copy original records
    for (int i = 0; i < count; i++) {
        sorted[i] = emp[i];
    }

    // Sort employees by ID
    qsort(sorted, count, sizeof(struct Employee), compareID);

    printf("\nEmployees Sorted by ID:\n");

    for (int i = 0; i < count; i++) {
        printf("%d - %s\n", sorted[i].id, sorted[i].name);
    }

    int id;

    printf("\nEnter Employee ID to search: ");
    id = readInt();

    int linearComparisons, binaryComparisons;

    int linearResult = linearSearchID(id, &linearComparisons);

    int binaryResult = binarySearchID(
        sorted, count, id, &binaryComparisons
    );

    printf("\n========== SEARCH RESULT ==========\n");

    if (binaryResult != -1) {
        printf("\nEmployee Found:\n");
        displayEmployee(sorted[binaryResult]);
    } else {
        printf("\nEmployee not found!\n");
    }

    printf("\n========== COMPARISON ==========\n");

    printf("Linear Search Comparisons: %d\n",
           linearComparisons);

    printf("Binary Search Comparisons: %d\n",
           binaryComparisons);

    if (linearComparisons > binaryComparisons) {
        printf("\nBinary Search used fewer comparisons.\n");
    } else if (linearComparisons < binaryComparisons) {
        printf("\nLinear Search used fewer comparisons.\n");
    } else {
        printf("\nBoth used equal comparisons.\n");
    }

    // Verify that both searches give the same result
    if ((linearResult == -1) == (binaryResult == -1))
        printf("Search results verified successfully.\n");
}

// Main Menu
int main() {
    int choice;

    do {
        printf("\n\n");
        printf("====================================\n");
        printf("     EMPLOYEE MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Add Employee\n");
        printf("2. Modify Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display All Employees\n");
        printf("5. Department-wise Employee Report\n");
        printf("6. Total and Average Salary Report\n");
        printf("7. Linear Search by Name\n");
        printf("8. Linear Search by Department\n");
        printf("9. Binary Search by Employee ID\n");
        printf("0. Exit\n");

        printf("------------------------------------\n");
        printf("Enter Your Choice: ");

        choice = readInt();

        switch (choice) {
            case 1:
                addEmployee();
                break;

            case 2:
                modifyEmployee();
                break;

            case 3:
                deleteEmployee();
                break;

            case 4:
                displayAllEmployees();
                break;

            case 5:
                departmentReport();
                break;

            case 6:
                salaryReport();
                break;

            case 7:
                linearSearchName();
                break;

            case 8:
                linearSearchDepartment();
                break;

            case 9:
                binarySearchModule();
                break;

            case 0:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 0);

    return 0;
}
