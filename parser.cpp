#include <iostream>
#include <string>
#include <algorithm>
#include "parser.h"
#include "util.h"

using namespace std;

Parser::Parser(){}

void Parser::split_c(string instruction)
{
    reset();
    vector<string> values;
    values = split(instruction, "//");
    values = split(values[0], ";");

    if (values.size() > 1)
    {
        jump = values[1];
        values.pop_back();
    }
    else jump.clear();

    values = split(values[0], "=");

    if (values.size() > 1)
    {
        dest = values[0]; comp = values[1];
    }
    else comp = values[0];

    clear_spaces();
}

string Parser::get_value(string value)
{
    del_char(value, '@'); del_char(value, ' ');
    return value;
}

string Parser::get_label(string value)
{
    del_char(value, '('); del_char(value, ')');
    return value;
}

string Parser::get_variable(string value)
{
    del_char(value, '@');
    return value;
}


bool Parser::is_variable(string value)
{
    vector<string> values = split(value, "@");
    if (values.size() > 1)
        return (!isdigit(values[0][0]));
    return false;
}

bool Parser::is_label(string value){ return !(value.rfind("(", 0)); }

bool Parser::ignore_line(string line){ return (!line.rfind("//", 0) || !line.rfind("\r", 0)); }

bool Parser::instruction_type(string instruction){ return !(instruction.find('@') != string::npos); }

void Parser::clear_spaces(){ del_char(dest, ' '); del_char(comp, ' '); del_char(jump, ' '); }

void Parser::reset(){ jump.clear(); comp.clear(); dest.clear(); }

string Parser::get_dest() { return dest; }

string Parser::get_comp() { return comp; }

string Parser::get_jump() { return jump; }
