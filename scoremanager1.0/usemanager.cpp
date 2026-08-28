#include<cctype>
#include"scoremanager2.h"

int main()
{
	Scoremanager s1; 
	{
		cout << "Welcome to Student Score Management System!\n";
		while (true)
		{
			{
				char choice;
				cout << "Which feature do you want to use?\n"
					<< "Tap <A> to add students'score\n"
					<< "Tap <B> to delete any fault score\n"
					<< "Tap <C> to search each student's score\n"
					<< "Tap <D> to sort the list by total score descending\n"
					<< "Tap <E> to present group statistics\n"
					<< "Tap <Q> to quit\n";
				cout << "Please give your choice: ";
				cin >> choice;
				choice = (char)toupper(choice);
				if (!(choice >= 'A' && choice <= 'D' || choice == 'Q'))
				{
					cout << "Invalid input! Please try again!\n";
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				else if (choice == 'A')
				{
					if (s1.isfull())
					{
						cout << "The system is overloaded! Please try other features!\n";
						continue;
					}
					int num, current = s1.Howmany();
					while (true)
					{
						cout << "Current number of students in the list: " << current << endl;
						cout << "How many student's score do you want to input(no more than 50 students in total)? ";
						cin >> num;
						if (num + current > Scoremanager::NODE_LIMIT)
						{
							cout << "Invalid input! Please try again!\n";
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							break;
						}
					}
					for (int i = current; i < num + current; i++)
					{
						Items* student = new Items;
						cout << "Please enter the information of student #" << i + 1 << ": \n";
						cin >> student;
						s1.isAdded = s1.add(*student);
						if (!s1.isAdded)
						{
							cout << "Fail to input! Please try again!\n";
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							continue;
						}
					}
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cout << "\nYou have finished adding!\n";
					cout << endl;
					if (s1.giveTotal())
						cout << "Calculate total score of each student successfully!\n";
					else
						cout << "Fail to calculate total score of each student! Please try again later!\n";
					continue;
				}
				else if (choice == 'B')
				{
					while (true)
					{
						std::string id;
						cout << "Please enter targeted student's ID: ";
						getline(cin, id);
						if (s1.takeOut(s1.search(id)))
						{
							char ch;
							cout << "Delete targeted score information succussfully!\n"
								<< "Tap any key to continue, or tap <Q> to quit deleting!\n";
							cin >> ch;
							ch = (char)toupper(ch);
							if (ch == 'Q')
							{
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								break;
							}
							else
							{
								cout << "Entering another delete process!\n";
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								continue;
							}
						}
						else
						{
							char oi;
							cout << "Fail to delete the targeted score information! Please try again!\n"
								<< "Tap any key to continue, or tap <Q> to quit deleting!\n";
							cin >> oi;
							oi = (char)toupper(oi);
							if (oi == 'Q')
							{
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								break;
							}
							else
							{
								cout << "Entering another delete process!\n";
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								continue;
							}
						}
					}
					cout << "\nYou have finished deleting!\n";
					cout << endl;
					continue;
				}
				else if (choice == 'C')
				{
					while (true)
					{
						std::string id;
						cout << "Please enter targeted student's ID: ";
						getline(cin, id);
						cout << s1.search(id);
						cout << "Present the targeted score information successfully!\n";
						char ch;
						cout << "Tap any key to continue, or tap <Q> to quit searching!\n";
						cin >> ch;
						ch = (char)toupper(ch);
						if (ch == 'Q')
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							break;
						}
						else
						{
							cout << "Entering another search process!\n";
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							continue;
						}
					}
					cout << "\nYou have finished searching!\n";
					cout << endl;
					continue;
				}
				else if (choice == 'D')
				{
					// Sort the list by total score in descending order, assign ranks and display
					if (s1.isempty())
					{
						cout << "No student information in the system! Please add records first!\n";
						continue;
					}
					if (s1.sortByTotal())
						cout << "Sort completed and ranked. Presented sorted list above." << endl;
					else
						cout << "Fail to sort the list! Please try again later!\n";
					continue;
				}
				else if (choice == 'E')
				{
					if (!(s1.showStatistics()))
					{
						cout << "Fail to present the group statistics!\n";
						cout << "Please check your input!\n";
						continue;
					}
					else
					{
						cout << "\nThe group statistics are presented successfully!\n";
						cout << s1.Howmany() << " students's score information in total!\n";
						cout << endl;
						continue;
					}
				}
				else if (choice == 'Q')
				{
					cout << "The process has been ended!\n";
					cout << "See you next time!\n";
					break;
				}
			}
		}
	}
	return 0;
}