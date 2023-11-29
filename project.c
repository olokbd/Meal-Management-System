#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int id;
    int balance;
    char name[30];
    char username[20];
    char password[20];
    char phone[11];
    struct Node *next;
} node;
node *head = NULL;

typedef struct Node2
{
    int id;
    char item[20];
    int price;
    struct Node2 *next;
} node2;
node2 *head2 = NULL;

int isManagerLogged = 0, isCustomerLogged = 0;
char loggedCustomerUsername[20] = "";

void manager_login();
void about_us();
void manager_menu();
void add_customer();
void delete_customer();
void view_all_customer();
void search_customer_by_id();
void search_customer_by_username();
void add_customer_balance();
void save_to_database();
void read_customer_data();
void customer_login();
void change_passowrd();
void check_balance();
void load_food_menu();
void view_meal_menu();
void place_order();

int main ()
{
    read_customer_data();
    load_food_menu();

    while (1)
    {
        int choice = -1;
        fflush(stdin);
        system("cls");
        printf("\n");
        printf("                     ***************************************************\n");
        printf("                     *        Welcome to Meal Management System        *\n");
        printf("                     ***************************************************\n");
        printf("\n");
        printf("                     1. Manager Login\n");
        printf("                     2. Customer Login\n");
        printf("                     3. About Us\n");
        printf("                     4. Exit\n\n");
        printf("                     Enter your choice: ");

        scanf("%d", &choice);

        while (choice < 1 || choice > 4)
        {
            printf("                     Please enter a valid choice: ");
            fflush(stdin);
            scanf("%d", &choice);
        }

        switch (choice)
        {
        case 1:
            manager_login();
            break;
        case 2:
            customer_login();
            break;
        case 3:
            about_us();
            break;
        case 4:
            system("cls");
            exit(0);
        }
    }
}

void manager_login()
{
    if (isManagerLogged == 0)
    {
        char managerUsername[20], managerPassword[20];

        FILE *file;
        file = fopen("database/managerData.txt", "r");
        if (file == NULL)
        {
            printf("\n\nError opening the file.\n");
            getch();
        }
        fscanf(file, "Username: %s\n", managerUsername);
        fscanf(file, "Password: %s\n", managerPassword);
        fclose(file);

        while (1)
        {
            fflush(stdin);
            system("cls");
            char username[20], password[20];

            printf("\n");
            printf("                     ***************************************************\n");
            printf("                     *                  Manager Login                  *\n");
            printf("                     ***************************************************\n");
            printf("\n");
            printf("                     Enter Username: ");
            scanf("%s", &username);
            printf("                     Enter Password: ");
            scanf("%s", &password);

            if (strcmp(username, managerUsername) == 0 && strcmp(password, managerPassword) == 0)
            {
                printf("\n                     Login Successful! Press any key to continue.");
                isManagerLogged = 1;
                getch();
                manager_menu();
                break;
            }
            else
            {
                printf("\n                     Login Failed. Press any key to try again.");
                getch();
            }
        }
    }
}

