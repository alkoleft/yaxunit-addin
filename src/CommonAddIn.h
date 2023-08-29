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

#ifndef COMMONADDIN_H
#define COMMONADDIN_H

#include "Component.h"

class CommonAddIn final : public Component {
public:
    const char *Version = u8"1.0.1";

    CommonAddIn();

private:
    std::string extensionName() override;

    void sleep(const variant_t &delay);
    void print(const variant_t &msg);
};

#endif //COMMONADDIN_H
