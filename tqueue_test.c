#include <stdio.h>
#include <string.h>
#include "tqueue.c"

#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define RESET   "\033[0m"		/* Reset */
int nTest = 1;

void assertEqualsPtr(void* exp, void *got);
void assertNotNullPtr(void* ptr);
void assertNotPtr(void* ptr);
void assertInt(int exp, int got);

void testEnqueue() {
    TQueue q = NULL;

    int a = 1;
    int b = 2;

	assertInt(0, tqueue_size(q));
    tqueue_enqueue(&q, (void *) &a);
	assertInt(1, tqueue_size(q));
    tqueue_enqueue(&q, (void *) &b);

    TQueue q2 = tqueue_at_offset(q, 0);
    int *v = (int *) (q2->data);

	assertEqualsPtr(q, q2);
	assertEqualsPtr(&a, v);
	assertInt(2, tqueue_size(q));

    void *data = tqueue_pop(&q);
    int *dataD = (int *) data;

	assertEqualsPtr(&a, data);
	assertInt(a, *dataD);

    data = tqueue_pop(&q);
    dataD = (int *) data;

	assertEqualsPtr(&b, data);
	assertInt(b, *dataD);
	assertInt(0, tqueue_size(q));
}

void assertEqualsPtr(void* exp, void *got)
{
	if (exp != got) 
	{
		char* str;
		sprintf(str, "Expected %p \t Got %p", exp, got);
		printf("%sFAILED %d \t %s", RED, nTest, str);
	}
	else {
		printf("%sSUCCESS %d", GREEN, nTest);
	}
	
	nTest++;
	printf("%s\n", RESET);
}


void assertInt(int exp, int got)
{
	if (exp != got)
	{
		char* str;
		sprintf(str, "Expected %p \t Got %p", exp, got);
		printf("%sFAILED %d \t %s", RED, nTest, str);
	}
	else {
		printf("%sSUCCESS %d", GREEN, nTest);
	}

	nTest++;
	printf("%s\n", RESET);
}

void assertNotNullPtr(void* ptr)
{
	if (ptr != NULL)
	{
		printf("%sSUCCESS %d", GREEN, nTest);
	} 
	else
	{
		printf("%sFAILED %d \t ptr not NULL", RED, nTest);
	}

	nTest++;
	printf("%s\n", RESET);
}

void assertNullPtr(void* ptr)
{
	if (ptr == NULL)
	{
		printf("%sSUCCESS %d", GREEN, nTest);
	}
	else
	{
		printf("%sFAILED %d \t ptr not NULL", RED, nTest);
	}

	nTest++;
	printf("%s\n", RESET);
}