void manager_menu()
{
    int choice;
    fflush(stdin);
    system("cls");

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                 Manager Section                 *\n");
    printf("                     ***************************************************\n");
    printf("\n");
    printf("                     1. Add Customer\n");
    printf("                     2. Delete Customer\n");
    printf("                     3. View All Customer\n");
    printf("                     4. Search Customer by ID\n");
    printf("                     5. Search Customer by Username\n");
    printf("                     6. Add Customer Balance\n");
    printf("                     7. Logout\n\n");
    printf("                     Enter your choice: ");

    scanf("%d", &choice);

    while (choice < 1 || choice > 7)
    {
        printf("                     Please enter a valid choice: ");
        fflush(stdin);
        scanf("%d", &choice);
    }

    switch (choice)
    {
    case 1:
        add_customer();
        break;
    case 2:
        delete_customer();
        break;
    case 3:
        view_all_customer();
        break;
    case 4:
        search_customer_by_id();
        break;
    case 5:
        search_customer_by_username();
        break;
    case 6:
        add_customer_balance();
        break;
    case 7:
        isManagerLogged = 0;
        break;
    }
}
void add_customer()
{
    fflush(stdin);
    system("cls");
    node *newNode = (node *)malloc(sizeof(node));
    newNode->next = NULL;
    newNode->balance = 0;
    node *temp = head;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                   Add Customer                  *\n");
    printf("                     ***************************************************\n\n");

    printf("                     Enter Name: ");
    fflush(stdin);
    gets(newNode->name);
    printf("                     Enter ID: ");
    fflush(stdin);
    scanf("%d", &newNode->id);
    printf("                     Enter username: ");
    fflush(stdin);
    gets(newNode->username);
    printf("                     Enter Password: ");
    fflush(stdin);
    gets(newNode->password);
    printf("                     Enter Phone: ");
    fflush(stdin);
    gets(newNode->phone);

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("\n                     Customer added successfully. Enter any key to continue.");
    save_to_database();
    getch();
    manager_menu();
}

void delete_customer()
{
    fflush(stdin);
    system("cls");
    node *temp = head;
    int count = 0;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                  Delete Customer                *\n");
    printf("                     ***************************************************\n\n");

    printf("                     Enter Customer ID to delete: ");
    int ID;
    scanf("%d", &ID);

    while (temp != NULL)
    {
        if (temp->id == ID)
        {
            printf("\n                                      Data of Customer\n");
            printf("                     Name: %s\n", temp->name);
            printf("                     ID: %d\n", temp->id);
            printf("                     Username: %s\n", temp->username);
            printf("                     Password: %s\n", temp->password);
            printf("                     Balance: %d\n", temp->balance);
            printf("                     Phone: %s\n\n", temp->phone);
            count++;
            printf("                     Enter 1 to delete, 2 to cancel: ");
            fflush(stdin);
            int choice;
            scanf("%d", &choice);

            if (choice == 1)
            {
                if (temp == head)
                {
                    head = temp->next;
                    free(temp);
                    printf("\n                     Customer deleted successfully.");
                    break;
                }
                else
                {
                    node *prev = head;
                    while (prev->next != temp)
                    {
                        prev = prev->next;
                    }
                    prev->next = temp->next;
                    free(temp);
                    printf("\n                     Customer deleted successfully.");
                    break;
                }
            }
            else
            {
                break;
            }
        }
        temp = temp->next;
    }
    if (count==0)
    {
        printf("\n                     No data found for this ID");
    }
    printf("\n\n                     Enter any key to continue.");
    save_to_database();
    getch();
    manager_menu();
}

void view_all_customer()
{
    fflush(stdin);
    system("cls");
    node *temp = head;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                   All Customer                  *\n");
    printf("                     ***************************************************\n\n");

    if (temp == NULL)
    {
        printf("                     There is no customer!\n\n");
    }
    else
    {
        int i = 1;
        while (temp)
        {
            printf("                                      Data of Customer %d\n", i);
            printf("                     Name: %s\n", temp->name);
            printf("                     ID: %d\n", temp->id);
            printf("                     Username: %s\n", temp->username);
            printf("                     Password: %s\n", temp->password);
            printf("                     Balance: %d\n", temp->balance);
            printf("                     Phone: %s\n\n", temp->phone);

            temp = temp->next;
            i++;
        }
    }

    printf("                     Enter any key to continue.");
    getch();
    manager_menu();
}

