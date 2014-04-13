/* test_dlist.c */

#include "errcodes.h"
#include "linklist.h"
#include "test_util.h"

static Dlheader s_dlist;

static int
dlist_init(void)
{
	return (init_list(&s_dlist) == Success) ? CUE_SUCCESS : -1;
}

static int
dlist_cleanup(void)
{
	return (free_dl_list(&s_dlist) == Success) ? CUE_SUCCESS : -1;
}

static void
do_add_head(void)
{
	Dlnode nodea;
	Dlnode nodeb;

	/* Add to head.
	 *  [] -> [a,b]
	 */
	CU_ASSERT(add_head(&s_dlist, &nodea) == Success);
	CU_ASSERT(add_head(&s_dlist, &nodeb) == Success);
	CU_ASSERT(is_head(&nodeb));
	CU_ASSERT(&nodeb == nodea.prev);
	CU_ASSERT(nodeb.next == &nodea);
	CU_ASSERT(is_tail(&nodea));

	/* Remove from head.
	 *  [b,a] -> []
	 */
	CU_ASSERT(rem_node(&nodeb) == Success);
	CU_ASSERT(rem_node(&nodea) == Success);
	CU_ASSERT_PTR_NULL(see_head(&s_dlist));
	CU_ASSERT_PTR_NULL(see_tail(&s_dlist));
}

static void
do_add_tail(void)
{
	Dlnode nodea;
	Dlnode nodeb;

	/* Add to tail.
	 *  [] -> [a,b]
	 */
	CU_ASSERT(add_tail(&s_dlist, &nodea) == Success);
	CU_ASSERT(add_tail(&s_dlist, &nodeb) == Success);
	CU_ASSERT(is_head(&nodea));
	CU_ASSERT(&nodea == nodeb.prev);
	CU_ASSERT(nodea.next == &nodeb);
	CU_ASSERT(is_tail(&nodeb));

	/* Remove from tail.
	 *  [a,b] -> []
	 */
	CU_ASSERT(rem_node(&nodea) == Success);
	CU_ASSERT(rem_node(&nodeb) == Success);
	CU_ASSERT_PTR_NULL(see_head(&s_dlist));
	CU_ASSERT_PTR_NULL(see_tail(&s_dlist));
}

static const TestList TL_dlist[] = {
	{ "add_head", do_add_head },
	{ "add_tail", do_add_tail },
	{ NULL, NULL }
};

const TestSuite TS_dlist = {
	"dlist",
	dlist_init,
	dlist_cleanup,
	TL_dlist
};
