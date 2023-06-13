#ifndef PROJECTS_TABLE_H
#define PROJECTS_TABLE_H



typedef struct table * Table;

Table initTable(int nr_top, int nr_side, int init_records);
void destroyTable(Table t);
int addSideHeader(Table t, char* header);
int addTopHeader(Table t, char* header);
int addElem(Table t, char** elem, int size_elem);
Table proj(Table t, int* cols, int n);
void printTable(Table t);
int getNrRecords(Table table);
void tableToCSV(Table table, char delim, char* filepath);

#endif