void search_customer_by_id()
{
    fflush(stdin);
    system("cls");
    node *temp = head;
    int count = 0;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                  Search Customer                *\n");
    printf("                     ***************************************************\n\n");

    printf("                     Enter Customer ID to search: ");
    int ID;
    scanf("%d", &ID);

    while (temp != NULL)
    {
        if (temp->id == ID)
        {
            printf("\n                                      Data of Customer\n");
            printf("                     Name: %s\n", temp->name);
            printf("                     ID: %d\n", temp->id);
            printf("                     Username: %s\n", temp->username);
            printf("                     Password: %s\n", temp->password);
            printf("                     Balance: %d\n", temp->balance);
            printf("                     Phone: %s\n", temp->phone);
            count++;
        }
        temp = temp->next;
    }
    if (count==0)
    {
        printf("\n                     No data found for this ID\n");
    }
    printf("\n                     Enter any key to continue.");
    getch();
    manager_menu();
}

void search_customer_by_username()
{
    fflush(stdin);
    system("cls");
    node *temp = head;
    int count = 0;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                  Search Customer                *\n");
    printf("                     ***************************************************\n\n");

    printf("                     Enter Customer username to search: ");
    char uname[20];
    gets(uname);

    while (temp != NULL)
    {
        if (strcasecmp(temp->username, uname) == 0)
        {
            printf("\n                                      Data of Customer\n");
            printf("                     Name: %s\n", temp->name);
            printf("                     ID: %d\n", temp->id);
            printf("                     Username: %s\n", temp->username);
            printf("                     Password: %s\n", temp->password);
            printf("                     Balance: %d\n", temp->balance);
            printf("                     Phone: %s\n", temp->phone);
            count++;
        }
        temp = temp->next;
    }
    if (count==0)
    {
        printf("\n                     No data found for this Username\n");
    }
    printf("\n                     Enter any key to continue.");
    getch();
    manager_menu();
}

void add_customer_balance()
{
    fflush(stdin);
    system("cls");
    node *temp = head;
    int count = 0;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                    Add Balance                  *\n");
    printf("                     ***************************************************\n\n");

    printf("                     Enter Customer ID to add Balance: ");
    int ID;
    scanf("%d", &ID);

    while (temp != NULL)
    {
        if (temp->id == ID)
        {
            printf("\n                                      Data of Customer\n");
            printf("                     Name: %s\n", temp->name);
            printf("                     ID: %d\n", temp->id);
            printf("                     Balance: %d\n", temp->balance);
            count++;

            int amount = -1;
            while (amount < 1 || amount > 10000)
            {
                printf("\n                     Enter amount to add: ");
                fflush(stdin);
                scanf("%d", &amount);
            }

            temp->balance += amount;
            save_to_database();
            printf("\n                     Balance added successfully!\n");
        }
        temp = temp->next;
    }
    if (count==0)
    {
        printf("\n                     No customer found for this ID\n");
    }
    printf("\n                     Enter any key to continue.");
    getch();
    manager_menu();
}

void save_to_database()
{
    node *temp = head;

    FILE *file;

    file = fopen("database/customers.txt", "w");

    if (file == NULL)
    {
        printf("                     Error opening the file for writing.\n");
    }

    while (temp != NULL)
    {
        fprintf(file, "ID: %d\n", temp->id);
        fprintf(file, "Name: %s\n", temp->name);
        fprintf(file, "Username: %s\n", temp->username);
        fprintf(file, "Password: %s\n", temp->password);
        fprintf(file, "Balance: %d\n", temp->balance);
        fprintf(file, "Phone: %s\n\n", temp->phone);

        temp = temp->next;
    }

    fclose(file);
}

void read_customer_data()
{
    FILE* file;
    file = fopen("database/customers.txt", "r");

    if (file == NULL)
    {
        printf("Error opening the file for reading.\n");
        return;
    }

    node* lastCustomer = NULL;

    while (1)
    {
        node* newCustomer = (node*)malloc(sizeof(node));
        newCustomer->next = NULL;

        if (fscanf(file, "ID: %d\n", &newCustomer->id) == EOF)
        {
            break;
        }
        fscanf(file, "Name: %[^\n]\n", newCustomer->name);
        fscanf(file, "Username: %[^\n]\n", newCustomer->username);
        fscanf(file, "Password: %[^\n]\n", newCustomer->password);
        fscanf(file, "Balance: %d\n", &newCustomer->balance);
        fscanf(file, "Phone: %[^\n]\n\n", newCustomer->phone);

        if (head == NULL)
        {
            head = newCustomer;
        }
        else
        {
            lastCustomer->next = newCustomer;
        }

        lastCustomer = newCustomer;
    }
    fclose(file);
}

