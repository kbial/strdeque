#include <iostream>
#include <deque>
#include <map>
#include <cassert>
#include <limits>

#include "strdeque.h"
#include "cstrdequeconst"

namespace
{

#ifndef NDEBUG
    const bool debug = true;
    static std::ios_base::Init init;
#else
    const bool debug = false;
#endif

    using std::string;
    using std::deque;
    using map = std::map<unsigned long, deque<string>>;
    bool is_initialized = false;

    map& deque_map()
    {
        static map deque_map;
        return deque_map;
    }

    unsigned long last_index;

    void initialize()
    {
        if (is_initialized) return;

        deque_map()[jnp1::emptystrdeque()] = deque<string>();
        if (debug) std::cerr << "strdequeconst init finished" << std::endl;
        last_index = 0;
        is_initialized = true;
    }

    void cerr_function_with_params(string function_name, int params_length = 0, string params[] = nullptr)
    {

        if (!debug) return;

        std::cerr << function_name << "(";
        if (params != nullptr)
        {
            for (int i = 0; i < params_length - 1; i++)
                std::cerr << params[i] << ", ";
            std::cerr << params[params_length - 1] << ")" << std::endl;
        }
        else std::cerr << ")" << std::endl;
    }

    void cerr_id_message(string function_name, unsigned long id, string message)
    {
        if (!debug) return;

        std::cerr << function_name << ": ";
        if (id == 0) std::cerr << "the Empty Deque";
        else std::cerr << "deque " << id;
        std::cerr << " " << message << std::endl;
    }

    void cerr_empty_deque(string function_name, string message)
    {
        if (!debug) return;

        std::cerr << function_name << ": attempt to ";
        std::cerr << message << " " << "the Empty Deque" << std::endl;
    }

    void cerr_not_containing(string function_name, unsigned long id, size_t index)
    {
        if (!debug) return;

        std::cerr << function_name << ": ";
        if (id == 0) std::cerr << "the Empty Deque";
        else std::cerr << "deque " << id;
        std::cerr << " does not contain an element at " << index << std::endl;
    }

    void cerr_successful_size(string function_name, unsigned long id, size_t size)
    {
        if (!debug) return;

        std::cerr << function_name << ": ";
        if (id == 0) std::cerr << "the Empty Deque";
        else std::cerr << "deque " << id;
        std::cerr << " contains " << size << " elements" << std::endl;
    }

    void cerr_successful_insert(string function_name, unsigned long id,
                                const char* val, size_t pos)
    {
        if (!debug) return;

        std::cerr << function_name << ": deque " << id;
        std::cerr << " - element \"" << val << "\" inserted at ";
        std::cerr << pos << std::endl;
    }

    void cerr_successful_removal(string function_name, unsigned long id, size_t pos)
    {
        if (!debug) return;

        std::cerr << function_name << ": deque " << id;
        std::cerr << " - element at " << pos << " removed" << std::endl;
    }

    void cerr_successful_get(string function_name, unsigned long id,
                             size_t pos, const char* val)
    {
        if (!debug) return;

        std::cerr << function_name << ": deque " << id << " - element at ";
        std::cerr << pos << " is " << "\"" << val << "\"" << std::endl;
    }

    void cerr_successful_comp(string function_name, unsigned long id1,
                              unsigned long id2, int result)
    {
        if (!debug) return;

        std::cerr << function_name << ": result of comparing ";
        if (id1 == 0) std::cerr << "the Empty Deque";
        else std::cerr << "deque " << id1;
        std::cerr << " to ";
        if (id2 == 0) std::cerr << "the Empty Deque";
        else std::cerr << "deque " << id2;
        std::cerr << " is " << result << std::endl;
    }
}

namespace jnp1
{

    unsigned long strdeque_new()
    {
        const static string strdeque_new_name = "strdeque_new";
        cerr_function_with_params(strdeque_new_name);
        initialize();

        if (debug) assert(last_index < std::numeric_limits<unsigned long>::max());
        last_index++;

        deque<string> new_deque;
        deque_map()[last_index] = new_deque;
        unsigned long deque_id = last_index;

        cerr_id_message(strdeque_new_name, deque_id, "created");
        return deque_id;
    }

    void strdeque_delete(unsigned long id)
    {
        const static string strdeque_delete_name = "strdeque_delete";
        string params[1] {std::to_string(id)};
        cerr_function_with_params(strdeque_delete_name, 1, params);
        initialize();

        if (id == 0)
        {
            cerr_empty_deque(strdeque_delete_name, "delete");
            return;
        }

        unsigned long erased_deques = deque_map().erase(id);

        if (debug && erased_deques == 1)
            cerr_id_message(strdeque_delete_name, id, "deleted");
        if (debug && erased_deques == 0)
            cerr_id_message(strdeque_delete_name, id, "does not exist");
    }

