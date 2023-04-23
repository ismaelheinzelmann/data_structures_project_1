#include "../data_structures/linked_structures.h"
#include "./scenar.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
class XML_READER {
  public:
    XML_READER() {
        stack = new structures::LinkedStack<string>();
        queue = new structures::LinkedQueue<string>();
    }
    ~XML_READER() {
        delete stack;
        for (size_t i = 0; i < scenar_counter; i++) {
            delete scenaries[i];
        }
        delete scenaries;
    }

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
                        if (tag == "cenario") {
                            scenaries_counter++;
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
    }

    void parse_scenaries(string filename) {
        int n;
        try {
            n = verify(filename);
        } catch (std::exception &e) {
            throw std::runtime_error("malformed xml");
        }
        scenar_counter = 0;
        scenaries = new scenar *[n];
        recursive_tags(filename);
        if (queue->dequeue() != "cenarios") {
            throw std::runtime_error("malformed xml");
        }
        for (int k = 0; k < n; k++) {
            string nome = "default";
            int altura = 0, largura = 0, x = 0, y = 0;
            char *matrix;
            queue->dequeue();
            while (!queue->empty() && queue->front() != "cenario") {
                string valor = queue->dequeue();
                if (valor == "nome") {
                    nome = queue->dequeue();
                    continue;
                }
                if (valor == "dimensoes") {
                    for (int i = 0; i < 2; i++) {
                        string inner = queue->dequeue();
                        if (inner == "altura") {
                            altura = stoi(queue->dequeue());
                        }
                        if (inner == "largura") {
                            largura = stoi(queue->dequeue());
                        }
                    }
                }
                if (valor == "robo") {
                    for (int i = 0; i < 2; i++) {
                        string inner = queue->dequeue();
                        if (inner == "x") {
                            x = stoi(queue->dequeue());
                        }
                        if (inner == "y") {
                            y = stoi(queue->dequeue());
                        }
                    }
                }
                if (valor == "matriz") {
                    matrix = new char[altura * largura];
                    for (int i = 0; i < altura; i++) {
                        string line = queue->dequeue();
                        for (int j = 0; j < largura; j++) {
                            matrix[i * largura + j] = line[j];
                        }
                    }
                }
            }
            try {
                scenar *new_scenar =
                    new scenar(nome, altura, largura, x, y, matrix);
                scenaries[scenar_counter] = new_scenar;
                scenar_counter++;
            } catch (const std::exception &e) {
                std::cerr << "Error creating scenary " << nome << '\n';
                std::cerr << e.what() << '\n';
            }
        }
    }
    void print_scenaries() {
        for (int i = 0; i < scenar_counter; i++) {
            cout << scenaries[i]->get_name() << endl;
            cout << scenaries[i]->get_height() << endl;
            cout << scenaries[i]->get_widght() << endl;
            cout << scenaries[i]->get_robot_x() << endl;
            cout << scenaries[i]->get_robot_y() << endl;
            cout << scenaries[i]->get_matrix_base() << endl;
        }
    }
    int get_counter() { return scenar_counter; }
    scenar **get_parsed_scenaries() { return scenaries; }

  private:
    structures::LinkedStack<string> *stack;
    structures::LinkedQueue<string> *queue;
    scenar **scenaries;
    int scenar_counter;
};