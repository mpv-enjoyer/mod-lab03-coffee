// Copyright 2024 mpv-enjoyer
#include "Automata.h"

Automata::Automata() {
    _state = States::down;
    _cash = 0;
    _current_id = -1;
    _drinks.push_back({100, "Лимонад"});
    _drinks.push_back({200, "Яблочный сок"});
    _drinks.push_back({350, "Кофе"});
    _drinks.push_back({250, "Чай"});
}

Automata::Automata(States state) {
    _state = state;
    _cash = 0;
    _current_id = -1;
    _drinks.push_back({100, "Лимонад"});
    _drinks.push_back({200, "Яблочный сок"});
    _drinks.push_back({350, "Кофе"});
    _drinks.push_back({250, "Чай"});
}

void Automata::cancel() {
    switch (_state) {
        case (accepting): _state = waiting; return;
        case (checking): _state = waiting; return;
        default: _state = invalid; return;
    }
}

void Automata::choice(int id) {
    if (id > _drinks.size() || id < 0) {
        _state = invalid;
        return;
    }
    _current_id = id;
    switch (_state) {
        case (accepting): _state = checking; return;
        default: _state = invalid; return;
    }
}

void Automata::check() {
    switch (_state) {
        case (checking): _state = checking; return;
        default: _state = invalid; return;
    }
}

void Automata::coin(int cash) {
    _cash += cash;
    switch (_state) {
        case (waiting): _state = accepting; return;
        case (accepting): _state = accepting; return;
        default: _state = invalid; return;
    }
}

void Automata::cook() {
    if (_state == checking) {
        if (_drinks[_current_id].price > _cash) {
            _state = invalid;
            return;
        }
    }
    switch (_state) {
        case (checking): _state = cooking; return;
        default: _state = invalid; return;
    }
}

Drink* Automata::finish() {
    Drink* output = nullptr;
    if (_state == cooking) {
        output = new Drink(_drinks[_current_id]);
    }
    switch (_state) {
        case (cooking): _state = waiting; break;
        default: _state = invalid; break;
    }
    return output;
}

void Automata::off() {
    switch (_state) {
        case (waiting): _state = down; return;
        default: _state = invalid; return;
    }
}

void Automata::on() {
    switch (_state) {
        case (down): _state = waiting; return;
        default: _state = invalid; return;
    }
}

bool Automata::end() {
    switch (_state) {
        case (down): return true;
        default: return false;
    }
}

States Automata::position() {
    return _state;
}

std::string Automata::to_string() {
    std::string output;
    switch (_state) {
        case (down): return "down\n";
        case (waiting): return "waiting\n";
        case (accepting): return "accepting\n";
        case (checking): return "checking\n";
        case (cooking): return "cooking\n";
        case (invalid): return "invalid\n";
        default: return "State not found!";
    }
    return "";
}
