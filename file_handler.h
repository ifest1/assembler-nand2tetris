#include <string>
#include <fstream>

using namespace std;

class FileHandler 
{
    private:
        ifstream input_file;
        ofstream output_file;

    public:
        FileHandler(string input_filename, string output_filename);

        void set_input_file(string filename);
        void set_output_file(string filename);

        bool read_line(string &line);
        void write_line(string line);

        void reset();
        
        void close_stream();
};