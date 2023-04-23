#include "./class/XML_READER.h"
#include <iostream>
#include <string>

int flood(scenar *scenar) {
    int flood;
    char map[scenar->get_height()][scenar->get_widght()];

    for (size_t i = 0; i < scenar->get_height(); i++) {
        for (size_t j = 0; j < scenar->get_widght(); j++) {
            map[i][j] = '0';
        }
    }
    // robot_x * get_widght() + robot_y
    if (scenar->get_matrix_base()[scenar->get_robot_x() * scenar->get_widght() +
                                  scenar->get_robot_y()] != '0') {
        structures::LinkedQueue<string> queue;
        queue.enqueue(to_string(scenar->get_robot_x()) + " " +
                      to_string(scenar->get_robot_y()));
        map[scenar->get_robot_x()][scenar->get_robot_y()] = '1';
        flood = 1;
        while (!queue.empty()) {
            string aux = queue.dequeue();
            int x = stoi(aux.substr(0, aux.find(" ")));
            int y = stoi(aux.substr(aux.find(" ") + 1, aux.size()));
            if (x - 1 >= 0) {
                if (scenar->get_matrix_base()[(x - 1) * scenar->get_widght() + y] !=
                    '0') {
                    if (map[x - 1][y] == '0') {
                        queue.enqueue(to_string(x - 1) + " " + to_string(y));
                        map[x - 1][y] = '1';
                        flood++;
                    }
                }
            }
            if (x + 1 < scenar->get_height()) {
                if (scenar->get_matrix_base()[(x + 1) * scenar->get_widght() + y] !=
                    '0') {
                    if (map[x + 1][y] == '0') {
                        queue.enqueue(to_string(x + 1) + " " + to_string(y));
                        map[x + 1][y] = '1';
                        flood++;
                    }
                }
            }
            if (y - 1 >= 0) {
                if (scenar->get_matrix_base()[x * scenar->get_widght() + y - 1] !=
                    '0') {
                    if (map[x][y - 1] == '0') {
                        queue.enqueue(to_string(x) + " " + to_string(y - 1));
                        map[x][y - 1] = '1';
                        flood++;
                    }
                }
            }
            if (y + 1 < scenar->get_widght()) {
                if (scenar->get_matrix_base()[x * scenar->get_widght() + y + 1] !=
                    '0') {
                    if (map[x][y + 1] == '0') {
                        queue.enqueue(to_string(x) + " " + to_string(y + 1));
                        map[x][y + 1] = '1';
                        flood++;
                    }
                }
            }
        }
        return flood;
    }
    return 0;
}
int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename; // entrada
    XML_READER reader;
    reader.parse_scenaries(xmlfilename);
    scenar **parsed_scenaries = reader.get_parsed_scenaries();

    for (int i = 0; i < reader.get_counter(); i++) {
        cout << parsed_scenaries[i]->get_name() << " "
             << flood(parsed_scenaries[i]) << endl;
    }

    return 0;
}
