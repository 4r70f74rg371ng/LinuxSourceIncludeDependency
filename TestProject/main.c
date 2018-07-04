#include <stdio.h>
#include <stdlib.h>
#include "PathGraph.h"

int main(int argc, char *argv[]) {
	PathGraph graph;
	
	InitGraph(&graph);
	
	InsertLink(&graph, "C:\\Users\\user\\Desktop\\IncludeDependency\\TestProject", "main.c", "stdio.h", 1, 0);
	InsertLink(&graph, "C:\\Users\\user\\Desktop\\IncludeDependency\\TestProject\\", "PathGraph.c", "PathGraph.h", 0, 0);
	InsertLink(&graph, "C:\\Users\\user\\Desktop\\IncludeDependency\\TestProject\\", "PathGraph.h", "CustomableSimpleLinkedList.h", 0, 0);
	InsertLink(&graph, "C:\\Users\\user\\Desktop\\IncludeDependency\\TestProject\\", "CustomableSimpleLinkedList.c", "CustomableSimpleLinkedList.h", 0, 0);
	
	WriteDotFileGraph(&graph, "test.dot");
	
	CleanupGraph(&graph);
	
	return 0;
}
