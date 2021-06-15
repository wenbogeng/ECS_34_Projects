#include "StringUtils.h"
#include <algorithm> 
#include <cctype>
#include <cstdio>
#include <iostream>


namespace StringUtils{
    
std::string Slice(const std::string &str, ssize_t start, ssize_t end){
    // no end argument is passed, default 0;
    if (end == 0 and start + 1 <= str.size()){
        return str.substr(start);
    }
    // both start and end is positive
    else if (start >= 0 and end > 0 and start <= end){
        return str.substr(start, end-start);
    }
    // start is positive and end is negative
    else if (start >= 0 and end < 0){
        // convert negative end index to positive
        int a = end + str.size();
        return str.substr(start, a-start);
    }
    //  start and end are both negative
    else if (start < 0 and end < 0){
        // convert negative indexs into positive
        int b = start+str.size();
        int c = end+str.size();
        return str.substr(b, c-b);
    }
    else {
        return "";
    }
}

std::string Capitalize(const std::string &str){
    std::string value = str;
    // first, turn all the chars into lower case
    for (auto &x : value)
        x = tolower(x);
    // turn the first char into upper case
    value[0] = toupper(value[0]);
    return value;
}

std::string Title(const std::string &str){
    std::string value = str;
    // first, turn all the chars into lower case
    for (auto &x : value)
        x = tolower(x);
    // turn the first char into upper case
    value[0] = toupper(value[0]);
    // if a char have space before it, turn it into upper case
    for (int index = 1; index < value.length(); ++index)
        if (not isalpha(value[index-1]))
            value[index] = toupper(value[index]);
    return value;
    
}

std::string LStrip(const std::string &str){
    std::string value = str;
    int index = 0;
    while (not isalpha(value[index]))
        ++index;
    return value.substr(index, value.length()-(index));
}

std::string RStrip(const std::string &str){
    std::string value = str;
    int index = str.length()-1;
    while (not isalpha(value[index]))
        --index;
    return value.substr(0,index+1);
}

std::string Strip(const std::string &str){
    std::string value = str;
    int index1 = 0;
    while (not isalpha(value[index1]))
        ++index1;
    
    int index2 = str.length()-1;
    while (not isalpha(value[index2]))
        --index2;
    return value.substr(index1, index2-index1+1);
}

std::string Center(const std::string &str, int width, char fill){
    std::string value = str;
    std::string left_addOn ((width-value.length())/2,fill);
    std::string right_addOn ((width-value.length())/2 + (width-value.length())%2 ,fill);
    return left_addOn + value + right_addOn;
}

std::string LJust(const std::string &str, int width, char fill){
    std::string value = str;
    std::string addOn (width-value.length(),fill);
    return value + addOn;
}

std::string RJust(const std::string &str, int width, char fill){
    std::string value = str;
    std::string addOn (width-value.length(),fill);
    return addOn + value;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep){
    // part of these codes is cited from the StackoverFlow, check the readme file for detail
    std::string value = str;
    std::size_t index;
    while (value.find(old) != std::string::npos){
        index = value.find(old);
        value.replace(index, old.length(), rep);
    }
    return value;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt){
    // part of these codes is cited from the StackoverFlow, check the readme file for detail
    std::string value = str;
    std::string spliter = splt;
    std::vector <std::string> result;
    std::string element;
    size_t index = 0;
    
    if (splt == ""){
        while ((index = value.find('\t')) != std::string::npos)
            value[value.find('\t')] = ' ';
        while ((index = value.find('\n')) != std::string::npos)
            value[value.find('\n')] = ' ';
        spliter = " ";
    }

    while ((index = value.find(spliter)) != std::string::npos) {   
        element = value.substr(0, index);
        result.push_back(element);
        value.erase(0, index + spliter.length());
    }
    result.push_back(value);
    
    if (splt == ""){
        while(find(result.begin(), result.end(), "") != result.end())   // cited from GeekforGeek
            result.erase(find(result.begin(), result.end(),""));    // cited from GeekforGeek
    }
    
    return result;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect){
    std::vector <std::string> value = vect;
    std::string result;
    for (auto &x: value){
        result += str+x;
    }
    result = result.substr(1,result.length()-1);
    return result;
}

std::string ExpandTabs(const std::string &str, int tabsize){
    std::vector <std::string> list;
    std::string result;
    
    list = Split(str,"\t");
    
    std::string last = list[list.size()-1];
    list.pop_back();
    
    for (auto &x:list){
        if (tabsize == 0){
            result += x;
        }
        else if (x.length() < tabsize){
            std::string spaces(tabsize - x.length(),' ');
            result += x + spaces;
        }
        else if (x.length() >= tabsize){
            std::string spaces((tabsize*2) - x.length(),' ');
            result += x + spaces;
        }
    }
    result += last;
    return result;
}


int EditDistance(const std::string &left, const std::string &right, bool ignorecase){
    std::string old_ = left;
    std::string new_ = right;

    std::vector <std::string> old_list;
    std::vector <std::string> new_list;

    size_t cost = 0;

    if (ignorecase == true){
        for (auto &x : old_)
            x = tolower(x);
        for (auto &x : new_)
            x = tolower(x);
    }
    
    old_list = Split(old_, "");
    new_list = Split(new_, "");
    
    for (auto index = 0; index < old_list.size(); ++index){
        if (old_list[index] != new_list[index]){
            
            std::string Spaces((old_list[index].length() - new_list[index].length()),' ');
            
            if (old_list[index][0] == new_list[index][0]){
                new_list[index] = new_list[index] + Spaces;
            }
            
            else {
                new_list[index] = Spaces + new_list[index];
            }
            
            for (auto x = 0; x < old_list[index].size(); ++x){
                if (new_list[index][x] != old_list[index][x]){
                    ++cost;
                }
            }
        }
    }
    return cost;
}

}