void customer_login()
{

    if (isCustomerLogged == 0)
    {
        while (1)
        {
            fflush(stdin);
            system("cls");
            char username[20], password[20], fileUsername[20], filePassword[20];

            printf("\n");
            printf("                     ***************************************************\n");
            printf("                     *                  Customer Login                 *\n");
            printf("                     ***************************************************\n");
            printf("\n");
            printf("                     Enter Username: ");
            scanf("%s", &username);
            printf("                     Enter Password: ");
            scanf("%s", &password);

            FILE *file;
            file = fopen("database/customers.txt", "r");
            if (file == NULL)
            {
                printf("\n\nError opening the file.\n");
                getch();
            }

            while (fscanf(file, "ID: %*d\nName: %*[^\n]\nUsername: %s\nPassword: %s\nBalance: %*s\nPhone: %*s\n\n", fileUsername, filePassword) == 2)
            {
                if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
                {
                    printf("\n                     Login Successful! Press any key to continue.");
                    isCustomerLogged = 1;
                    strcpy(loggedCustomerUsername, username);
                    getch();
                    fclose(file);
                    customer_menu();
                    return;
                }
            }
            fclose(file);

            if (isCustomerLogged == 0)
            {
                printf("\n                     Login Failed. Press any key to try again.");
                getch();
            }
        }
    }
}

void customer_menu()
{
    int choice;
    fflush(stdin);
    system("cls");

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                 Customer Section                *\n");
    printf("                     ***************************************************\n");
    printf("\n");
    printf("                     1. View Meal Menu\n");
    printf("                     2. Place an Order\n");
    printf("                     3. Check Balance\n");
    printf("                     4. View Profile\n");
    printf("                     5. Change Password\n");
    printf("                     6. Logout\n\n");
    printf("                     Enter your choice: ");

    scanf("%d", &choice);

    while (choice < 1 || choice > 6)
    {
        printf("                     Please enter a valid choice: ");
        fflush(stdin);
        scanf("%d", &choice);
    }

    switch (choice)
    {
    case 1:
        view_meal_menu();
        break;
    case 2:
        place_order();
        break;
    case 3:
        check_balance();
        break;
    case 4:
        view_profile();
        break;
    case 5:
        change_password();
        break;
    case 6:
        strcpy(loggedCustomerUsername, "");
        isCustomerLogged = 0;
        break;
    }
}

void check_balance()
{
    fflush(stdin);
    system("cls");
    node *temp = head;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                      Balance                    *\n");
    printf("                     ***************************************************\n\n");

    while (temp != NULL)
    {
        if (strcmp(temp->username, loggedCustomerUsername) == 0)
        {
            printf("                     You currently have %d taka on your account.\n", temp->balance);
            break;
        }
        temp = temp->next;
    }
    printf("\n                     Enter any key to continue.");
    getch();
    customer_menu();
}

void view_profile()
{
    fflush(stdin);
    system("cls");
    node *temp = head;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                      Profile                    *\n");
    printf("                     ***************************************************\n\n");

    while (temp != NULL)
    {
        if (strcmp(temp->username, loggedCustomerUsername) == 0)
        {
            printf("                     Name: %s\n", temp->name);
            printf("                     ID: %d\n", temp->id);
            printf("                     Username: %s\n", temp->username);
            printf("                     Password: %s\n", temp->password);
            printf("                     Balance: %d\n", temp->balance);
            printf("                     Phone: %s\n", temp->phone);
            break;
        }
        temp = temp->next;
    }
    printf("\n                     Enter any key to continue.");
    getch();
    customer_menu();
}

