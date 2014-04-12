/* test_slist.c */

#include "linklist.h"
#include "test_util.h"

static void
do_join_slists(void)
{
	Slnode nodea = { NULL };
	Slnode nodeb = { NULL };
	Slnode nodec = { NULL };
	Slnode *list = NULL;

	/* Add to empty list.
	 *  [] -> [a]
	 */
	list = join_slists(&nodea, list);
	CU_ASSERT(slist_el(list, 0) == &nodea);

	/* Add to head.
	 *  [a] -> [b,a]
	 */
	list = join_slists(&nodeb, list);
	CU_ASSERT(slist_el(list, 0) == &nodeb);
	CU_ASSERT(slist_el(list, 1) == &nodea);

	/* Remove from head.
	 *  [b,a] -> [a]
	 */
	list = remove_el(list, &nodeb);
	nodeb.next = NULL;
	CU_ASSERT(slist_el(list, 0) == &nodea);

	/* Add to tail.
	 *  [a] -> [a,b,c]
	 */
	list = join_slists(list, join_slists(&nodeb, &nodec));
	CU_ASSERT(slist_el(list, 0) == &nodea);
	CU_ASSERT(slist_el(list, 1) == &nodeb);
	CU_ASSERT(slist_el(list, 2) == &nodec);

	/* Remove from middle.
	 *  [a,b,c] -> [a,c]
	 */
	list = remove_el(list, &nodeb);
	CU_ASSERT(slist_el(list, 0) == &nodea);
	CU_ASSERT(slist_el(list, 1) == &nodec);

	/* Remove from tail.
	 *  [a,c] -> []
	 */
	list = remove_el(remove_el(list, &nodec), &nodea);
	CU_ASSERT(slist_len(list) == 0);
}

static const TestList TL_slist[] = {
	{ "join_slists", do_join_slists },
	{ NULL, NULL }
};

const TestSuite TS_slist = {
	"slist",
	NULL,
	NULL,
	TL_slist
};
