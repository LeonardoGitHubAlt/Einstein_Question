#include <iostream>
#include <list>
#include <string.h>

#include "description.h"

Country cn[5]    = {GB, SE, DK, NO, DE};
Pet pet[5]       = {Dog , Bird, Cat, Horse, Fish};
Color color[5]   = {Red, Green, White, Yellow, Blue};
Drink drink[5]   = {Tea, Milk, Beer, Water, Coffee};
Cigarette cig[5] = {Pall, Dunhill, Blends, Master, Prince};

template<typename T>
struct Array {
    T* array;
    int size;
    Array(T* arr, int s)
        : array(arr)
        , size(s)
    {
    }
    static Array copy(const Array<T>& other)
    {
        T* arr = new T[other.size];
        memcpy(arr, other.array, other.size * sizeof(T));
        return Array(arr, other.size);
    }
    void dump() const
    {
        for (int i = 0 ; i < size ; ++i) {
            std::cout.width(11);
            std::cout << convertToStr(array[i]) << ", ";
        }
        std::cout << std::endl;
    }
};

template<typename T>
void getArrayList(const Array<T>& array, std::list<Array<T>>& list, int subIndex)
{
    using Array = Array<T>;

    if (subIndex >= array.size) {
        Array arr = Array::copy(array);
        //arr.dump();
        list.push_back(arr);
        return;
    }
    for (int i = subIndex; i < array.size; ++i) {
        T temp = array.array[subIndex];
        array.array[subIndex] = array.array[i];
        array.array[i] = temp;

        getArrayList(array, list, subIndex + 1);

        array.array[i] = array.array[subIndex];
        array.array[subIndex] = temp;
    }
}

