#include "./class/XML_READER.h"
#include <iostream>

int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename; // entrada
    XML_READER reader;
    reader.parse_scenaries(xmlfilename);
    scenar **parsed_scenaries = reader.get_parsed_scenaries();

    for (int i = 0; i < reader.get_counter(); i++) {
        cout << parsed_scenaries[i]->flood();
    }

    return 0;
}
