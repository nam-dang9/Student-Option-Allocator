#include <iostream>
#include "student.hpp"
#include <ctime>
#include <random>
#include <algorithm>

/*
DEF: Method to create a random int
PRE: Accepts an upper and lower bound
POST: Random int between the 2 bounds
RETURN: Integer
*/
int get_int(int lower, int upper) {
	static default_random_engine generator_int(clock());
	uniform_int_distribution <int> distribution_int(lower, upper);
	int random_num = distribution_int(generator_int);
	return random_num;
}
/*
DEF: Method to create a random double
PRE: Accepts an upper and lower bound
POST: Random double between the 2 bounds
RETURN: Double
*/
double get_double(double lower, double upper) {
	static default_random_engine generator_double(clock());
	uniform_real_distribution <double> distribution_double(lower, upper);
	double random_num = distribution_double(generator_double);
	return random_num;
}
/*
DEF: Method to get student priority
PRE: N/A
POST: Priority should be 1 or 2
RETURN: Integer
*/
int student::get_priority() const {
	return student_priority;
}
void make_list(vector<student>& list)
{
	int const PRIORITY_1 = 100;
	int const PRIORITY_2 = 25;
	for (int i = 0; i < PRIORITY_1; ++i) {
		list.push_back(student(1));
	}
	sort(list.begin(), list.end(), [](student a, student b) { return a.get_gpa() > b.get_gpa(); });
	for (int i = 0; i < PRIORITY_2; ++i) {
		list.push_back(student(2));
	}
	sort(list.begin() + PRIORITY_1, list.end(), [](student a, student b) { return a.get_gpa() > b.get_gpa(); });
	check_id(list);
}
/*
DEF: Method to check all IDs are unique
PRE: Valid student list
POST: All student ids are unique
RETURN: N/A
*/
void check_id(vector<student>& list)
{
	for (int i = 0; i < (int)list.size(); ++i) {
		for (int j = i + 1; j < (int)list.size(); ++j) {
			if (list[i].get_id() == list[j].get_id()) {
				if (list[j].get_priority() == 1) {
					list[j].set_id(get_int(10000000, 19999999));
				}
				else {
					list[j].set_id(get_int(20000000, 29999999));
				}
				check_id(list);
			} 
			else {
				break;
			}
		}
	}
}
/*
DEF: One param constructor that accepts student priority
PRE: Priority should be 1 or 2
POST: Student with priority 1 or 2
RETURN: Student
*/
student::student(int p) {
	if (p == 1) {
		id = get_int(10000000, 19999999);
	}
	else {
		id = get_int(20000000, 29999999);
	}
	gpa = get_double(50.0, 100.0);
	gpa = (int)(gpa * 10 + 0.5) / 10.0;
	student_priority = p;
	assign_priority();
}

student::student(int num, double grade, int p, char c[5]) : id(num), gpa(grade), student_priority(p)
{
	for (int i = 0; i < 5; ++i) {
		student_option_list[i] = c[i];
	}
}
/*
DEF: Method to get assign a list of options to students
PRE: N/A
POST: Random list of option
RETURN: N/A
*/
void student::assign_priority()
{
	vector<char> priority_array{ 'A', 'B', 'C', 'D', 'E' };
	int random_num = get_int(0, 4);
	student_option_list[0] = priority_array[random_num];
	priority_array.erase(priority_array.begin() + random_num);
	random_num = get_int(0, 3);
	student_option_list[1] = priority_array[random_num];
	priority_array.erase(priority_array.begin() + random_num);
	random_num = get_int(0, 2);
	student_option_list[2] = priority_array[random_num];
	priority_array.erase(priority_array.begin() + random_num);
	random_num = get_int(0, 1);
	student_option_list[3] = priority_array[random_num];
	priority_array.erase(priority_array.begin() + random_num);
	student_option_list[4] = priority_array[0];
}
/*
DEF: Method to get assign a student to an option based on GPA
PRE: Valid student list
POST: All options should be filled
RETURN: N/A
*/
void assign_option_list(vector<student>& list)
{
	int optionA = 0;
	int optionB = 0;
	int optionC = 0;
	int optionD = 0;
	int optionE = 0;
	int const MAX = 25;
	for (int i = 0; i < (int)list.size(); ++i) {
		for (int j = 0; j < 5; ++j) {
			if (list[i].student_option_list[j] == 'A' && optionA < MAX) {
				list[i].assigned_option = 'A';
				optionA++;
				break;
			}
			if (list[i].student_option_list[j] == 'B' && optionB < MAX) {
				list[i].assigned_option = 'B';
				optionB++;
				break;
			}
			if (list[i].student_option_list[j] == 'C' && optionC < MAX) {
				list[i].assigned_option = 'C';
				optionC++;
				break;
			}
			if (list[i].student_option_list[j] == 'D' && optionD < MAX) {
				list[i].assigned_option = 'D';
				optionD++;
				break;
			}
			if (list[i].student_option_list[j] == 'E' && optionE < MAX) {
				list[i].assigned_option = 'E';
				optionE++;
				break;
			}
		}
	}
}
/*
DEF: Method to set student id
PRE: Valid integer
POST: student id should be the same as num
RETURN: N/A
*/
void student::set_id(int num)
{
	id = num;
}

