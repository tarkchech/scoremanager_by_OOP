#pragma once
#ifndef SCOREMANAGER1_H_
#define SCOREMANAGER1_H_
#include<vector>
#include<iostream>
#include<string>

struct Students
{
	std::string name;
	std::string code;
	char sex;
	double Calculas;
	double English;
	double Programming;
	double total=0.0;
	int rank;
};

typedef struct Students Items;

class Scoremanager
{
private:
	struct Node
	{
		Node* prev;
		Items item;
		Node* next;
	};
	Node* front;
	Node* end;
	std::vector<double> avgAll = { 0.0,0.0,0.0,0.0 };
	static int num_students;
public:
	enum { NODE_LIMIT = 50 };
	bool isAdded;
	static bool isSorted;
	Scoremanager();
	~Scoremanager();
	int Howmany() { return num_students; }
	bool isfull() { return num_students == NODE_LIMIT; }
	bool isempty() { return num_students == 0; }
	bool add(Items& it);
	bool takeOut(Items* it);
	Items* search(std::string codeinput) const;
	bool avgCal();
	bool giveRank();
	bool giveTotal();
	bool sortByTotal();
	Node* merge(Node* n1,Node* n2);
	Node* mergeSort(Node* head);
	bool showStatistics();
	friend std::ostream& operator<<(std::ostream& os,const Items* n);
	friend std::istream& operator>>(std::istream& is,Items* n);
};

#endif