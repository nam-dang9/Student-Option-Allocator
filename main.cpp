#include <iostream>
#include "student.hpp"
#include <vector>
#include <fstream>
#include <algorithm>
#include <istream>
using namespace std;

/*
DEF: Method to to open a file
PRE: Accepts an vector of students and the name of a file
POST: Assigns the values in the file to a vector of students
RETURN: N/A
*/
void read_file(vector<student> &list, string file) {
	ifstream fin{ file };
	if (!fin) {
		cout << "Cant open " << endl;
	}
	int id; 
	double gpa;
	char c[5];
	int p;

	while (fin >> id >> gpa >> c[0] >> c[1] >> c[2] >> c[3] >> c[4] >> p) {
		list.push_back(student(id, gpa, p, c));
	}
	fin.close();
}
/*
DEF: Method to to create a student file
PRE: Accepts an vector of students
POST: Assigns the values of the students and prints them in a file
RETURN: N/A
*/
void create_student_file(vector<student>& student_list) {
	ofstream output_file;
	output_file.open("student.txt");
	for (int i = 0; i < (int)student_list.size(); ++i) {
		output_file << student_list[i].get_id() << " " << student_list[i].get_gpa() << " "
			<< student_list[i].get_student_option_list(0) << " " << student_list[i].get_student_option_list(1) << " "
			<< student_list[i].get_student_option_list(2) << " " << student_list[i].get_student_option_list(3) << " "
			<< student_list[i].get_student_option_list(4) << " " << student_list[i].get_priority() << "\r\n";
	}
	output_file.close();
}
/*
DEF: Method to to create a file
PRE: Accepts an vector of students and the name of the file
POST: Assigns the values of the students and prints them in a file
RETURN: N/A
*/
void create_file(vector<student> student_file, string file) {
	ofstream output_gpa;
	output_gpa.open(file);
	int total = 0;
	for (int i = 0; i < (int)student_file.size(); ++i) {
		output_gpa << student_file[i].get_id() << " " << student_file[i].get_assigned_option() << "\r\n";
		total += student_file[i].get_unhappiness();
	}
	output_gpa << total;
	output_gpa.close();
}
int main() 
{
	vector<student> student_list;
	make_list(student_list);
	assign_option_list(student_list);
	assign_unhappiness(student_list);

	create_student_file(student_list);

	vector<student> student_file;
	read_file(student_file, "student.txt");
	assign_option_list(student_file);
	assign_unhappiness(student_file);

	create_file(student_file, "gpa.txt");

	resolve_unhappiness(student_file);
	assign_unhappiness(student_file);

	create_file(student_file, "maxhappy.txt");

	return 0;
}