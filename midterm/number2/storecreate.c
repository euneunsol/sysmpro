#include <stdio.h> 

struct store {
	int id;
    char name[20];
	char category;
	int data;
	int stock;
};


int main(int argc, char* argv[]) { 
	struct store rec;
	FILE *fp;
	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1; 
	}
	fp = fopen(argv[1], "w");
	printf("%-s %-13s %-6s %-4s %-3s\n", "id", "name", "category", "expired data", "stock"); 
	while (scanf("%d %s %s %d %d", &rec.id, rec.name, rec.category, rec.data, rec.stock)==5){ 
		fprintf(fp, "%d %s %s %d %d ", rec.id, rec.name, rec.category, rec.data, rec.stock);
	}
	fclose(fp);
	return 0;
}