    size_t strdeque_size(unsigned long id)
    {
        const static string strdeque_size_name = "strdeque_size";
        string params[1] {std::to_string(id)};
        cerr_function_with_params(strdeque_size_name, 1, params);
        initialize();

        size_t deque_size;
        unsigned long found_deques = deque_map().count(id);
        if (found_deques == 0) deque_size = 0;
        else deque_size = deque_map()[id].size();

        if (debug && found_deques == 1)
            cerr_successful_size(strdeque_size_name, id, deque_size);
        if (debug && found_deques == 0)
            cerr_id_message(strdeque_size_name, id, "does not exist");

        return deque_size;
    }

    void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
    {
        const static string strdeque_insert_name = "strdeque_insert_at";
        string params[3]
        {
                std::to_string(id),
                std::to_string(pos),
                value == nullptr ? "NULL" : ("\"" + string(value) + "\"")
        };
        cerr_function_with_params(strdeque_insert_name, 3, params);
        initialize();

        if (id == 0)
        {
            cerr_empty_deque(strdeque_insert_name, "insert into");
            return;
        }

        if (deque_map().count(id) == 0)
        {
            cerr_id_message(strdeque_insert_name, id, "does not exist");
            return;
        }
        if (value == nullptr)
        {
            cerr_id_message(strdeque_insert_name, id,
                            "- attempt to insert NULL into a deque");
            return;
        }

        string val(value);
        deque<string>& searched_deque = deque_map()[id];
        size_t insert_index = pos;
        if (pos > searched_deque.size()) insert_index = searched_deque.size();
        searched_deque.insert(searched_deque.begin() + insert_index, val);

        cerr_successful_insert(strdeque_insert_name, id, value, insert_index);
    }

    void strdeque_remove_at(unsigned long id, size_t pos)
    {
        const static string strdeque_remove_name = "strdeque_remove_at";
        string params[2]
        {
                std::to_string(id),
                std::to_string(pos)
        };
        cerr_function_with_params(strdeque_remove_name, 2, params);
        initialize();

        if (id == 0)
        {
            cerr_empty_deque(strdeque_remove_name, "remove from");
            return;
        }

        if (deque_map().count(id) == 0)
        {
            cerr_id_message(strdeque_remove_name, id, "does not exist");
            return;
        }

        deque<string>& searched_deque = deque_map()[id];
        if (pos >= searched_deque.size())
        {
            cerr_not_containing(strdeque_remove_name, id, pos);
            return;
        }

        searched_deque.erase(searched_deque.begin() + pos);
        cerr_successful_removal(strdeque_remove_name, id, pos);
    }

    const char* strdeque_get_at(unsigned long id, size_t pos)
    {
        const static string strdeque_get_name = "strdeque_get_at";
        string params[2]
        {
                std::to_string(id),
                std::to_string(pos)
        };
        cerr_function_with_params(strdeque_get_name, 2, params);
        initialize();

        if (deque_map().count(id) == 0)
        {
            cerr_id_message(strdeque_get_name, id, "does not exist");
            return nullptr;
        }

        deque<string>& searched_deque = deque_map()[id];
        if (pos >= searched_deque.size())
        {
            cerr_not_containing(strdeque_get_name, id, pos);
            return nullptr;
        }

        cerr_successful_get(strdeque_get_name, id, pos, searched_deque[pos].c_str());
        return searched_deque[pos].c_str();
    }

    void strdeque_clear(unsigned long id)
    {
        const static string strdeque_clear_name = "strdeque_clear";
        string params[1] {std::to_string(id)};
        cerr_function_with_params(strdeque_clear_name, 1, params);
        initialize();

        if (id == 0)
        {
            cerr_empty_deque(strdeque_clear_name, "clear");
            return;
        }

        if (deque_map().count(id) == 0)
        {
            cerr_id_message(strdeque_clear_name, id, "does not exist");
            return;
        }


        deque<string> new_deque;
        deque_map()[id] = new_deque;
        cerr_id_message(strdeque_clear_name, id, "cleared");
    }

    int strdeque_comp(unsigned long int id1, unsigned long id2)
    {
        const static string strdeque_comp_name = "strdeque_comp";
        string params[2]
        {
                std::to_string(id1),
                std::to_string(id2)
        };
        cerr_function_with_params(strdeque_comp_name, 2, params);
        initialize();

        deque<string> deque1, deque2;

        if (deque_map().count(id1) == 0)
        {
            deque1 = deque_map()[0];
            cerr_id_message(strdeque_comp_name, id1, "does not exist");
        }
        else deque1 = deque_map()[id1];

        if (deque_map().count(id2) == 0)
        {
            deque2 = deque_map()[0];
            cerr_id_message(strdeque_comp_name, id2, "does not exist");
        }
        else deque2 = deque_map()[id2];

        int result;
        if (deque1 < deque2) result = -1;
        else if (deque1 > deque2) result = 1;
        else result = 0;

        cerr_successful_comp(strdeque_comp_name, id1, id2, result);
        return result;
    }
}