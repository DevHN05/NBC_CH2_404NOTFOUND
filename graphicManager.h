#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <deque>

using namespace std;

class graphicManager {
private:

    graphicManager() {}
    deque<string> gameLogs;

public:
    static graphicManager& get_instance() {
        static graphicManager instance;
        return instance;
    }
    void go_space(int x, int y);
    void set_console_size(int width, int height);

    void draw_layout();
    string show_title();

    void add_log(const string& log);

    void clear_logs();
};