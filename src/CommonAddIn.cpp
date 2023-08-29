/*
 *  Modern Native AddIn
 *  Copyright (C) 2018  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <iostream>

#include "CommonAddIn.h"

std::string CommonAddIn::extensionName() {
    return "Common";
}

CommonAddIn::CommonAddIn() {

    // Full featured property registration example
    AddProperty(L"Version", L"ВерсияКомпоненты", [&]() {
        auto s = std::string(Version);
        return std::make_shared<variant_t>(std::move(s));
    });

    AddMethod(L"Sleep", L"Ожидать", this, &CommonAddIn::sleep, {{0, 5}});
    AddMethod(L"Print", L"Напечатать", this, &CommonAddIn::print);
}

void CommonAddIn::sleep(const variant_t &delay) {
    using namespace std;
    // It safe to get any type from variant.
    // Exceptions are handled by component API.
    this_thread::sleep_for(chrono::milliseconds(get<int32_t>(delay)));
}


std::string variant_present(const variant_t &msg){

    using namespace std;
    string result;

    visit(overloaded{
            [&](const string &v) { 
                result = v; 
            },
            [&](const int32_t &v) {
                result = to_string(static_cast<int>(v));
            },
            [&](const double &v) { 
                result = to_string(v);
            },
            [&](const bool &v) {
                result = string(v ? u8"Истина" : u8"Ложь");
            },
            [&](const std::tm &v) {
                ostringstream oss;
                oss.imbue(std::locale("ru_RU.utf8"));
                oss << put_time(&v, "%c");
                result = oss.str();
            },
            [&](const vector<char> &v) {
                result = string(v.begin(), v.end());
            },
            [&](const monostate &) { }
    }, msg);
    
    return result;
}

void print_time() {
    std::time_t t = std::time(nullptr);
    std::cout << "[" << std::put_time(std::localtime(&t), "%F %T %Z") << "] ";
}

void CommonAddIn::print(const variant_t &msg) {
    std::string present = variant_present(msg);
    
    if(!present.empty()){
        std::cout << present << std::endl;
    }
}