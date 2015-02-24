// my_test_tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stack>
#include <algorithm>
#include <vector>
#include <cassert>

template <typename data>
class tree
{
public:

	class tree_item
	{
	public:
		tree_item(const data _d = data(), tree_item *_p = 0, tree_item *_l = 0, tree_item *_r = 0) :d(_d), visit_count(0), p(_p), l(_l), r(_r)
		{
		}
		data d;

		unsigned visit_count;

		tree_item *p;
		tree_item *l;
		tree_item *r;
	};
public:
	typedef tree_item item_of_type;

	tree() :root(0)
	{
	}

	bool is_bst()
	{
		if (!root)
			return true;		
		return is_bst(root);
	}

	bool is_bst(tree_item *i)
	{
		if (i == &nul)
			return true; 
		bool r = true;

		if (i->l != &nul)
		{
			r = i->d > i->l->d && r;
			if (i->d <= i->l->d)
			{
				std::cout << "p:" << i->d << "l:" << i->l->d << "\n";
			}
		
		}

		if (i->r != &nul)
		{
			r = i->d < i->r->d && r;
			if (i->d >= i->r->d)
			{
				std::cout << "p:" << i->d << "r:" << i->r->d << "\n";
			}
		}

		if (i->l != &nul)
			r = is_bst(i->l) && r;
		if (i->r != &nul)
			r = is_bst(i->r) && r;

		return   r;
	}

	item_of_type *get(data d)
	{		
		item_of_type *i = root;
		assert(i);
		while (true)
		{
			if (i->d == d)
				return i;
			if (d < i->d)
			{
				if (i->l != &nul)
					i = i->l;
				else
					return i;
			}
			else
			{
				if (i->r != &nul)
					i = i->r;
				else
					return i;
			}
		}
		return i;
	}
	item_of_type *get_r(data d)
	{
		assert(root);
		return get_r( d, root ) ;
	}

	item_of_type *get_r(data d, item_of_type *i)
	{
		assert(i);		
		if (i->d == d)
			return i;
		if (d < i->d )
		{
			if (i->l != &nul)
				return get(d, i->l);
			else
				return i;
		}
		else
		{
			if (i->r != &nul)
				return get(d, i->r);
			else
				return i;
		}
	}

	void insert(item_of_type *item)
	{
		if (!root)
		{
			root = item;
			root->p = &nul;
			root->l = &nul;
			root->r = &nul;
		}
		return;
	}

	void insert(item_of_type *item, item_of_type *where, bool left)
	{
		assert(where);
		assert(item);

		if (left)	
			where->l = item;
		else
			where->r = item;
		item->p = where;
		item->l = &nul;
		item->r = &nul;
	}

	void insert(data where, data l, data r)
	{
		insert(new item_of_type(l), get(where), true);
		insert(new item_of_type(r), get(where), false);
	}

	void walk_r(std::vector<data> & result)
	{
		if (!root)
			return;

		walk_r(root->l, result );		
		result.push_back( root->d );
		walk_r(root->r, result);		
	}

	void walk_r(item_of_type *i, std::vector<data> & result)
	{
		if (!i)
			return;
		if (i->l != &nul)
			walk_r(i->l, result);
		result.push_back(i->d);
		if (i->r != &nul)
			walk_r(i->r, result);
	}

	void walk_mem(std::vector<data> & result)
	{
		if (!root)
			return;

		std::stack<item_of_type *> mem;

		item_of_type *i = root;

		while (i->l != 0)
		{			
			mem.push(i);
			i = i->l;
		}		
		//std::cout << mem.size() << '\n';
		while (!mem.empty())
		{
			i = mem.top();
			mem.pop();
			result.push_back(i->d);

			if (i->r != &nul)
			{				
				i = i->r;
				while (i->l != 0)
				{
					mem.push(i);
					i = i->l;
				}				
				//std::cout << mem.size()<<'\n';
			}			
		}
	}


	item_of_type *predecessor(data d) // предшественник
	{
		assert(false);
	}

	item_of_type *successor(data d)
	{
		item_of_type *i = get(d);
		assert(i);

		if ( i->r == &nul )
		{			
			if (i->p->l == i)
				return i->p;
			else
				while (i->p->r == i)
					i = i->p;
				return i->p;
		}

		if (i->r != &nul)
		{
			if (i->r->l == &nul)
			{
				return i->r;
			}
			else
			{
				i = i->r->l;
				while (i->l != &nul)
				{
					i = i->l;
				}
				return i;
			}
		}
		return 0;
	}

	item_of_type *min()
	{
		assert(root);
		item_of_type *i = root;
		while (i->l != &nul)
		{
			i = i->l;
		}
		return i; 
	}

	void walk( std::vector<data> & result )
	{		
		item_of_type *i = min();
		assert(i);
		while( i != &nul )
		{
			result.push_back(i->d);
			i = successor(i->d);
		}		
	}

	void count()
	{
		count(root);
	}

	int  count(item_of_type *i)
	{
		if (i == &nul)
			return 0;
		i->visit_count = count(i->l) + count(i->r) + 1;
		return i->visit_count;
	}

private:
	item_of_type *root;
	static item_of_type nul;
};

tree<long>::item_of_type tree<long>::nul;
typedef tree<long> long_tree;

void create_1(long_tree & t)
{
	t.insert(new long_tree::item_of_type(45));
	assert(t.is_bst());
	t.insert(45, 24, 76);
	assert(t.is_bst());
	t.insert(24, 14, 32);
	assert(t.is_bst());
	t.insert(14, 8, 20);
	assert(t.is_bst());
	t.insert(32, 27, 37);
	assert(t.is_bst());
	t.insert(76, 61, 87);
	assert(t.is_bst());
	t.insert(61, 56, 67);
	assert(t.is_bst());
	t.insert(87, 81, 94);	
	assert(t.is_bst());

	long_tree::item_of_type *i = t.get(16);
	assert(i);
	t.insert(new long_tree::item_of_type(16), i, true);
}

int _tmain(int argc, _TCHAR* argv[])
{
	long_tree t;

	assert(t.is_bst());

	std::vector<long> r1;	
	std::vector<long> r2;
	std::vector<long> r3;

	create_1(t);

	assert(t.is_bst());

	//t.count();
	
	t.walk_r(r1);	
	t.walk_mem(r2);
	t.walk(r3);

	std::for_each(r1.begin(), r1.end(), [](long i){std::cout << i << ";"; });
	std::cout << '\n';	
	std::for_each(r2.begin(), r2.end(), [](long i){std::cout << i << ";"; });
	std::cout << '\n';
	std::for_each(r3.begin(), r3.end(), [](long i){std::cout << i << ";"; });
	std::cout << '\n';

	assert(r1 == r2);
	assert(r3 == r2);
	
	return 0;
}

