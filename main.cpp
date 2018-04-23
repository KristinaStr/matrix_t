#include <iostream>
 // #include ''stdafx.h''
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
using namespace std;

class matrix_t {
    int **data_;
    unsigned int rows_;
    unsigned int coll_;

public:
    matrix_t() {
        coll_ = 0;
        rows_ = 0;
        data_ = nullptr;
    }

    /*
    matrix_t(matrix_t const &other) {
        rows_ = other.rows_;
        coll_ = other.coll_;
        data_ = new int *[rows_];
        for (unsigned int i = 0; i < rows_; i++) {
            data_[i] = new int[coll_];
            for (unsigned int j = 0; j < coll_; j++) {
                data_[i][j] = other.data_[i][j];

            }
        }
    } */


     matrix_t( unsigned int rows, unsigned int coll)
      {
          rows_ = rows;
          coll_ = coll;
          data_ = new int *[rows_];
          for (unsigned int i = 0; i < rows_; i++)
          {
              data_[i] = int[coll_];
              for (unsigned int j = 0; j < coll_; j++)
              {
                  data_[i][j] = 0;
              }
          }
      }






    matrix_t &operator=(matrix_t const &other) {
        for (unsigned int i = 0; i < rows_; i++) {
            delete[] data_[i];
        }
    }

    matrix_t add(matrix_t const &other) const {
        assert (rows_ == other.rows_ && coll_ == other.coll_);
        matrix_t result;
        for (unsigned int i = 0; i < rows_; i++) {
            for (unsigned int j = 0; j < coll_; j++) {
                result.data_[i][j] = data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }


    matrix_t mul(matrix_t const &other) const {
        assert (rows_ == other.rows_ && coll_ == other.coll_);
        matrix_t result;
        for (unsigned int i = 0; i < rows_; i++) {
            for (unsigned int j = 0; j < coll_; j++) {
                result.data_[i][j] = data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }


    matrix_t sub(matrix_t const &other) const {
        assert (rows_ == other.coll_ && coll_ == other.rows_);
        matrix_t result;
        for (unsigned int i = 0; i < rows_; i++) {
            for (unsigned int j = 0; j < other.coll_; j++) {
                int res = 0;
                for (unsigned int k = 0; k < coll_; k++) {
                    res += data_[i][k] * other.data_[k][j];
                }
                result.data_[i][j] = res;
            }
        }
        return result;

    }

    matrix_t T(matrix_t const &other) const {
        matrix_t result;
        result.rows_ = other.rows_;
        result.coll_ = other.coll_;
        result.data_ = new int *[other.coll_];
        for (unsigned int i = 0; i < other.coll_; i++) {
            result.data_[i] = new int[other.rows_];
        }
        for (unsigned int i = 0; i < rows_; i++) {
            for (unsigned int j = 0; j < coll_; j++) {
                result.data_[i][j] = other.data_[i][j];
            }


        }
        return result;

    }

    ifstream &read(std::ifstream &fin) {
        char op;
        string line;
        getline(fin, line);
        istringstream stream(line);
        if (stream >> rows_ && stream >> op && op == ',' && stream >> coll_) {
            data_ = new int *[rows_];
            for (unsigned int i = 0; i < rows_; i++) {
                data_[i] = new int[coll_];
                for (unsigned int j = 0; j < coll_; j++) {
                    fin >> data_[i][j];
                }
            }
        } else {
            cout << "Error 1";
            exit(0);
        }
        fin.close();
        return fin;
    }

    ostream &write(ostream &stream) {
        for (unsigned int i = 0; i < rows_; i++) {
            for (unsigned int j = 0; j < coll_; j++) {
                stream << data_[i][j] << ' ';
            }
            stream << endl;
        }
        return stream;
    }


    bool name(string &name1, char &op, string &name2) {
        string line;
        getline(cin, line);
        istringstream stream(line);

        if (stream >> name1 && stream >> op) {
            if (op == 'T' || op == 'R') {
                return true;
            }
            else {
                if (stream >> name2) {
                    return true;
                }
            }
        }
        return false;
    }

    ~matrix_t(unsigned int rows_, unsigned coll_) const
    {
        for (unsigned int i = 0; i < rows_; i++)
        {
            delete[] data_[i];
        }
        delete[] data_;
    }
};



int main()
{
    matrix_t matrix1;
    matrix_t result;

    char op ;
    string name1, name2;
    if (!(name(name1, op, name2))) {
        cout << "Error 2";
        cin.get();
        return 0;
    }
    ifstream fin;
    const char * str = name1.c_str();
    fin.open(str);
    if (!fin.is_open()) {
        cerr << "file 1 open fail" << endl;
        return 0;
    }
    matrix1.read(fin);
    if (op == '+' || op == '-' || op == '*')
    {
        matrix_t matrix2;
        ifstream fin;
        const char * str = name2.c_str();
        fin.open(str);
        if (!fin.is_open()) {
            cerr << "file 2 open fail" << endl;
            return 0;
        }
        matrix2.read(fin);
        switch (op)
        {
            case '+':
                result = matrix1.add(matrix2);
                break;
            case '-':
                result = matrix1.sub(matrix2);
                break;
            case '*':
                result = matrix1.mul(matrix2);
                break;
        }
    }
    else if (op == 'T')
    {
        result = result.T(matrix1);

    }
    result.write(cout);
    cin.get();
    return 0;
}


