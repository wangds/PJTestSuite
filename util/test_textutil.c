/* test_textutil.c */

#include "errcodes.h"
#include "test_util.h"
#include "textutil.h"

static void
do_text_count(void)
{
	CU_ASSERT(text_count_until_dir_delim("") == 0);
	CU_ASSERT(text_count_until_dir_delim("\\") == 0);
	CU_ASSERT(text_count_until_dir_delim("abc/123") == 3);
}

static void
do_text_ncopy(void)
{
	char dst[16];
	const char *src = "/abc\\";

	/* sizeof(dst) >= strlen(src) + 1
	 * -> return num bytes written, string copied.
	 */
	CU_ASSERT(text_ncopy(dst, "", sizeof(dst)) == 0);
	CU_ASSERT_STRING_EQUAL(dst, "");

	CU_ASSERT(text_ncopy(dst, src, sizeof(dst)) == (Errcode)strlen(src));
	CU_ASSERT_STRING_EQUAL(dst, src);

	/* sizeof(dst) <= strlen(src)
	 * -> return error, dst NUL terminated. */
	CU_ASSERT(text_ncopy(dst, src, strlen(src)) == Err_overflow);
	CU_ASSERT(dst[strlen(src) - 1] == '\0');
}

static void
do_text_ncopy_dir_delim(void)
{
	char dst[16];
	const char *src = "/abc\\";

	/* sizeof(dst) >= num bytes including next delim
	 * -> return num bytes written, string copied.
	 */
	CU_ASSERT(text_ncopy_dir_delim(dst, src, sizeof(dst)) == 0);
	CU_ASSERT_STRING_EQUAL(dst, "");

	CU_ASSERT(text_ncopy_dir_delim(dst, src + 1, sizeof(dst)) == 3);
	CU_ASSERT_STRING_EQUAL(dst, "abc");

	/* sizeof(dst) < num bytes including next delim
	 * -> return error, dst NUL terminated.
	 */
	CU_ASSERT(text_ncopy_dir_delim(dst, src + 1, 3) == Err_overflow);
	CU_ASSERT(dst[3 - 1] == '\0');
}

static const TestList TL_textutil[] = {
	{ "text_count", do_text_count },
	{ "text_ncopy", do_text_ncopy },
	{ "text_ncopy_dir_delim", do_text_ncopy_dir_delim },
	{ NULL, NULL }
};

const TestSuite TS_textutil = {
	"textutil",
	NULL,
	NULL,
	TL_textutil
};