int main(int argc, char* argv[])
{
    Array<Country> cn_array(cn, sizeof(cn)/sizeof(cn[0]));
    std::list<Array<Country>> list_cn;
    getArrayList<Country>(cn_array, list_cn, 0);

    Array<Pet> pet_array(pet, sizeof(pet)/sizeof(pet[0]));
    std::list<Array<Pet>> list_pet;
    getArrayList<Pet>(pet_array, list_pet, 0);

    Array<Color> color_array(color, sizeof(color)/sizeof(color[0]));
    std::list<Array<Color>> list_color;
    getArrayList<Color>(color_array, list_color, 0);

    Array<Drink> drink_array(drink, sizeof(drink)/sizeof(drink[0]));
    std::list<Array<Drink>> list_drink;
    getArrayList<Drink>(drink_array, list_drink, 0);

    Array<Cigarette> cig_array(cig, sizeof(cig)/sizeof(cig[0]));
    std::list<Array<Cigarette>> list_cig;
    getArrayList<Cigarette>(cig_array, list_cig, 0);

    for (auto it_cn = list_cn.begin(); it_cn != list_cn.end() ; ++it_cn) {
        auto array_cn = it_cn->array;
        bool get_next_cn = false;
        // 9. Norway lives in 1st house
        if(array_cn[0] != NO) {
            get_next_cn = true;
        }
        if (get_next_cn) {
            continue;
        }
        for (auto it_pet = list_pet.begin(); it_pet != list_pet.end() ; ++it_pet) {
            auto array_pet = it_pet->array;
            bool get_next_pet = false;
            // 2. Sweden has a Dog
            for(int i = 0; i < it_pet->size; ++i) {
                if (array_cn[i] == SE && array_pet[i] != Dog) {
                    get_next_pet = true;
                    break;
                }
            }
            if(get_next_pet) {
                continue;
            }
             
            for (auto it_color = list_color.begin(); it_color != list_color.end() ; ++it_color) {
                auto array_color = it_color->array;
                bool get_next_color = false;
                // 1. English in Red House
                for(int i = 0; i < it_color->size; ++i) {
                    if (array_cn[i] == GB && array_color[i] != Red) {
                        get_next_color = true;
                        break;
                    }
                }
                if(get_next_color) {
                    continue; 
                }
                // 4. Green house is in the left of White house
                for(int i = 0; i < it_color->size; ++i) {
                    if (array_color[i] == Green || array_color[i] == White) {
                        if (array_color[i] == White) {
                            get_next_color = true;
                        }
                        break;
                    }
                }
                if(get_next_color) {
                    continue; 
                }
                // 14. Norway lives besides Blue house
                for (int i = 0; i < it_color->size; ++i) {
                    if (array_cn[i] == NO) {
                        if (i == 0 && array_color[i+1] != Blue) {
                            get_next_color = true;
                            break;
                        } else if(i == it_color->size-1 && array_color[i-1] != Blue) {
                            get_next_color = true;
                            break;
                        } else if (array_color[i-1] != Blue && array_color[i+1] != Blue) {
                            get_next_color = true;
                            break;
                        }
                    }
                }
                if(get_next_color) {
                    continue; 
                }

                for (auto it_drink = list_drink.begin(); it_drink != list_drink.end() ; ++it_drink) {
                    auto array_drink = it_drink->array;
                    bool get_next_drink = false;

                    // 8. Middle house drinks Milk
                    if (array_drink[it_drink->size/2] != Milk) {
                        get_next_drink = true;
                    }
                    if(get_next_drink) {
                        continue; 
                    }

                    // 3. DenMark drinks Tea
                    for(int i = 0; i < it_drink->size; ++i) {
                        if (array_cn[i] == DK && array_drink[i] != Tea) {
                            get_next_drink = true;
                            break;
                        }
                    }
                    if(get_next_drink) {
                        continue; 
                    }
                    // 5. Green house drinks Coffee
                    for(int i = 0; i < it_drink->size; ++i) {
                        if (array_color[i] == Green && array_drink[i] != Coffee) {
                            get_next_drink = true;
                            break;
                        }
                    }
                    if(get_next_drink) {
                        continue; 
                    }

                    for (auto it_cig = list_cig.begin(); it_cig != list_cig.end() ; ++it_cig) {
                        auto array_cig = it_cig->array;
                        bool get_next_cig = false;
                        // 6. Pall Mall has a Bird
                        for(int i = 0; i < it_cig->size; ++i) {
                            if (array_cig[i] == Pall && array_pet[i] != Bird) {
                                get_next_cig = true;
                                break;
                            }
                        }
                        if(get_next_cig) {
                            continue; 
                        }
                        // 7. Yellow house smokes Dunhill
                        for(int i = 0; i < it_cig->size; ++i) {
                            if (array_color[i] == Yellow && array_cig[i] != Dunhill) {
                                get_next_cig = true;
                                break;
                            }
                        }
                        if(get_next_cig) {
                            continue; 
                        }
                        // 10. Blends lives besides Cat
                        for(int i = 0; i < it_cig->size; ++i) {
                            if (array_cig[i] == Blends) {
                                if (i == 0 && array_pet[i+1] != Cat) {
                                    get_next_cig = true;
                                    break;
                                } else if (i == it_cig->size-1 && array_pet[i-1] != Cat) {
                                    get_next_cig = true;
                                    break;
                                } else if (array_pet[i-1] != Cat && array_pet[i+1] != Cat){
                                    get_next_cig = true;
                                    break;
                                }
                            }
                        }
                        if(get_next_cig) {
                            continue; 
                        }

                        // 11. Horse lives besides smoke Dunhill
                        for(int i = 0; i < it_cig->size; ++i) {
                            if (array_pet[i] == Horse) {
                                if (i == 0 && array_cig[i+1] != Dunhill) {
                                    get_next_cig = true;
                                    break;
                                } else if (i == it_cig->size-1 && array_cig[i-1] != Dunhill) {
                                    get_next_cig = true;
                                    break;
                                } else if (array_cig[i-1] != Dunhill && array_cig[i+1] != Dunhill) {
                                    get_next_cig = true;
                                    break;
                                }
                            }
                        }
                        if(get_next_cig) {
                            continue; 
                        }

                        // 12. Blue Master drinks Beer
                        for(int i = 0; i < it_cig->size; ++i) {
                            if (array_cig[i] == Master && array_drink[i] != Beer) {
                                get_next_cig = true;
                                break;
                            }
                        }
                        if(get_next_cig) {
                            continue; 
                        }

                        // 13. Germany smokes Prince
                        for(int i = 0; i < it_cig->size; ++i) {
                            if (array_cn[i] == DE && array_cig[i] != Prince) {
                                get_next_cig = true;
                                break;
                            }
                        }
                        if(get_next_cig) {
                            continue; 
                        }

                        // 15. Blends lives besides Water
                        for(int i = 0; i < it_cig->size; ++i) {
                            if (array_cig[i] == Blends) {
                                if (i == 0 && array_drink[i+1] != Water) {
                                    get_next_cig = true;
                                    break;
                                } else if (i == it_cig->size-1 && array_drink[i-1] != Water) {
                                    get_next_cig = true;
                                    break;
                                } else if (array_drink[i-1] != Water && array_drink[i+1] != Water) {
                                    get_next_cig = true;
                                    break;
                                }
                            }
                        }
                        if(get_next_cig) {
                            continue; 
                        }

                        std::cout << "===============" << std::endl;
                        it_cn->dump();
                        it_pet->dump();
                        it_color->dump();
                        it_drink->dump();
                        it_cig->dump();
                        std::cout << "===============" << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}
