// FILE: bag6.cpp
// -------------------------------------------------------------------------
// This is a partial implementation of the bag template class from Section
// 10.5 of "Data Structures and Other Objects Using C++". The parts marked
// with ***STUDENT WORK*** are left as a project for data structures
// students.
// -------------------------------------------------------------------------
// TEMPLATE CLASS IMPLEMENTED: bag<Item> (see bag6.h for documentation)
// INVARIANT of the ADT:
//   root_ptr is the root pointer of a binary search tree that contains the
//   bag's items.

#include <cassert>
#include <cstdlib>
#include "bag6.h"
#include "bintree.h"

namespace main_savitch_10
{
    template <class Item>
	void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed)
	{
		if (root_ptr->right() == NULL)
		{
			removed = root_ptr->data();
			binary_tree_node<Item>* old_root_ptr = root_ptr;
			root_ptr = root_ptr->left();
			delete old_root_ptr;
			old_root_ptr = NULL;
		}
		else
			bst_remove_max(root_ptr->right(), removed);
	}

    template <class Item>
	bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target)
	// Precondition: root_ptr is a root pointer of a binary search tree 
	// or may be NULL for an empty tree).
	// Postcondition: If target was in the tree, then one copy of target
	// has been removed, and root_ptr now points to the root of the new 
	// (smaller) binary search tree. In this case the function returns true.
	// If target was not in the tree, then the tree is unchanged (and the
	// function returns false).
	{
	    binary_tree_node<Item> *oldroot_ptr;
	    
	    if (root_ptr == NULL)
	    {   // Empty tree
		return false;
	    }

	    if (target < root_ptr->data( ))
	    {   // Continue looking in the left subtree
		// Note: Any change made to root_ptr->left by this recursive
		// call will change the actual left pointer (because the return
		// value from the left() member function is a reference to the
		// actual left pointer.
		return bst_remove(root_ptr->left( ), target);
	    }

	    if (target > root_ptr->data( ))
	    {   // Continue looking in the right subtree
		// Note: Any change made to root_ptr->right by this recursive
		// call will change the actual right pointer (because the return
		// value from the right() member function is a reference to the
		// actual right pointer.
		return bst_remove(root_ptr->right( ), target);
	    }
	    
	    if (root_ptr->left( ) == NULL)
	    {   // Target was found and there is no left subtree, so we can
		// remove this node, making the right child be the new root.
		oldroot_ptr = root_ptr;
		root_ptr = root_ptr->right( );
		delete oldroot_ptr;
		return true;
	    }
	    
	    // If code reaches this point, then we must remove the target from
	    // the current node. We'll actually replace this target with the
	    // maximum item in our left subtree.
	    // Note: Any change made to root_ptr->left by bst_remove_max
	    // will change the actual left pointer (because the return
	    // value from the left() member function is a reference to the
	    // actual left pointer.
	    bst_remove_max(root_ptr->left( ), root_ptr->data( ));
	    return true;
	}

    template <class Item>
	typename bag<Item>::size_type bst_remove_all
	(binary_tree_node<Item>*& root_ptr, const Item& target)
	{
		if (root_ptr == NULL)
			return 0;
		if (target < root_ptr->data())
			bst_remove_all(root_ptr->left(), target);
		if (target > root_ptr->data())
			bst_remove_all(root_ptr->right(), target);
		if (root_ptr->left() == NULL)
		{
			binary_tree_node<Item>* old_root_ptr = root_ptr;
			root_ptr = root_ptr->right();
			delete old_root_ptr;
			old_root_ptr = NULL;
			return 1;
		}
		bst_remove_max(root_ptr->left(), root_ptr->data());
		return 1 + bst_remove_all(root_ptr, target);

	    binary_tree_node<Item> *oldroot_ptr;
	    
	    if (root_ptr == NULL)
	    {   // Empty tree
			return false;
	    }

	    if (target < root_ptr->data( ))
	    {   // Continue looking in the left subtree
			return bst_remove(root_ptr->left(), target);
	    }

	    if (target > root_ptr->data( ))
	    {   // Continue looking in the right subtree
			return bst_remove(root_ptr->right(), target);
	    }
	    
	    if (root_ptr->left( ) == NULL)
	    {   // Target was found and there is no left subtree, so we can
		// remove this node, making the right child be the new root.
		oldroot_ptr = root_ptr;
		root_ptr = root_ptr->right( );
		delete oldroot_ptr;
		return 1;
	    }
	    
		bst_remove_max(root_ptr->left(), root_ptr->data());
		return true;

	}

    template <class Item>
	bag<Item>::bag(const bag<Item>& source)
	// Library facilities used: bintree.h
	{
	    root_ptr = tree_copy(source.root_ptr);
	}

    template <class Item>
	bag<Item>::~bag( )
	// Header file used: bintree.h
	{
	    tree_clear(root_ptr);
	}

    template <class Item>
	typename bag<Item>::size_type bag<Item>::size( ) const
	// Header file used: bintree.h
	{
	    return tree_size(root_ptr);
	}

    template <class Item>
	void bag<Item>::insert(const Item& entry)
		// Header file used: bintree.h
	{
		binary_tree_node<Item>* cursor;

		bool done = false;

		if (root_ptr == NULL)
		{   // Add the first node of the binary search tree:
			root_ptr = new binary_tree_node<Item>(entry);
			done = true;
		}

		else
		{   // Move down the tree and add a new leaf:
			cursor = root_ptr;
			while (!done) {
				if (cursor->data() >= entry) {
					if (cursor->left() == NULL) {
						cursor->left() = new binary_tree_node<Item>(entry);
						done = true;
					}
					else cursor = cursor->left();
				}
				else {
					if (cursor->right() == NULL) {
						cursor->right() = new binary_tree_node<Item>(entry);
						done = true;
					}
					else cursor = cursor->right();
				}
			}
		}
	}

    template <class Item>
	typename bag<Item>::size_type bag<Item>::count(const Item& target) const
	{
	    size_type answer = 0;
	    binary_tree_node<Item> *cursor;

	    cursor = root_ptr;
		while (cursor != NULL)
		{
			if (cursor->data() >= target)
			{
				if (cursor->data() == target)
					count++;
				cursor = cursor->left();
			}
			else
			{
				cursor = cursor->right();
			}
		}

	    return count;
	}

    template <class Item>
	typename bag<Item>::size_type bag<Item>::erase(const Item& target)
	{
	    return bst_remove_all(root_ptr, target);
	}

    template <class Item>
	bool bag<Item>::erase_one(const Item& target)
	{
	    return bst_remove(root_ptr, target);
	}

    template <class Item>
	void bag<Item>::operator =(const bag<Item>& source)
        // Header file used: bintree.h
        {
	    if (root_ptr == source.root_ptr)
	        return;
	    tree_clear(root_ptr);
	    root_ptr = tree_copy(source.root_ptr);
	}

    template <class Item>
	void bag<Item>::operator +=(const bag<Item>& addend)
        {
	    if (root_ptr == addend.root_ptr)
	    {
		bag<Item> copy = addend;
		insert_all(copy.root_ptr);
	    }
	    else
	        insert_all(addend.root_ptr);
	}

    template <class Item>
	bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2)
	{
	    bag<Item> answer = b1;
	    answer += b2;
	    return answer;
	}

    template <class Item>
	void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr)
        // Precondition: addroot_ptr is the root pointer of a binary search tree that
        // is separate for the binary search tree of the bag that activated this
        // method.
        // Postcondition: All the items from the addroot_ptr's binary search tree
        // have been added to the binary search tree of the bag that activated this
        // method.
	{
	    if (addroot_ptr != NULL)
	    {
		insert(addroot_ptr->data( ));
		insert_all(addroot_ptr->left( ));
		insert_all(addroot_ptr->right( ));
	    }
	}
}
