#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 20

struct sickPerson {
    char surname[MAXLEN];
    char place[MAXLEN];
    struct sickPerson *next;
};

struct hospital {
    char name[MAXLEN];
    int allPlaces;
    int freePlaces;
    int distance;
    struct hospital *next;
};

int globalFlag = 0;


void createHospital(hospital **hospitalList);
void statisticHospital(hospital *hospitalList);
void createSick(sickPerson **sickList, hospital **hospitalList);
void statisticSick(sickPerson *sickList);

// Функуция удаления больных неисправна
void deleteSick(sickPerson **sickList, hospital *hospitalList);
int closestHospital(hospital *hospitalList);
int allocation(hospital *hospitalList, sickPerson *sickList);
int Flag(hospital *hospitalListReserve, int min);

int menu();


int main() {
    struct sickPerson *sickList;
    struct hospital *hospitalList;

    sickList = NULL;
    hospitalList = NULL;

    int flag = 0;
    while (flag != 1) {
        switch (menu()) {
            case 1:
                createHospital(&hospitalList);
                break;
            case 2:
                createSick(&sickList, &hospitalList);
                break;
            case 3:
                statisticHospital(hospitalList);
                break;
            case 4:
                statisticSick(sickList);
                break;
            case 5:
                allocation(hospitalList, sickList);
                break;
            case 6:
                deleteSick(&sickList, hospitalList);
                break;
            default:
                puts("Проверьте ввод.");
                break;

            case 0:
                puts("Завершение работы...");
                flag = 1;
                break;
        }
    }

    free(sickList);
    free(hospitalList);
    return 0;
}

int menu() {
    int option;
    printf("\n\n-------МЕНЮ-------");
    printf("\n 1) Создать больницы.");
    printf("\n 2) Добавить больных.");
    printf("\n 3) Список больниц.");
    printf("\n 4) Список больных.");
    printf("\n 5) Перераспределение больных по больницам.");
    printf("\n 6) Выписка больных.");
    printf("\n > ");
    fflush(stdin);
    scanf("%d", &option);
    return option;
}

void createHospital(hospital **hospitalList) {
    if (hospitalList == NULL) {
        printf("Ошибка.");
        return;
    }


    int option = 0;
    globalFlag = 0;
    hospital *hospitalListReserve;

    printf("\n\n--------- Ввод новой больницы ---------");
    do {
        hospitalListReserve = (hospital*) calloc (1, sizeof(hospital));
        fflush(stdin);
        printf("\n Введите название больницы: ");
        scanf("%s", hospitalListReserve->name);

        printf("\n Введите общее количество мест для больных: ");
        scanf("%d", &hospitalListReserve->allPlaces);

        printf("\n Введите количество свободных мест для больных: ");
        scanf("%d", &hospitalListReserve->freePlaces);

        printf("\n Введите расстояние до больного: ");
        scanf("%d", &hospitalListReserve->distance);


        if (!hospitalList)
            *hospitalList = hospitalListReserve;
        else {
            hospitalListReserve->next = *hospitalList;
            *hospitalList = hospitalListReserve;
        }

        printf("\n\n Желаете продолжить?\n1)Да\n2)Нет\n");
        fflush(stdin);
        scanf("%d", &option);
    } while (option != 2);

    getchar();
    getchar();

    return;
}

void statisticHospital(hospital *hospitalList) {
    if (!hospitalList) {
        printf("\n Нет информации о больницах.");
        return;
    }

    printf("\n\n------------Информация о больницах------------");
    do {
        printf("\n Больница : %s.", hospitalList->name);
        printf("\n Общее количество мест: %d.", hospitalList->allPlaces);
        printf("\n Количество свободных мест: %d.\n", hospitalList->freePlaces);

        hospitalList = hospitalList -> next;
    } while (hospitalList);

    getchar();
    getchar();

    return;
}