void change_password()
{
    fflush(stdin);
    system("cls");
    char oldPassword[20], newPassword[20];

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                  Change Password                *\n");
    printf("                     ***************************************************\n\n");

    node *temp = head;

    while (strcmp(temp->username, loggedCustomerUsername) != 0)
    {
        temp = temp->next;
    }

    printf("                     Enter Old Password: ");
    gets(oldPassword);

    if (strcmp(oldPassword, temp->password) == 0)
    {
        printf("                     Enter New Password: ");
        gets(newPassword);

        strcpy(temp->password, newPassword);
        printf("\n                     Password change successful!\n\n");
    }
    else
    {
        printf("\n                     You have entered wrong password!\n\n");
    }

    printf("                     Press any key to continue.");
    save_to_database();
    getch();
    customer_menu();
}

void load_food_menu()
{
    FILE *file;
    file = fopen("database/foods.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        getch();
    }
    node2 *current = NULL;
    while (1)
    {
        node2 *newNode = (node2 *)malloc(sizeof(node2));
        newNode->next = NULL;
        if (fscanf(file, "%d %s %d\n", &newNode->id, newNode->item, &newNode->price) == EOF)
        {
            free(newNode);
            break;
        }
        if (head2 == NULL)
        {
            head2 = newNode;
        }
        else
        {
            current->next = newNode;
        }
        current = newNode;
    }
    fclose(file);
}

void view_meal_menu()
{
    fflush(stdin);
    system("cls");
    node2 *temp = head2;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                     Meal Menu                   *\n");
    printf("                     ***************************************************\n\n");
    printf("                     ID         Name        Price\n");
    while (temp != NULL)
    {
        printf("                     %d  %s  %d\n", temp->id, temp->item, temp->price);
        temp = temp->next;
    }
    printf("\n                     Enter any key to continue.");
    getch();
    customer_menu();
}

void place_order()
{
    fflush(stdin);
    system("cls");
    node2 *temp = head2;

    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *                     Order Meal                  *\n");
    printf("                     ***************************************************\n\n");
    printf("                     ID         Name        Price\n");
    while (temp != NULL)
    {
        printf("                     %d  %s  %d\n", temp->id, temp->item, temp->price);
        temp = temp->next;
    }
    printf("\n                     Enter item ID to buy: ");

    int id;
    scanf("%d", &id);

    temp = head2;
    int count = 0;
    while (temp)
    {
        if (temp->id == id)
        {
            count++;
            break;
        }
        temp = temp->next;
    }

    if (count == 0)
    {
        printf("\n                     Please input a valid item ID\n");
    }
    else
    {
        node *temp2 = head;
        while (temp2)
        {
            if (strcmp(temp2->username, loggedCustomerUsername) == 0)
            {
                break;
            }
            temp2 = temp2->next;
        }

        if (temp->price > temp2->balance)
        {
            printf("\n                     You do not have sufficient balance.\n");
        }
        else
        {
            temp2->balance -= temp->price;
            printf("\n                     Order placed successfully. %d taka deducted.\n                     You currently have %d taka on your account.\n", temp->price, temp2->balance);
        }
    }

    printf("\n                     Enter any key to continue.");
    getch();
    customer_menu();
}

void about_us()
{
    system("cls");
    printf("\n");
    printf("                     ***************************************************\n");
    printf("                     *           About Meal Management System          *\n");
    printf("                     ***************************************************\n\n");
    printf("                     This C program is a Meal Management System that enables\n");
    printf("                     a manager to perform various operations on customer data,\n");
    printf("                     such as adding, deleting, viewing, searching, and updating\n");
    printf("                     records, with data stored in a linked list and a text file\n");
    printf("                     based database. It provides essential tools for managing\n");
    printf("                     customer accounts in a meal service.");
    printf("\n\n                     Enter any key to continue");
    getch();
}
