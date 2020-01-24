#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class student {
private:
	int id;
	double gpa;
	int student_priority;
	char student_option_list [5];
	char assigned_option;
	int unhappiness;
	
public:
	student() = default;
	student(int p);
	student(int num, double grade, int p, char c[5]);
	void assign_priority();
	void set_id(int num);
	void set_unhappiness(int i);
	void set_assigned_option(char c);
	int get_id() const;
	double get_gpa() const;
	int get_priority() const;
	char get_assigned_option() const;
	char get_student_option_list(int i) const;
	int get_unhappiness() const;
	friend void assign_option_list(vector<student>& list);
	friend void make_list(vector<student>& list);
	friend void check_id(vector<student>& list);
	friend void resolve_unhappiness(vector<student>& list);
	friend void assign_unhappiness(vector<student>& list);
	friend ostream& operator<<(ostream& out, const student& s);
};