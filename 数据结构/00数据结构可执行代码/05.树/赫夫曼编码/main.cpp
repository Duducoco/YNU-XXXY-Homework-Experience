#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(void)
{
	htTree *codeTree = buildTree("I love FishC.com!");
	hlTable *codeTable = buildTable(codeTree);
	encode(codeTable,"I love FishC.com!");
	decode(codeTree,"0011111000111");
	return 0;
}
