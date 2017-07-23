#include <sstream>

enum Country {
    GB = 0, // Great Britain
    SE,     // Sweden
    DK,     // Denmark
    NO,     // Norway
    DE,     // Germany
};

enum Pet {
    Dog = 0,
    Bird,
    Cat,
    Horse,
    Fish,
};

enum Color {
    Red = 0,
    Green,
    White,
    Yellow,
    Blue,
};

enum Drink {
    Tea = 0,
    Milk,
    Beer,
    Water,
    Coffee,
};

enum Cigarette {
    Pall = 0,
    Dunhill,
    Blends,
    Master,
    Prince,
};

const char* cn_str[5]
    = {"Britain", "Sweden", "Denmark", "Norway", "Germany"};
const char* pet_str[5]
    = {"Dog", "Bird", "Cat", "Horse", "Fish"};
const char* color_str[5]
    = {"Red", "Green", "White", "Yellow", "Blue"};
const char* drink_str[5]
    = {"Tea", "Milk", "Beer", "Water", "Coffee"};
const char* cig_str[5]
    = {"Pall Mall", "Dunhill", "Blends", "Blue Master", "Prince"};

template <typename T>
const char* convertToStr(T& t)
{
    int index = t;
    std::stringstream ss;
    ss << index;
    return ss.str().c_str();
}

template<>
const char* convertToStr<Country>(Country& cn)
{
    int index = cn;
    return cn_str[index];
}

template<>
const char* convertToStr<Pet>(Pet& pet)
{
    int index = pet;
    return pet_str[index];
}

template<>
const char* convertToStr<Color>(Color& color)
{
    int index = color;
    return color_str[index];
}

template<>
const char* convertToStr<Drink>(Drink& drink)
{
    int index = drink;
    return drink_str[index];
}

template<>
const char* convertToStr<Cigarette>(Cigarette& cig)
{
    int index = cig;
    return cig_str[index];
}
