/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf("------------------------2020039104 Son Ji Yeon------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");  // 배열이 비어있으면 출력할 내용이 없음을 알림
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);  // 배열의 인덱스를 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);  // 배열의 요소를 출력
	printf("\n");
}



int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;  // 현재 위치를 최소값 인덱스로 설정
		min = a[i];  // 현재 위치를 최소값으로 설정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];  // 더 작은 값을 찾으면 최소값 갱신
				minindex = j;  // 최소값 인덱스 갱신
			}
		}
		a[minindex] = a[i];  // 최소값을 현재 위치로 이동
		a[i] = min;  // 현재 위치에 최소값 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}


int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];  // 현재 값을 임시 변수에 저장
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];  // 현재 값보다 큰 값을 오른쪽으로 한 칸씩 이동
			j--;
		}
		a[j] = t;  // 현재 값을 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}


int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];  // 현재 요소와 다음 요소를 비교하여 큰 값을 임시 변수에 저장
				a[j-1] = a[j];  // 다음 요소를 현재 요소 위치에 저장
				a[j] = t;  // 임시 변수에 저장된 값을 다음 요소 위치에 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}


int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];  // 현재 값을 임시 변수에 저장
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];  // h 간격만큼 떨어진 요소들과 비교하여 현재 값보다 큰 값을 오른쪽으로 이동
					k -= h;
				}
				a[k] = v;  // 현재 값을 삽입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}


int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];  // 피벗을 배열의 마지막 요소로 설정
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);  // 피벗보다 큰 값을 찾을 때까지 i를 증가
			while(a[--j] > v);  // 피벗보다 작은 값을 찾을 때까지 j를 감소

			if (i >= j) break;  // i와 j가 엇갈리면 반복문 종료
			t = a[i];
			a[i] = a[j];
			a[j] = t;  // i와 j 위치의 값을 교환
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;  // 피벗을 정렬된 위치에 삽입

		quickSort(a, i);  // 피벗을 기준으로 분할된 왼쪽 부분 배열에 대해 재귀적으로 퀵 정렬 수행
		quickSort(a+i+1, n-i-1);  // 피벗을 기준으로 분할된 오른쪽 부분 배열에 대해 재귀적으로 퀵 정렬 수행
	}

	return 0;
}


int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  // 할당된 메모리의 주소를 복사하여 main에서 배열을 제어할 수 있도록 함
	} else {
		hashtable = *ht;  // hash table이 NULL이 아닌 경우, table 재활용하고 -1로 초기화
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;  // 해시 테이블을 -1로 초기화

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];  // 배열의 요소를 키로 설정
		hashcode = hashCode(key);  // 키에 대한 해시 코드 계산

		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;  // 해당 해시 코드 위치가 비어있으면 키를 저장
		} else {
			index = hashcode;

			while (hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;  // 충돌이 발생한 경우 다음 위치로 이동
			}
			hashtable[index] = key;  // 충돌이 발생하지 않는 위치에 키를 저장
		}
	}

	return 0;
}


int search(int *ht, int key)
{
	int index = hashCode(key);  // 주어진 키에 대한 해시 코드 계산

	if (ht[index] == key)
		return index;  // 해시 테이블에서 해당 위치에 저장된 키와 일치하면 해당 인덱스 반환

	while (ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;  // 충돌이 발생한 경우 다음 위치로 이동
	}
	return index;  // 일치하는 키를 찾을 때까지 반복하여 인덱스 반환
}
