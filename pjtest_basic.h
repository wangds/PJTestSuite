#ifndef PJTEST_BASIC_H
#define PJTEST_BASIC_H

#include <CUnit/Basic.h>

typedef struct {
	const char *name;
	void (*func)(void);
} TestList;

typedef struct {
	const char *name;
	CU_InitializeFunc init;
	CU_CleanupFunc cleanup;

	const TestList *test;
} TestSuite;

#endif
