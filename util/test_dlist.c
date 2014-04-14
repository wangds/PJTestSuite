/* test_dlist.c */

#include "errcodes.h"
#include "linklist.h"
#include "test_util.h"

static Dlheader s_dlist;
static Dlheader s_dlist2;

static int
dlist_init(void)
{
	if (init_list(&s_dlist) != Success)
		return -1;

	if (init_list(&s_dlist2) != Success)
		return -1;

	return CUE_SUCCESS;
}

static int
dlist_cleanup(void)
{
	int ret = CUE_SUCCESS;

	if (free_dl_list(&s_dlist) != Success)
		ret = -1;

	if (free_dl_list(&s_dlist2) != Success)
		ret = -1;

	return ret;
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
	CU_ASSERT(&nodeb == nodea.prev && nodeb.next == &nodea);
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
	CU_ASSERT(&nodea == nodeb.prev && nodea.next == &nodeb);
	CU_ASSERT(is_tail(&nodeb));

	/* Remove from tail.
	 *  [a,b] -> []
	 */
	CU_ASSERT(rem_node(&nodea) == Success);
	CU_ASSERT(rem_node(&nodeb) == Success);
	CU_ASSERT_PTR_NULL(see_head(&s_dlist));
	CU_ASSERT_PTR_NULL(see_tail(&s_dlist));
}

static void
do_list_tohead(void)
{
	Dlnode nodea;
	Dlnode nodeb;
	Dlnode nodec;
	Dlnode noded;

	/* Form lists.
	 *  [], [] -> [a,b], [c,d]
	 */
	add_head(&s_dlist, &nodea);
	insert_after(&nodeb, &nodea);

	add_head(&s_dlist2, &noded);
	insert_before(&nodec, &noded);

	/* Append to head.
	 *  [a,b], [c,d] -> [], [a,b,c,d]
	 */
	CU_ASSERT(list_tohead(&s_dlist, &s_dlist2) == Success);
	CU_ASSERT(see_head(&s_dlist2) == &nodea);
	CU_ASSERT(&nodea == nodeb.prev && nodea.next == &nodeb);
	CU_ASSERT(&nodeb == nodec.prev && nodeb.next == &nodec);
	CU_ASSERT(&nodec == noded.prev && nodec.next == &noded);
	CU_ASSERT(see_tail(&s_dlist2) == &noded);
	CU_ASSERT_PTR_NULL(see_head(&s_dlist));
	CU_ASSERT_PTR_NULL(see_tail(&s_dlist));

	/* Remove nodes from lists. */
	init_list(&s_dlist);
	init_list(&s_dlist2);
}

static void
do_list_totail(void)
{
	Dlnode nodea;
	Dlnode nodeb;
	Dlnode nodec;
	Dlnode noded;

	/* Form lists.
	 *  [], [] -> [a,b], [c,d]
	 */
	add_head(&s_dlist, &nodea);
	insert_after(&nodeb, &nodea);

	add_head(&s_dlist2, &noded);
	insert_before(&nodec, &noded);

	/* Append to tail.
	 *  [a,b], [c,d] -> [a,b,c,d], []
	 */
	CU_ASSERT(list_totail(&s_dlist2, &s_dlist) == Success);
	CU_ASSERT(see_head(&s_dlist) == &nodea);
	CU_ASSERT(&nodea == nodeb.prev && nodea.next == &nodeb);
	CU_ASSERT(&nodeb == nodec.prev && nodeb.next == &nodec);
	CU_ASSERT(&nodec == noded.prev && nodec.next == &noded);
	CU_ASSERT(see_tail(&s_dlist) == &noded);
	CU_ASSERT_PTR_NULL(see_head(&s_dlist2));
	CU_ASSERT_PTR_NULL(see_tail(&s_dlist2));

	/* Remove nodes from lists. */
	init_list(&s_dlist);
	init_list(&s_dlist2);
}

static const TestList TL_dlist[] = {
	{ "add_head", do_add_head },
	{ "add_tail", do_add_tail },
	{ "list_tohead", do_list_tohead },
	{ "list_totail", do_list_totail },
	{ NULL, NULL }
};

const TestSuite TS_dlist = {
	"dlist",
	dlist_init,
	dlist_cleanup,
	TL_dlist
};
