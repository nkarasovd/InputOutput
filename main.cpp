#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


void f1(int a, int b) {
    if (a != b)
        throw std::exception();
}

void f2(int a, int b) {
    try {
        f1(a, b);
    }
    catch (std::exception) {
        std::cout << "Неверное число элементов в строке";
        exit(1);
    }
}

int main() {

    std::ofstream out;
    out.open("Test.txt");
    if (out.is_open()) {
        out << "Col1,Col2,Col3" << std::endl;
        out << "1,2,3" << std::endl;
        out << "4,gff,9" << std::endl;
        out << "7,8,9" << std::endl;
        out << "12,12,12" << std::endl;

    }

    std::ifstream infile("Test.txt");
    infile.exceptions(ifstream::badbit);

    std::string line;


    std::vector<std::vector<double>> vv;
    std::vector<string> names;

    std::string::size_type sz;
    double parsed_number = 0.0;
    int z = 0;
    int n = 0;
    bool is_valid;
    int n_col;
    try {
        while (std::getline(infile, line)) {
            std::vector<double> v;

            vector<string> row_values;

            split(line, ',', row_values);

            if (n == 0) {
                n_col = row_values.size();
                for (string item: row_values) {
                    cout << item << ' ';
                    names.push_back(item);
                }

            } else {
                int n_col_local = row_values.size();
                vv.push_back(vector<double>());
                f2(n_col, n_col_local);
                for (int i = 0; i < n_col; ++i) {
                    try {
                        parsed_number = std::stod(row_values[i], &sz);
                        is_valid = true;
                    } catch (std::exception &ia) {
                        is_valid = false;
                    }
                    if (is_valid) {
                        v.push_back(parsed_number);
                        std::cout << v.back() << " ";

                        vv[vv.size() - 1].push_back(parsed_number);

                    } else {
                        v.push_back(NAN);
                        std::cout << v.back() << " ";
                        vv[vv.size() - 1].push_back(NAN);

                    }
                }
            }

            ++z;
            cout << endl;
            ++n;
        }
    } catch (const ifstream::failure &e) {
        cout << "Exception reading file";
    }


    for (int i = 0; i < n_col; ++i) {
        std::cout << names[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < n-1; ++i) {

        for (int j = 0; j < n_col; ++j) {
            std::cout << vv[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