/*
DEF: Method to set student unhappiness
PRE: Valid integer
POST: student unhappiness should be the same as num
RETURN: N/A
*/
void student::set_unhappiness(int i)
{
	unhappiness = i;
}
/*
DEF: Method to set student option
PRE: Valid char
POST: student option should be the same as char
RETURN: N/A
*/
void student::set_assigned_option(char c)
{
	assigned_option = c;
}
/*
DEF: Method to get student option
PRE: N/A
POST: should return the option the student is enrolled in
RETURN: char
*/
char student::get_assigned_option() const
{
	return assigned_option;
}
/*
DEF: Method to get student option list
PRE: Valid int
POST: should return the option list of the student
RETURN: Return char
*/
char student::get_student_option_list(int i) const
{
	return student_option_list[i];
}
/*
DEF: Method to assign unhappiness to each student in a vector
PRE: Valid vector
POST: Unhappiness should be set based on student assigned option
RETURN: N/A
*/
void assign_unhappiness(vector<student>& list)
{
	for (int i = 0; i < (int)list.size(); ++i) {
		for (int j = 0; j < 5; ++j) {
			if (list[i].get_assigned_option() == list[i].get_student_option_list(j)) {
				list[i].set_unhappiness(j);
				break;
			}
		}
	}
}
/*
DEF: Method to reduce overall student unhappiness
PRE: Valid student list
POST: Total unhappiness is reduced
RETURN: N/A
*/
void resolve_unhappiness(vector<student>& list) {
	for (int i = 0; i < (int)list.size(); ++i) {
		for (int j = 0; j < (int)list.size(); ++j) {
			int num1 = 0;
			int num2 = 0;
			int total = list[i].get_unhappiness() + list[j].get_unhappiness();
			while (list[i].get_student_option_list(num1) != list[j].get_assigned_option()) {
				num1++;
			}
			while (list[j].get_student_option_list(num2) != list[i].get_assigned_option()) {
				num2++;
			}
			if (total > (num1 + num2 + 2) ) {
				char temp = list[i].assigned_option;
				list[i].set_assigned_option(list[j].assigned_option);
				list[j].set_assigned_option(temp);
			}
		}
	}
}
/*
DEF: Method to get student unhappiness
PRE: N/A
POST: student unhappiness
RETURN: Integer
*/
int student::get_unhappiness() const
{
	return unhappiness;
}
/*
DEF: Method to get student id
PRE: N/A
POST: student id
RETURN: Integer
*/
int student::get_id() const{
	return id;
}
/*
DEF: Method to get student gpa
PRE: N/A
POST: student gpa
RETURN: Double
*/
double student::get_gpa() const {
	return gpa;
}
ostream & operator<<(ostream &out, const student &s) {
	// TODO: insert return statement here
	out << s.id << " " << s.gpa << " " << s.student_option_list[0] << " " << s.student_option_list[1] << " " 
		<< s.student_option_list[2] << " " << s.student_option_list[3] << " " << s.student_option_list[4] 
		<< " " << s.student_priority;
	return out;
}
