#include <iostream>
#include <cassert>
#include <sstream>
#include <stack>
#include <string>

bool is_true_sequence(std::string str) {
    std::stack<char> st;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '(') {
            st.push(str[i]);
        } else if (str[i] == ')') {
            if (st.empty()) {
                return false;
            }
            st.pop();
        }
    }

    if (st.empty()) {
        return true;
    } else {
        return false;
    }
}


int run(std::istream& input, std::ostream& output) {
    std::string str;
    input >> str;

    if (is_true_sequence(str)) {
        output << "YES";
    } else {
        output << "NO";
    }

    return 0;
}

void testFindIn() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "()";
        run(input, output);
        assert(output.str() == "YES");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << ")(";
        run(input, output);
        assert(output.str() == "NO");
    }
}

int main() {
    // testFindIn();
    run(std::cin, std::cout);
    return 0;
}