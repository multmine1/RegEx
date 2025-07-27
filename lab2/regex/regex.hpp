//
//  regex.hpp
//  lab2
//
//  Created by Владислав Агибалов on 15.07.2025.
//

#ifndef regex_hpp
#define regex_hpp

#include <stdio.h>
#include "nfa.hpp"
#include "dfa.hpp"

namespace regex{

class regex{
    
    bool addition_ = 0;
    
    std::string pattern_ = "";
    
    bool compiled_ = 0;
    
    nfa nfa_;
    
    dfa dfa_;
    
    dfa min_dfa_;
    
    std::string recognazing_text_ = "";
    
    size_t current_pos_ = 0;
    
    size_t end_pos_ = 0;
    
public:
    
    regex();
    
    regex(std::string);
    
    void compile();
    
    void compile(std::string);
    
    bool rmatch(std::string);
    
    size_t findAll(std::string, std::vector<match>&);
    
    bool find(std::string, match&);
    
    bool find(match&);
    
    bool rmatch(std::string, match&);
    
    size_t findAllWithGroups(std::string, std::vector<match>&);
    
    bool findWithGroups(std::string, match&);
    
    bool findWithGroups(match&);
    
    regex addition();
    
    static regex combine(std::string, std::string);
    
    regex combine(std::string);
    
    regex combine(regex);
    
    static regex intersection(std::string, std::string);
    
    regex intersection(std::string);
    
    regex intersection(regex);
    
    std::string rebirth();
    
    void print(std::string);
    
    bool operator==(regex);
    
};

}

#endif /* regex_hpp */
