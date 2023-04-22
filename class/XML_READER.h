#include "../data_structures/linked_structures.h"
#include "./scenar.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
using namespace structures;
class XML_READER {
  public:
    XML_READER() {
        stack = new structures::LinkedStack<string>();
        queue = new structures::LinkedQueue<string>();
        xml_content = "";
    }
    ~XML_READER() { delete stack; }

    // Verify if the xml file is well formed and return the number of scenaries
    int verify(string file_name) {
        std::ifstream file(file_name);
        string line;
        int scenaries_counter = 0;
        while (getline(file, line)) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '<') {
                    if (line[i + 1] == '/') {
                        string tag = "";
                        i++;
                        while (line[i] != '>') {
                            tag += line[i];
                            i++;
                        }
                        tag.erase(0, 1);
                        string tag_stack = stack->pop();
                        if (tag_stack != tag) {
                            xml_content = "";
                            stack->clear();
                            throw std::runtime_error("malformed xml");
                        }
                    } else {
                        string tag = "";
                        i++;
                        while (line[i] != '>') {
                            tag += line[i];
                            i++;
                        }
                        stack->push(tag);
                    }
                }
            }
        }
        file.close();
        stack->clear();
        return scenaries_counter;
    }

    // Parse the scenaries and return the xml content as scenar classes
    void parse_scenaries(string file_name) {
        // firstly verify to avoid malformed xml
        int n = verify(file_name);

        std::ifstream file(file_name);
        string line, name;
        int height, widght, robot_x, robot_y, *matrix_base;
        recursive_tags(file_name);
    }

    void recursive_tags(string file_name) {
        std::ifstream file(file_name);
        string line;
        while (getline(file, line)) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '<') {
                    if (line[i + 1] == '/') {
                        i++;
                        while (line[i] != '>') {
                            i++;
                        }
                    } else {
                        string tag = "";
                        i++;
                        while (line[i] != '>') {
                            tag += line[i];
                            i++;
                        }
                        queue->enqueue(tag);
                    }
                } else {
                    string value = "";
                    while (line[i] != '<') {
                        if (i == line.length()) {
                            break;
                        }
                        value += line[i];
                        i++;
                    }
                    i--;
                    queue->enqueue(value);
                }
            }
        }
        file.close();
        // Stack now have all values and its flags
        while (!queue->empty()) {
            cout << queue->dequeue() << endl;
        }
    }

  private:
    structures::LinkedStack<string> *stack;
    structures::LinkedQueue<string> *queue;
    string xml_content;
};