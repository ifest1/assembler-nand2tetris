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

    public:
        Tradutor();
        
        void concatenate(string dest, string comp, string jump);

        void set_a_value(string raw_value);

        void init_jump_bits_map();
        void init_dest_bits_map();
        void init_comp_bits_map();
        
        void init_instruction_variables();

        string get_binary_instruction();
        string get_a_value();

        void reset();
};