//
//  dfa.hpp
//  lab2
//
//  Created by Владислав Агибалов on 19.07.2025.
//

#ifndef dfa_hpp
#define dfa_hpp

#include <stdio.h>
#include "dfa_node.hpp"
#include "nfa.hpp"
#include "match.hpp"

namespace regex {

class dfa{
    
    std::shared_ptr<dfa_node> start_;
    
    std::set<std::shared_ptr<dfa_node>> all_nodes_;
    
    std::set<std::shared_ptr<dfa_node>> common_nodes_;
    
    std::set<std::shared_ptr<dfa_node>> finish_nodes_;
    
    static std::set<size_t> getAlphabet(std::set<std::shared_ptr<dfa_node>> const&);
    
    std::map<std::shared_ptr<dfa_node>, std::set<std::shared_ptr<dfa_node>>> generateSets(dfa const&) const;
    
    std::pair<std::map<std::shared_ptr<dfa_node>, size_t>, std::vector<std::vector<std::pair<bool, std::string>>>> matrix_generate() const;
    
public:
    
    dfa();
    
    void dfaGenerate(nfa const&);
    
    void minimization(dfa const&);
    
    void print(std::string const &) const;
    
    size_t find(std::string const &, match&) const;
    
    dfa copy() const;
    
    std::string rebirth() const;
    
    bool operator==(const dfa&) const;
    
    dfa intersection(const dfa&);
    
};


}

#endif /* dfa_hpp */
