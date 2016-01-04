#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

string generate_space(int c) {
	string s = "";
	for (int i = 1; i <= c; ++ i) {
		s += " ";
	}
	return s;
}

string generate_numbers(void) {
	string s = "", s1 = "", s2 = "";
	stringstream ss;
	int i;
	int d1, d2;
	int r = rand() % 2;
	if (r) {
		i = rand() % 800 - rand() % 400;
		ss << i;
		ss >> s;
	}
	else {
		d1 = rand() % 800 - rand() % 400;
		d2 = rand() % 8000008;
		ss << d1;
		ss >> s1;
		ss.clear();
		ss << d2;
		ss >> s2;
		s = s1 + "." + s2;
	}
	return s;
}

string generate_name(int c) {
	string s = "";
	for (int i = 1; i <= c; ++ i) {
		int r = rand() % 3;
		switch (r) {
			case 0:
				s += rand() % 26 + 'a';
				break;
			case 1:
				s += rand() % 26 + 'A';
				break;
			case 2:
				s += rand() % 10 + '0';
		}
	}
	return s;
}

int main(void) {
	srand((unsigned int)time(NULL));

	ofstream out("output.txt");

	vector<string> variable_list;

	const string double_pre = "double",
			int_pre = "int",
			print_pre = "print";

	//int c = rand() % 100 + 50;
	int c = 100;
	for (int i = 1; i <= c; ++ i) {
		string temp;
		int r = rand() % 3;
		switch (r) {
			case 0:
				temp = double_pre;
				break;
			case 1:
				temp = int_pre;
				break;
			case 2:
				temp = print_pre;
				break;
		}
		int rc = rand() % 13 + 1;
		string t = temp;
		vector<string>::iterator result;
		do {
			t += generate_name(rc);
			result = find(variable_list.begin(), variable_list.end(), t);
		} while (result != variable_list.end());
		variable_list.push_back(t);
		//cerr << t << endl;
	}
	int cc = 0;
	while (cc <= c) {
		int r = rand() % 2, cs = rand() % 10, en = rand() % 8 + 2;
		switch (r) {
			case 0:
				out << generate_space(cs) << int_pre << " ";
				break;
			case 1:
				out << generate_space(cs) << double_pre << " ";
				break;
		}
		int bound = ((en + cc <= c) ? en + cc - 1 : c - 1);
		for (int j = cc; j < bound; ++ j) {
			out << variable_list.at(j) << "," << generate_space(rand() % 3);
		}
		out << variable_list.at(bound) << ";" << endl;
		cc += en;
	}

	for (int i = 0; i < rand() % (c - 80) + 80; ++ i) {
		out << generate_space(rand() % 2) << variable_list.at(i) << generate_space(rand() % 5)
			<< "=" << generate_space(rand() % 5) << generate_numbers() << ";" << endl;
	}

	for (int i = 1; i < rand() % 20000; ++ i) {
		string assignment = "(";
		bool is_assigned = false;
		if (rand() % 25 != 1) {

			// 制造随机的赋值
			for (int j = 1; j < rand() % 5; ++ j) {
				int range_left = rand() % (c - 10);
				int range_right = rand() % 5 + range_left;
				for (int k = range_left; k <= range_right; ++ k) {
					assignment += generate_space(rand() % 2) + variable_list.at(k) + generate_space(rand() % 2)
					              + "=" + generate_space(rand() % 2);
				}
			}
			assignment += generate_numbers() + ")";

			string a = variable_list.at(rand() % (c - 1));
			string b;
			bool is_a_assigned = false;
			if (rand() % 10 != 1) {
				is_a_assigned = true;
				out << generate_space(rand() % 3) << a << generate_space(rand() % 3) << "=";
				if (rand() % 6 == 1) {
					b = generate_numbers();
				}
				else {
					do {
						b = variable_list.at(rand() % (c - 1));
					} while (assignment.find(b) != -1);
				}
				out << generate_space(rand() % 3) << b;
			}
			else {
				out << generate_space(rand() % 3) << a << generate_space(rand() % 3);
			}

			for (int j = 2; j < rand() % 10 + 2; ++j) {
				if (rand() % 6 == 1) {
					b = generate_numbers();
				}
				else {
					do {
						b = variable_list.at(rand() % (c - 1));
					} while (b == a);
				}
				char opt;
				switch (rand() % 3) {
					case 0:
						opt = '+';
						break;
					case 1:
						opt = '-';
						break;
					case 2:
						opt = '*';
				}
				switch (rand() % 7) {
					case 0:
						if (!is_assigned && j != 1) {
							out << opt << generate_space(rand() % 2) << assignment;
							is_assigned = true;
						}
						break;
					case 1:
					case 2:
					case 3:
						out << opt << generate_space(rand() % 2) << b;
						break;
					case 4:
						if (rand() % 10 == 1) {
							out << "/" << generate_space(rand() % 2) << b;
						}
						break;
					case 5:
						if (opt == '+' || opt == '-') {
							out << opt << generate_space(rand() % 2) << "(" << generate_space(rand() % 2)
							<< "+" << generate_space(rand() % 2) << b << generate_space(rand() % 2) << ")";
						}
						else {
							out << opt << generate_space(rand() % 2) << "+" << generate_space(rand() % 2) << b;
						}
						break;
					case 6:
						if (opt == '+' || opt == '-') {
							out << opt << generate_space(rand() % 2) << "(" << generate_space(rand() % 2)
							<< "-" << generate_space(rand() % 2) << b << generate_space(rand() % 2) << ")";
						}
						else {
							out << opt << generate_space(rand() % 2) << "-" << generate_space(rand() % 2) << b;
						}
						break;
				}
			}
			out << ";" << endl;
			if (is_a_assigned) {
				if (rand() % 3 == 1) {
					out << generate_space(rand() % 3) << print_pre << generate_space(rand() % 3) << "(" << a
						<< generate_space(rand() % 3) << ")" << generate_space(rand() % 3) << ";"<< endl;
				}
			}
		}
		else {
			out << generate_space(rand() % 20) << generate_numbers() << generate_space(rand() % 20) << ";" << endl;
		}
	}

	for (int i = 1; i < rand() % 8000; ++ i) {
		int r = rand() % 2;
		out << generate_space(rand() % 5) << "print" << generate_space(rand() % 3) << "(" << generate_space(rand() % 3);
		if (r) {
			out << variable_list.at(rand() % (c - 1));
		}
		else {
			out << generate_numbers();
		}
		out << generate_space(rand() % 3) << ");" << endl;
	}
	out.close();
	return 0;
}