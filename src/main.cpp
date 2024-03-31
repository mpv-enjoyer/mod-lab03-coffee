// Copyright 2024 mpv-enjoyer
#include "Automata.h"
#include <iostream>

int main() {
    Automata automata;
    std::cout << automata.to_string();
    automata.on();
    std::cout << automata.to_string();
    automata.coin(100);
    std::cout << automata.to_string();
    automata.choice(0);
    std::cout << automata.to_string();
    automata.check();
    std::cout << automata.to_string();
    automata.cook();
    std::cout << automata.to_string();
    automata.finish();
    std::cout << automata.to_string();
    automata.off();
    std::cout << automata.to_string();
    return 0;
}
