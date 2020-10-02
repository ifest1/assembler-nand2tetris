#include <iostream>
#include <map>
using namespace std;
class Tradutor
{
    private:
        string binary_instruction, value;
        map<string, string> jump_bits;
        map<string, string> dest_bits;
        map<string, string> comp_bits;

        map<string, int> symbol_table;

    public:
        Tradutor();
        
        void concatenate(string dest, string comp, string jump);

        string bitify(string raw_value);

        void init_jump_bits_map();
        void init_dest_bits_map();
        void init_comp_bits_map();

        void init_symbol_table();
        void init_remaining_predef_symbols();

        bool is_on_symbol_table(string key);
        void add_symbol(string key, int value);
        string get_symbol_value(string key);

        string get_binary_instruction();
    
        string get_bit_sequence_from_int(int length);

        void reset();
};