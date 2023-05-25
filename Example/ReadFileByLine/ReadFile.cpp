#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>

int main() {
    std::string fileName{"test.env"};
    std::ifstream ifs{fileName};

    std::ostringstream outStr;
    for(std::string out; std::getline(ifs, out);) {
        std::vector<std::string> splitVec;
        boost::algorithm::split(splitVec, out, boost::is_any_of("="));
        outStr << splitVec.front();
        if (!ifs.eof()) {
            outStr << ",";
        }
    }
    std::cout << outStr.str() << std::endl;
}
