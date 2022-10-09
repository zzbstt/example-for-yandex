#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Person {
public:
  Person(const string& namebirth, const string &surnamebirth, int year) {
        names[year] = namebirth;
        surnames[year] = surnamebirth;
        birthyear = year;
  }
  void ChangeFirstName(int year, const string& first_name) {
    // добавить факт изменения имени на first_name в год year
        if (year >= birthyear) {
            names[year] = first_name;
        }
  }
  void ChangeLastName(int year, const string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
        if (year >= birthyear) {
            surnames[year] = last_name;
        }
  }
  string GetFullName(int year) const {
    // получить имя и фамилию по состоянию на конец года year
        if (year < birthyear) return "No person";
        int max1 = 0, f1 = 0;
        int max2 = 0, f2 = 0;
        string name, surname;
        for (auto help : names) {
            if (help.first <= year && help.first >= max1) {
                max1 = help.first;
                name = help.second;
                f1 = 1;
            }
        }

        for (auto help : surnames) {
            if (help.first <= year && help.first >= max2) {
                max2 = help.first;
                surname = help.second;
                f2 = 1;
            }
        }
        if (f1 == 0 && f2 == 0) {
            return "Incognito";
        } else if (f1 == 1 && f2 == 0) {
            return name + " with unknown last name";
        } else if (f1 == 1 && f2 == 1) {
            return name + " " + surname;
        } else if (f1 == 0 && f2 == 1) {
            return surname + " with unknown first name";
        }
  }

   string GetFullNameWithHistory(int year) const{
    // получить имя и фамилию по состоянию на конец года year
        if (year < birthyear) return "No person";
        int max1 = 0, f1 = 0;
        int max2 = 0, f2 = 0;
        string name, surname;
        vector<string> hsnames;
        vector<string> hssurnames;
        set<string> hsresn;
        set<string> hsress;
        for (auto help : names) {
            if (help.first <= year && help.first >= max1) {
                max1 = help.first;
                if (hsresn.find(help.second) == hsresn.end()) {
                    hsresn.insert(help.second);
                    hsnames.push_back(help.second);
                }
                name = help.second;
                f1 = 1;
            }
        }
        for (auto help : surnames) {
            if (help.first <= year && help.first >= max2) {
                max2 = help.first;
                if (hsress.find(help.second) == hsress.end()) {
                    hsress.insert(help.second);
                    hssurnames.push_back(help.second);
                }
                surname = help.second;
                f2 = 1;
            }
        }
        if (hsnames.size() != 0) {
        if (hsnames[hsnames.size() - 1] == name) {
            hsnames.pop_back();
        }
        }

        if (hssurnames.size() != 0) {
        if (hssurnames[hssurnames.size() - 1] == surname) {
            hssurnames.pop_back();
        }
        }

        reverse(hsnames.begin(), hsnames.end());
        reverse(hssurnames.begin(), hssurnames.end());
        string help = "";
        string help2 = "";
        if (hsnames.size() != 0 && hsnames.size() != 1) {
            help += "(";
            for (int i = 0; i < hsnames.size() - 1; ++i) {
                help += hsnames[i] + ", ";
            }
            help += hsnames[hsnames.size() - 1];
            help += ")";
        } else if (hsnames.size() == 1) {
            help += "(" + hsnames[0] + ")";
        }

        if (hssurnames.size() != 0 && hssurnames.size() != 1) {
            help2 += "(";
            for (int i = 0; i < hssurnames.size() - 1; ++i) {
                help2 += hssurnames[i] + ", ";
            }
            help2 += hssurnames[hssurnames.size() - 1];
            help2 += ")";
        } else if (hssurnames.size() == 1) {
            help2 += "(" + hssurnames[0] + ")";
        }

        if (f1 == 0 && f2 == 0) {
            return "Incognito";
        } else if (f1 == 1 && f2 == 1) {
            if (help != "" && help2 != "") {
                return name + " " + help + " " + surname + " " + help2;
            } else if (help != "" && help2 == "") {
                return name + " " + help + " " + surname;
            } else if (help == "" && help2 != "") {
                return name + " " + surname + " " + help2;
            } else {
                return name + " " + surname;
            }
        } else if (f1 == 1 && f2 == 0) {
            if (help != "") {
                return name + " " + help + " with unknown last name";
            } else {
                return name + " with unknown last name";
            }
        } else if (f1 == 0 && f2 == 1) {
            if (help2 != "") {
                return surname + " " + help2 + " with unknown first name";
            } else {
                return surname + " with unknown first name";
            }
        }
  }

private:
  map<int, string> names;
  map<int, string> surnames;
  int birthyear;
};

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}
