#pragma once
#ifndef SCOREMANAGER2_H_
#define SCOREMANAGER2_H_
#include"scoremanager1.h"

using std::cout;
using std::cin;
using std::endl;

Scoremanager::Scoremanager()
{
	num_students = 0;
	isAdded = false;
	isSorted = false;
	Node* santinel = new Node; // use sentinel node to avoid tackling edge case with tedious code 
	santinel->prev = nullptr;
	santinel->item = { "no name"," ",'\0',0.0,0.0,0.0,0.0,0};
	santinel->next = nullptr;
	front = end = santinel; // initializing front and end with santinel
}

Scoremanager::~Scoremanager()
{
	while (front != nullptr)
	{
		Node* temp = front;
		front = front->next;
		delete temp;
	}
}

bool Scoremanager::add(Items& it)
{
	if (isfull())
		return false;
	Node* newStudent = new Node;
	newStudent->prev = end;
	end->next = newStudent;
	newStudent->item = it;
	newStudent->next = nullptr;
	end = newStudent;
	num_students++;
	return true;
}

bool Scoremanager::takeOut(Items* it)
{
	if (isempty()||it==nullptr)
		return false;
	Node* temp = front->next;
	while (temp != nullptr)
	{
		if (temp->item.code == it->code)
			break;
		temp = temp->next;
	}
	if (temp == nullptr)
		return false;
	if (temp->next == nullptr) // whether temp is pointing at the "end" node
	{
		temp->prev->next = nullptr;
		end = temp->prev;
	}
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	num_students--;
	delete temp;
	return true;
}

Items* Scoremanager::search(std::string codeinput) const
{
	Node* temp = front;
	while (temp != nullptr)
	{
		if (temp->item.code == codeinput)
			break;
		temp = temp->next;
	}
	if (temp == nullptr)
	{
		cout << "Fail to locate the targeted student!\n";
		return nullptr;
	}
	return &(temp->item);
}

bool Scoremanager::giveRank()
{
	if (isempty() || !isSorted)
		return false;
	Node* temp = front->next;
	int ranking = 1;
	while (temp != nullptr)
	{
		temp->item.rank = ranking;
		ranking++;
		temp = temp->next;
	}
	return true;
}

bool Scoremanager::giveTotal()
{
	if (isempty())
		return false;
	Node* temp = front->next;
	while (temp != nullptr)
	{
		temp->item.total = temp->item.Calculas + temp->item.English + temp->item.Programming;
		temp = temp->next;
	}
	return true;
}

bool Scoremanager::avgCal()
{
	if (num_students <= 0)
		return false;
	Node* temp = front->next;
	while (temp != nullptr)
	{
		avgAll[0] += temp->item.Calculas;
		avgAll[1] += temp->item.English;
		avgAll[2] += temp->item.Programming;
		avgAll[3] += temp->item.total;
		temp = temp->next;
	}
	for (int i = 0; i < 4; i++)
		avgAll[i] /= num_students;
	return true;
}

// Merge two sorted lists (sorted by item.total descending) and return new head
Scoremanager::Node* Scoremanager::merge(Node* n1, Node* n2)
{
	if (n1 == nullptr) return n2;
	if (n2 == nullptr) return n1;

	// dummy head to simplify merging
	Node dummy;
	Node* tail = &dummy;
	dummy.next = nullptr;
	while (n1 != nullptr && n2 != nullptr)
	{
		if (n1->item.total >= n2->item.total)
		{
			tail->next = n1;
			n1->prev = tail == &dummy ? nullptr : tail;
			n1 = n1->next;
			tail = tail->next;
			tail->next = nullptr; // detach
		}
		else
		{
			tail->next = n2;
			n2->prev = tail == &dummy ? nullptr : tail;
			n2 = n2->next;
			tail = tail->next;
			tail->next = nullptr; // detach
		}
	}

	// attach remaining
	Node* rest = (n1 != nullptr) ? n1 : n2;
	while (rest != nullptr)
	{
		tail->next = rest;
		rest->prev = tail == &dummy ? nullptr : tail;
		tail = tail->next;
		rest = rest->next;
		tail->next = nullptr;
	}

	// result head
	Node* result = dummy.next;
	if (result != nullptr)
		result->prev = nullptr;
	return result;
}

// Top-down merge sort for linked list, returns new head (sorted by item.total descending)
Scoremanager::Node* Scoremanager::mergeSort(Node* head)
{
	if (head == nullptr)
		return nullptr;

	// If caller passed the sentinel (front), sort the real list and reattach to sentinel
	if (head == front)
	{
		Node* dataHead = front->next;
		Node* sortedHead = mergeSort(dataHead); // sort real nodes
		front->next = sortedHead;
		if (sortedHead != nullptr)
			sortedHead->prev = front;
		else
			front->next = nullptr;

		// update end to last node (or sentinel if empty)
		Node* tmp = front;
		while (tmp->next != nullptr)
			tmp = tmp->next;
		end = tmp;
		return front;
	}

	// base case for sublist (single node)
	if (head->next == nullptr)
		return head;

	// split list into two halves
	Node* slow = head;
	Node* fast = head->next;
	while (fast != nullptr && fast->next != nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	Node* mid = slow->next;
	slow->next = nullptr;
	if (mid != nullptr)
		mid->prev = nullptr;

	Node* left = mergeSort(head);
	Node* right = mergeSort(mid);
	return merge(left, right);
}


// Public helper to sort the whole list by total score (descending), compute ranks and print list
bool Scoremanager::sortByTotal()
{
	if (isempty())
		return false;
	// ensure total scores are up-to-date
	if (!giveTotal())
		return false;

	// perform merge sort on the sentinel node so mergeSort handles reattaching
	mergeSort(front);
	isSorted = true;

	// assign ranks based on current order
	giveRank();

	// print the sorted list
	Node* temp = front->next;
	while (temp != nullptr)
	{
		cout << &(temp->item) << endl;
		temp = temp->next;
	}
	return true;
}

bool Scoremanager::showStatistics()
{
	if (isempty() || avgAll.empty())
		return false;
	cout << "The average score of Calculus is: " << avgAll[0] << endl;
	cout << "The average score of English is : " << avgAll[1] << endl;
	cout << "The average score of Programming is : " << avgAll[2] << endl;
	cout << "The average score of all subject in total is : " << avgAll[3] << endl;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Items* it)
{
	if (it == nullptr)
	{
		os << "Fail to identify the object!\n" << endl;
		return os;
	}
	os << "Student's name: " << it->name << endl;
	os << "Student ID: " << it->code << endl;
	if (it->sex == 'f')
		os << "Gender: Female" << endl;
	else if (it->sex == 'm')
		os << "Gender: Male" << endl;
	else
		os << "Gender: INVALID" << endl;
	os << "Calculus score: " << it->Calculas << endl;
	os << "English score: " << it->English << endl;
	os << "Programming score: " << it->Programming << endl;
	os << "In total: " << it->total << endl;
	if (Scoremanager::isSorted)
		os << "Rank: " << it->rank << endl;
	else
		os << "Haven't sort the list yet! Fail to show rank!\n";
	return os;
}

std::istream& operator>>(std::istream& is, Items* it)
{
	cout << "Please enter the name of student: ";
	getline(is, it->name);
	cout << "Please enter student's ID: ";
	std::getline(is, it->code);
	cout << "Please enter student's gender(tap <M> or <F> to input): ";
	is >> it->sex;
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Student's Calculas score: ";
	is >> it->Calculas;
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Student's English score: ";
	is >> it->English;
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Student's Programming score: ";
	is >> it->Programming;
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return is;
}

#endif