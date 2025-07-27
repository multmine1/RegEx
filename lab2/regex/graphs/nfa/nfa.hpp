//
//  nfa.hpp
//  lab2
//
//  Created by Владислав Агибалов on 19.07.2025.
//

#ifndef nfa_hpp
#define nfa_hpp

#include <stdio.h>
#include "nfa_node.hpp"
#include "match.hpp"

namespace regex {

class nfa{
    
    std::shared_ptr<nfa_node> start_;
    
    std::shared_ptr<nfa_node> end_;
    
    std::size_t size_;
    
    std::set<std::shared_ptr<nfa_node>> all_nodes_;
    
public:
    
    explicit nfa();
    
    explicit nfa(size_t);
    
    explicit nfa(size_t, size_t);
    
    void nfaGenerate(std::string);
    
    void concatenation(nfa&);
    
    void alternation(nfa&);
    
    void kleene();
    
    void question();
    
    void repeat(size_t);
    
    void repeat(size_t, size_t);
    
    nfa copy() const;
    
    bool empty() const;
    
    void makevoid();
    
    void print(std::string const &) const;
    
    std::shared_ptr<nfa_node> getStart() const;
    
    size_t find(std::string, match&) const;
    
};

}


#endif /* nfa_hpp */
