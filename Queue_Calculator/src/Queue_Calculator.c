/*
 ============================================================================
 Name        : Queue.c
 Author      : AndrewVorotyntsev
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



float factorial(float n)
{
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

/* Определяем элемент очереди */
typedef struct list_node {
    struct list_node *next;
    int type;
    int oper;
    float *A;
    float *B;
} list_node_t;

/* Определяем саму очередь */
typedef struct list {

    int size;
    /* начало списка */
    list_node_t *head;
    /* конец списка */
    list_node_t *tail;
} list_t;

/* Инициализация массива */
list_t * create_list(void)
{
    list_t *lt = malloc(sizeof(list_t));

    lt->size = 0;
    lt->head = NULL;
    lt->tail = lt->head;

    return lt;
}

void list_push_back(list_t *lt, int type, int oper,float *A,float *B)
{
    list_node_t * node = malloc(sizeof(list_node_t));
    node->type=type;
    node->oper=oper;
    node->A=A;
    node->B=B;
    if(lt->tail != NULL)
        lt->tail->next = node;
    else {
        lt->head = node;
    }

    lt->tail = node;
    lt->size += 1;
}


void * list_pop(list_t *lt)
{
    if(lt->size == 0){
        /* Список пуст */
        return NULL;
    }

    list_node_t *node = lt->head;
    void *sign = lt->head;

    lt->size -= 1;
    lt->head = node->next;

    free(node);

    if(lt->size == 0){
        /* Это был последний элемент */
        lt->head = NULL;
        lt->tail = NULL;
    }

    //return lt->head;
    //lt->head = node->next;
    return sign;
}


//struct element* getElement();

typedef struct nodeResult
{
  float C; // значения
  struct nodeResult *next; // указатель на следующий элемент
}nodeResult;


typedef struct listResult
{
    nodeResult* head;
    nodeResult* tail;
}listResult;




listResult * initializelistResult(void)
{
    listResult* lt = malloc(sizeof(list_t));
    lt->head = NULL;
    lt->tail = lt->head;

    return lt;
}

void putResult(listResult* lst ,float C)
{
    nodeResult* t = (nodeResult*) malloc(sizeof(nodeResult));
    t->C=C;
    t->next = 0;
    if(lst->head == 0)
    {
       lst->head = t;
       lst->tail = t;
       return;
    }
    lst->tail->next = t;
    lst->tail = t;
}


void printResult(const listResult* const lst)
{
    FILE *result ;
    result = fopen("Result.txt" , "w");
    float p;
    for(nodeResult* tmp = lst->head; tmp; tmp = tmp->next){
        p = tmp->C;
        printf("p=%f",p);
        fprintf(result,"%f",p);
    }
}

int main(void) {
    list_t *queue = create_list();
    list_node_t* node;
    FILE *write ;
    write = fopen("Data.txt", "r");
    int t,o,r,k,l;
    float *A,*B,*C,e;
    r = 1;
    k = 0;//Длинна выводимого результата(Кол-во чисел)
    l = 0;//количество операций
    while(r == 1)
    {
        fscanf(write ,"%i" , &t);
        printf("t=%i,",t);
        A = malloc(t*sizeof(float));//Выделение памяти для векторов
        B = malloc(t*sizeof(float));
        fscanf(write ,"%i" , &o);
        for (int y=0;y<t;y++){
            fscanf(write,"%f", &A[y]);
        }
        for (int l=0;l<t;l++){
            fscanf(write,"%f", &B[l]);

        }
        if (t == 1)
            k = k + 1;
        if (t > 1)
        {
            if (o != 2)
                k = k + t;
            if (o == 2)
                k = k + 1;
        }
        printf("k=%i,",k);
        fscanf(write ,"%i" , &r);
        l = l + 1;
        list_push_back(queue,t,o,A,B);//Записываем данные
    }
    printf("fin=%i",k);
    fclose(write);
    C = malloc(k*sizeof(float));//Массив для записи результатов
    int j;
    j = 0;
    while(l != 0)
    {
        node = list_pop(queue);//Получаем указатель на элемент

        if (node->type==1)
        {
            switch (node->oper)
            {
                case 0:
                    C[j] = node->A[0]+node->B[0];
                    j = j + 1;
                    break;
                case 1:
                    C[j] = node->A[0]-node->B[0];
                    j = j + 1;
                    break ;
                case 2:
                    C[j] = node->A[0]*node->B[0];
                    j = j + 1;
                    break ;
                case 3:
                    C[j] = node->A[0]/node->B[0];
                    j = j + 1;
                    break;
                case 4:
                    C[j] = pow(node->A[0],node->B[0]);
                    j = j + 1;
                    break;
                case 5:
                    C[j] = factorial(node->A[0]);
                    j = j + 1;
                    break;
            }
        }
        else
        {
            switch (node->oper)
                {
                case 0:
                    for (int h=0;h<node->type;h++)
                    {
                        C[j] = node->A[h]+node->B[h];
                        j = j + 1;
                    }
                    break;
                case 1:
                    for (int u=0;u<node->type;u++)
                    {
                        C[j] = node->A[u]-node->B[u];
                        j = j + 1;
                    }
                    break;
                case 2:
                    e=0;
                    for (int s=0;s<node->type;s++)
                    {
                        float d;
                        d=node->A[s]*node->B[s];
                        e=e+d;
                    }
                    C[j] = e;
                    j = j + 1;
                    break;
                }
        }
    printf("j=%i,",j);
    l = l - 1;
    if (j == k)
        break;
    }
    listResult *answer = initializelistResult();
    for (int w=0;w<j;w++)
    {
        printf("C=%f", C[w]);
        putResult(answer ,C[w]);
    }
    printf("j=%i", j);
    printResult(answer);
    puts("OK");
}


