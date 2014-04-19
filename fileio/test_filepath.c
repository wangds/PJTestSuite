/* test_filepath.c */

#include "errcodes.h"
#include "filepath.h"
#include "test_fileio.h"

static void
do_filepath_dos(void)
{
	FilePath *filepath;
	char out[8];

	/* C:\ani */
	filepath = filepath_create_from_string("C:\\ani\\");
	CU_ASSERT_PTR_NOT_NULL_FATAL(filepath);

	/* C:\ */
	CU_ASSERT(filepath_drop_tail(filepath) == Success);
	CU_ASSERT(filepath_to_cstr(filepath, '\\', out, sizeof(out)) == 3);
	CU_ASSERT_STRING_EQUAL(out, "C:\\");

	/* C:\ (again) */
	CU_ASSERT(filepath_drop_tail(filepath) == Success);
	CU_ASSERT(filepath_to_cstr(filepath, '\\', out, sizeof(out)) == 3);
	CU_ASSERT_STRING_EQUAL(out, "C:\\");

	/* C:\PAAT */
	CU_ASSERT(filepath_append(filepath, "paat") >= Success);
	CU_ASSERT(filepath_to_cstr(filepath, '\\', out, sizeof(out)) == 7);
	CU_ASSERT_STRING_EQUAL(out, "C:\\paat");

	filepath_destroy(filepath);
}

static void
do_filepath_unix(void)
{
	FilePath *filepath;
	char out[18];

	/* / */
	filepath = filepath_create_from_string("/");
	CU_ASSERT_PTR_NOT_NULL_FATAL(filepath);

	/* / */
	CU_ASSERT(filepath_drop_tail(filepath) == Success);
	CU_ASSERT(filepath_to_cstr(filepath, '/', out, sizeof(out)) == 1);
	CU_ASSERT_STRING_EQUAL(out, "/");

	filepath_destroy(filepath);

	/* ~/.config/pjpaint */
	filepath = filepath_create_from_string("~/.config/pjpaint/");
	CU_ASSERT_PTR_NOT_NULL_FATAL(filepath);

	/* Convert to cstring. */
	CU_ASSERT(filepath_to_cstr(filepath, '/', out, sizeof(out)) == 17);
	CU_ASSERT_STRING_EQUAL(out, "~/.config/pjpaint");

	filepath_destroy(filepath);
}

static const TestList TL_filepath[] = {
	{ "filepath_dos", do_filepath_dos },
	{ "filepath_unix", do_filepath_unix },
	{ NULL, NULL }
};

const TestSuite TS_filepath = {
	"filepath",
	NULL,
	NULL,
	TL_filepath
};
