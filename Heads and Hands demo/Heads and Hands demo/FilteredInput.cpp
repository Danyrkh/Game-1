/*!
    \file
    \brief File with the implementation of the FilteredInput function
 */
#include "FilteredInput.hpp"

/*!
    The function processes the input
    \param[in] str Input string
 */
void FilteredInput(std::string& str) {
    getline(std::cin, str);
    if (str.length() == 0) {
        str = "";
    }
    str[0] = toupper(str[0]);
}
