#include <iostream>
#include <string>
#include <map>
#include <cmath>


class LSystemParser {
private:
    inline double
    cos(const int angle) const
    {
        return round_if_need(std::cos(angle * PI / 180));
    }

    inline double
    sin(const int angle) const
    {
        return round_if_need(std::sin(angle * PI / 180));
    }

    inline double
    round_if_need(const double value) const
    {
        double rounded = std::round(value);
        return abs(rounded - abs(value)) < epsilon ? rounded : value;
    }

    void
    plus_command()
    {
        current_angle += delta_angle;
        log("Find Plus command");
    }

    void
    minus_command()
    {
        current_angle -= delta_angle;
        log("Find Minus command");
    }

    void
    F_command()
    {
        current_x = round_if_need(current_x + delta_step * cos(current_angle));
        current_y = round_if_need(current_y + delta_step * sin(current_angle));

        current_x = current_x < epsilon ? 0 : current_x;
        current_y = current_y < epsilon ? 0 : current_y;

        log("Find F command");
    }

    void
    log(const std::string& log) const
    {
        printf("%s\r\n", log.c_str());
    }

    void
    unknown_command()
    {
        log("Find Unknown command");
    }

public:
    LSystemParser()
    : delta_step(1), delta_angle(90), current_angle(0), current_x(0), current_y(0)
    {
        this->handlers = {
                {'+', [this](){ this->plus_command(); }},
                {'-', [this](){ this->minus_command(); }},
                {'F', [this](){ this->F_command(); }},
        };
    }

    void
    print_state()
    {
        std::cout
            << "delta step = " << delta_step << std::endl
            << "delta angle = " << delta_angle << std::endl
            << "current angle = " << current_angle << std::endl
            << "current (x, y) = (" << current_x << ", " << current_y << ")" << std::endl;
    }

    void run(const std::string& command) {
        for (auto c : command) {
            if (handlers.find(c) != handlers.end()) {
                handlers[c]();
            }
            else {
                unknown_command();
            }
        }
    }


private:
    const double PI = 3.14159265359;
    const double epsilon = 0.00001;

    int delta_step;
    int delta_angle;

    int current_angle;
    double current_x;
    double current_y;

    std::map<char, std::function<void()>> handlers;
};


int
main()
{
    LSystemParser parser;
    parser.print_state();
    parser.run("F+F+F+F");
    parser.print_state();

    return 0;
}