void createSick (sickPerson **sickList, hospital **hospitalList) {
    int option;

    printf("\n\n------------Ввод информации о больных------------");
    do {
        struct sickPerson *sickListReserve;
        sickListReserve = (sickPerson*) calloc (1, sizeof(sickPerson));
        printf("\n Введите фамилию больного: ");
        fflush(stdin);
        scanf("%s", sickListReserve->surname);
        fflush(stdin);

        if (!sickList)
            *sickList = sickListReserve;
        else {
            sickListReserve -> next = *sickList;
            *sickList = sickListReserve;
        }

        if (!allocation(*hospitalList, *sickList)) {
            strcpy((**sickList).place, "Не распределен");
        }

        printf("\n\n Желаете продолжить?\n1)Да\n2)Нет\n");
        fflush(stdin);
        scanf("%d", &option);
    } while (option != 2);

    getchar();
    getchar();

    return;
}


void statisticSick(sickPerson *sickList) {
    if (!sickList) {
        printf("\n Список больных пуст.");
        getchar();
        getchar();
        return;
    }

    printf("\n\n-----------Список больных-----------");
    do {
        printf("\n Больной: %s", sickList->surname);
        printf("\n Больница в которой содержится: %s", sickList->place);
        sickList = sickList->next;
    } while (sickList);

    getchar();
    getchar();

    return;
}


int closestHospital(hospital *hospitalList) {
    if (!hospitalList) {
        printf("\n\n Нет очереди больниц.");
        return 0;
    }

    hospital *hospitalListReserve = hospitalList;
    int min = 1000000;
    int flag = 0;

    do {
        if (min > hospitalList->distance && hospitalList->freePlaces > 0) {
            min = hospitalList->distance;
        }
        hospitalList = hospitalList -> next;
    } while (hospitalList);

    flag = Flag(hospitalListReserve, min);
    printf("\n Минимальное расстоение: %d", min);
    //printf("\n Flag = %d", flag);

    getchar();
    getchar();

    return flag;
}


int Flag(hospital *hospitalListReserve, int min) {
    int flag = 0;
    do {
        flag++;
        if (hospitalListReserve->distance == min) break;
        hospitalListReserve = hospitalListReserve -> next;
    } while (hospitalListReserve);

    return (flag - 1);
}


int allocation(hospital *hospitalList, sickPerson *sickList) {
    if (!hospitalList) {
        printf(" Нет списка больниц.");
        getchar();
        getchar();
        return 0;
    }

    if (!sickList) {
        printf(" Нет списка больных.");
        getchar();
        getchar();
        return 0;
    }

    int flag = 0;
    int distanceFlag = 0;
    globalFlag = 0;
    int k = closestHospital(hospitalList);
    do {
        if (distanceFlag == k) {
            if (hospitalList->freePlaces > 0 && isgraph(sickList->place[0]) == 0) {
                strcpy(sickList->place, hospitalList->name);
                hospitalList->freePlaces--;
                flag = 1;
                break;
            }
        }

        hospitalList = hospitalList -> next;
        distanceFlag++;
    } while (hospitalList);

    return flag;
}


void deleteSick(sickPerson **sickList, hospital *hospitalList) {
    if (!sickList) {
        printf(" Нет списка больных.");
        return;
    }

    if (!hospitalList) {
        printf(" Нет списка больниц.");
        return;
    }

    char *str = (char*) malloc (MAXLEN * sizeof(char));
    printf("\n\n Введите фамилию больного для поиска.");
    fflush(stdin);
    scanf("%s", str);

    if (!(*sickList)->next && (!strcmp((*sickList)->surname,str))) {
        do {
            if (!strcmp(hospitalList->name, (*sickList)->place)) {
                hospitalList->freePlaces++;
                free(*sickList);
                *sickList = NULL;
                printf("\n\n -- Больной удалён --");
                return;
            }

            hospitalList = hospitalList->next;
        } while (hospitalList);
    }
}