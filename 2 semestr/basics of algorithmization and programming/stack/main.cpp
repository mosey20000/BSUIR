#include <stdlib.h>
#include <iostream>

struct Node {
    char info;
    struct Node *next;
};


void clearmemory(struct Node **stack);
void show(struct Node *stack);
char pop(struct Node **stack);
void push(struct Node **stack, char symbol);
int menu();


int main() {
    int flag = 0;
    int stackSize = 0;

    struct Node *begin = NULL, *stack;

    while (flag == 0) {
        switch (menu()) {
            case 1:
                std::cout << "Enter symbol to push in stack." << std::endl;
                fflush(stdin);
                char tempSymbol;
                std::cin >> tempSymbol;
                push(&begin, tempSymbol);
                stackSize++;
                std::cout << std::endl << std::endl;
                break;
            case 2:
                std::cout << "Stack include: " << std::endl;
                show(begin);
                std::cout << std::endl << std::endl;
                getchar();
                getchar();
                break;
            case 4:
                clearmemory(&begin);
                std::cout << std::endl << std::endl;
                std::cout << "Stack is cleared." << std::endl;
                std::cout << "Exiting..." << std::endl;
                exit(0);
                break;
            default:
                std::cout << "Error. Try again." << std::endl;
                break;
            case 3:
                std::cout << "Function to solve the task." << std::endl;
                char *string = (char*) malloc ((stackSize + 1) * sizeof (char));
                for (int i = 0; i < stackSize; i++) {
                    string[i] = pop(&begin);
                }
                string[stackSize + 1] = '\0';
                // До этого этапа содержимое стека помещается в строку в обратном порядке
                // Необходимо перевернуть строку
                for (int i = 0; i < stackSize/2; i++) {
                    char sTemp = string[i];
                    string[i] = string[stackSize - i - 1];
                    string[stackSize - i - 1] = sTemp;
                }
                std::cout << "String = " << string << std::endl;
                char digit;
                int index = 0;
                for (int i = 0; i < stackSize; i++) {
                    if (string[i] == '+') {
                        digit = '+';
                        index = i;
                        break;
                    }
                    if (string[i] == '-') {
                        digit = '-';
                        index = i;
                        break;
                    }
                    if (string[i] == '*') {
                        digit = '*';
                        index = i;
                        break;
                    }
                    if (string[i] == '/') {
                        digit = '/';
                        index = i;
                        break;
                    }
                }

                char *string1 = (char*) malloc ((stackSize + 1) * sizeof (char));
                int j = 0;
                for (int i = index+1; i < stackSize; i++)
                    string1[j++] = string[i];
                string1[j] = '\0';

                int num1 = atoi(string);
                int num2 = atoi(string1);
                switch (digit) {
                    case '+':
                        std::cout << "Result is = " << num1+num2 << std::endl;
                        break;
                    case '-':
                        std::cout << "Result is = " << num1-num2 << std::endl;
                        break;
                    case '*':
                        std::cout << "Result is = " << num1*num2 << std::endl;
                        break;
                    case '/':
                        std::cout << "Result is = " << num1/num2 << std::endl;
                        break;
                }

                free(string);
                free(string1);

                break;
        }
    }


    return 0;
}

char pop(struct Node **stack) {
    char symbol;
    struct Node *temp = *stack;
    symbol = (*stack) -> info;
    *stack = (*stack) -> next;
    delete temp;

    return symbol;
}

void push(struct Node **stack, char symbol) {
    struct Node *temp = new struct Node;
    temp -> info = symbol;
    temp -> next = *stack;
    *stack = temp;
}

void show(struct Node *stack) {
    struct Node *temp = stack;
    while (temp) {
        std::cout << temp -> info << " ";
        temp = temp -> next;
    }

    std::cout << std::endl << std::endl;
    return;
}

void clearmemory(struct Node **stack) {
    struct Node *temp;
    while (*stack != NULL) {
        temp = *stack;
        *stack = (*stack) -> next;
        delete temp;
    }

    return;
}

int menu() {
    std::cout << "1 - Push stack." << std::endl;
    std::cout << "2 - See stack." << std::endl;
    std::cout << "3 - Solve problem." << std::endl;
    std::cout << "4 - Delete stack. Clear memory." << std::endl;

    int option;
    fflush(stdin);
    std::cin >> option;

    return option;
}
