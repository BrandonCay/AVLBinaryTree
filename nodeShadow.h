#pragma once
#ifndef tnodeShadow_H
#define tnodeShadow_H
///////////////////////////////////////////////////////////////////////
/*#include "node.h"
#include <iostream>
using namespace std;
class tnodeShadow
{
public:
	string nodeValueStr;	// formatted node value
	int level, column;
	tnodeShadow* left, * right;

	tnodeShadow() { }
};
/////////////////////////////////////////////////////////////
tnodeShadow* buildShadowTree(node* t, int level, int& column)
{
	// pointer to new shadow tree node
	tnodeShadow* newNode = NULL;
	// text and ostr used to perform format conversion
	char text[80];
	ostream ostr(text, 80);

	if (t != NULL)
	{
		// create the new shadow tree node
		newNode = new tnodeShadow;

		// allocate node for left child at next level in tree; attach node
		tnodeShadow* newLeft = buildShadowTree(t->left, level + 1, column);
		newNode->left = newLeft;

		// initialize data members of the new node
		ostr << t->item << ends;	// format conversion
		newNode->nodeValueStr = text;
		newNode->level = level;
		newNode->column = column;

		// update column to next cell in the table
		column++;

		// allocate node for right child at next level in tree; attach node
		tnodeShadow* newRight = buildShadowTree(t->right, level + 1, column);
		newNode->right = newRight;
	}
	return newNode;
}*/
#endif