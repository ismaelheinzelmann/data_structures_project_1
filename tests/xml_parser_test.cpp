#include "../class/XML_READER.h"
// ctrl shift h
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    XML_READER reader;

    reader.parse_scenaries("../scenaries/cenarios1.xml");
    // reader.parse_scenaries("../scenaries/cenarios2.xml");
    // reader.parse_scenaries("../scenaries/cenarios3.xml");
    // reader.parse_scenaries("../scenaries/cenarios4.xml");
    // reader.parse_scenaries("../scenaries/cenarios5.xml");
    // reader.parse_scenaries("../scenaries/cenarios6.xml");
    
    return 0;
}