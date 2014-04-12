/* test_pjassert.c */

#include <stdbool.h>
#include "test_util.h"
#include "pjassert.h"

static void
do_pj_assert(void)
{
	/* pj_assert(true) -> return true. */
	CU_ASSERT_TRUE_FATAL(pj_assert(true));

	/* pj_assert(false) -> logs to stderr, return false. */
	CU_ASSERT_FALSE_FATAL(pj_assert(false));

	/* return value unused -> compilation warning. */
	/* pj_assert(true); */
}

static const TestList TL_pjassert[] = {
	{ "pj_assert", do_pj_assert },
	{ NULL, NULL }
};

const TestSuite TS_pjassert = {
	"pjassert",
	NULL,
	NULL,
	TL_pjassert
};
