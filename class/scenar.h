#include <stdexcept>
#include <string>
using namespace std;

class scenar {
  public:
    scenar(string name, int height, int widght, int robot_x, int robot_y,
           int *matrix_base) {
        name = name;
        height = height;
        widght = widght;
        robot_x = robot_x;
        robot_y = robot_y;
        matrix_base = matrix_base;
    }
    ~scenar() { delete matrix_base; }
    // getters
    string get_name() { return name; }
    int get_height() { return height; }
    int get_widght() { return widght; }
    int get_robot_x() { return robot_x; }
    int get_robot_y() { return robot_y; }
    int *get_matrix_base() { return matrix_base; }

  private:
    // private setters
    void set_name(string name) {
        if (name == "")
            name = "default";
        this->name = name;
    }
    void set_height(int height) {
        if (height <= 0)
            throw std::invalid_argument("height must be positive");
        this->height = height;
    }
    void set_widght(int widght) {
        if (widght <= 0)
            throw std::invalid_argument("widght must be positive");
        this->widght = widght;
    }
    void set_robot_x(int robot_x) {
        if (robot_x < 0 || robot_x >= widght)
            throw std::invalid_argument("robot_x must be positive");
        this->robot_x = robot_x;
    }
    void set_robot_y(int robot_y) {
        if (robot_y < 0 || robot_y >= height)
            throw std::invalid_argument("robot_y must be positive");
        this->robot_y = robot_y;
    }
    void set_matrix_base(int *matrix_base) {
        if (matrix_base == NULL)
            throw std::invalid_argument("matrix_base must be positive");
        this->matrix_base = matrix_base;
    }
    string name;
    int height;
    int widght;
    int robot_x;
    int robot_y;
    int *matrix_base;
};