// Copyright 2024 mpv-enjoyer
#pragma once
#include <string>
#include <vector>

enum States {
    down,
    waiting,
    accepting,
    checking,
    cooking,
    invalid
};

struct Drink {
    int price;
    std::string name;
};

class Automata {
    States _state;
    std::vector<Drink> _drinks;
    int _cash;
    int _current_id;
 public:
    Automata();
    explicit Automata(States state);
    void cancel();
    void choice(int id);
    void check();
    void coin(int cash);
    void cook();
    Drink* finish();
    void off();
    void on();
    bool end();
    States position();
    std::string to_string();
};
