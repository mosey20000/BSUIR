#include <iostream>
#include <iomanip>
#include <algorithm>


struct TreeNode {
    int info;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct QueueNode {
    int info;
    struct QueueNode *next;
    struct QueueNode *previous;
};

int size = 0;
int *array;

int menu();
void addQueue(struct QueueNode **begin, struct QueueNode **end);
void putQueue(struct QueueNode *ptr, int type);
void QueueToArray(struct QueueNode *begin);
void sortAlghoritm(int *arr, int len);

void makeBalancedTree(struct TreeNode **ptr, int n, int k, int *a);
void putTree(struct TreeNode *ptr, int depth);


int main() {
    struct QueueNode *begin, *end;
    struct TreeNode *node;
    // begin = tail;
    // end = head;

    while (1) {
        switch(menu()) {
            case 1:
                addQueue(&begin, &end);
                size++;
                break;
            case 2:
                std::cout << "Use correct option to see your queue." << std::endl;
                std::cout << "1 - Start from the tail." << std::endl;
                std::cout << "0 - Start from the head." << std::endl;
                int seeOption;
                fflush(stdin);
                std::cin >> seeOption;
                if (seeOption == 1) {
                    putQueue(end, 0);
                }
                if (seeOption == 0) {
                    putQueue(begin, 1);
                }
                std::cout << std::endl << std::endl;
                break;

            case 3:
                array = (int*) malloc (size * sizeof(int));
                QueueToArray(end);
                sortAlghoritm(array, size);
                makeBalancedTree(&node, 0, size, array);
                break;
            case 4:
                putTree(node , 0);
                break;
            default:
                std::cout << "Error. Try another variant." << std::endl;
                break;
            case 0:
                exit(0);
                break;
        }
    }

    return 0;
}

int menu() {
    std::cout << "Menu for the laboratory work." << std::endl;
    std::cout << "1 - Add element to the queue." << std::endl;
    std::cout << "2 - Put queue in console." << std::endl;
    std::cout << "3 - Create tree from the queue" << std::endl;
    std::cout << "4 - Put tree in console." << std::endl;

    int option;
    fflush(stdin);
    std::cin >> option;
    std::cout << std::endl << std::endl;
    return option;
}

void addQueue(struct QueueNode **begin, struct QueueNode **end) {
    struct QueueNode *temp;
    if (!(temp = (struct QueueNode*) malloc (1 * sizeof(struct QueueNode)))){
        std::cout << "Not enought memory to create new queue element." << std::endl;
        return;
    }

    std::cout << "Write number to put in queue: ";
    fflush(stdin);
    std::cin >> temp -> info;
    if (!*begin || !*end) {
        *begin = temp;
        *end = temp;
    } else {
        temp -> next = *end;
        (*end) -> previous = temp;
        *end = temp;
    }
}


void putQueue(struct QueueNode *ptr, int type) {
    std::cout << "Queue information: " << std::endl;
    if (!ptr) {
        std::cout << "Queue is not created or empty." << std::endl;
        return;
    }

    do {
        std::cout << std::setw(5) << ptr -> info;
        if (!type) ptr = ptr -> next; // to the head of the queue (1)
        else ptr = ptr -> previous;   // to the tail of the queue (0)
    } while (ptr);

    return;
}

void QueueToArray(struct QueueNode *begin) {
    if (!begin) {
        std::cout << "Queue is not created or empty." << std::endl;
        return;
    }

    int i = 0;
    do {
        array[i++] = begin -> info;
        begin = begin -> next;
    } while (begin);

    return;
}

void sortAlghoritm(int *arr, int len) {
    int gap, i, j;
    for (gap = len/2; gap > 0; gap = gap/2)
        for (i = gap; i < len; i++)
            for (j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap)
            {
                int temp = arr[j];
                arr[j] = arr[j + gap];
                arr[j + gap] = temp;
            }

    return;
}

void makeBalancedTree(struct TreeNode **ptr, int n, int k, int *a) {
    if (n == k) {
        *ptr = NULL;
        return;
    }
    else {
        int m = (n + k) / 2;
        *ptr = new TreeNode;
        (*ptr) -> info = a[m];
        makeBalancedTree(&(*ptr) -> left, n, m, a);
        makeBalancedTree(&(*ptr) -> right, m+1, k, a);
    }
}

void putTree(struct TreeNode *temp, int depth) {
    if (temp) {
        putTree(temp->left, depth + 1);
        for (int i = 0; i < depth; i++)
            std::cout << "  ";
        std::cout << temp->info;
        std::cout << std::endl;
        putTree(temp->right, depth+1);
    }
}
