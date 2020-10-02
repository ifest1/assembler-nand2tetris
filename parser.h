using namespace std;

class Parser 
{
    private:
        string dest, comp, jump;

    public:
        Parser();

        bool instruction_type(string instruction);
        
        bool ignore_line(string line);
        
        void split_c(string instruction);

        string get_dest();
        string get_comp();
        string get_jump();     

        string get_value(string value);
        string get_label(string value);
        string get_variable(string value);
        bool is_variable(string value);
        bool is_label(string value);

        void reset();
        void clear_spaces();
};