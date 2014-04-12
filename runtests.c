/* runtests.c */

#include <stdio.h>
#include "pjtest_basic.h"
#include "util/test_util.h"

static const TestSuite *suite[] = {
	&TS_pjassert,
	NULL
};

static int
add_suite(const TestSuite *s)
{
	CU_pSuite pSuite = CU_add_suite(s->name, s->init, s->cleanup);
	int i;

	if (!pSuite)
		return -1;

	for (i = 0; s->test[i].func != NULL; i++) {
		if (!CU_add_test(pSuite, s->test[i].name, s->test[i].func))
			return -1;
	}

	return CUE_SUCCESS;
}

int
main(int argc, char *argv[])
{
	int i;
	(void)argc;
	(void)argv;

	stderr = freopen("error.log", "wb", stderr);
	if (!stderr)
		goto end;

	/* Initialize the CUnit test registry. */
	if (CU_initialize_registry() != CUE_SUCCESS)
		goto end;

	/* Add suites to the registry. */
	for (i = 0; suite[i] != NULL; i++) {
		const int result = add_suite(suite[i]);
		if (result != CUE_SUCCESS)
			goto cleanup_registry;
	}

	/* Run all tests using the CUnit Basic interface. */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

cleanup_registry:
	CU_cleanup_registry();

end:
	return CU_get_error();
}
