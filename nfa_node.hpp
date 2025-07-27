//
//  nfa_node.hpp
//  lab2
//
//  Created by Владислав Агибалов on 19.07.2025.
//

#ifndef nfa_node_hpp
#define nfa_node_hpp

#include <stdio.h>
#include "node.hpp"

namespace regex{

class nfa_node: public node{
    
    bool is_finish_;
    
    bool eps_;
    
    size_t is_start_;
    
    size_t is_end_;
    
    std::vector<std::weak_ptr<nfa_node>> eps_edges_;
    
    size_t symbol_;
    
    std::weak_ptr<nfa_node> next_node_;
    
    inline static std::shared_ptr<nfa_node> null_node_ = nullptr;

public:
    
    nfa_node() = delete;
    
    explicit nfa_node(size_t);
    
    explicit nfa_node(size_t, size_t);
    
    explicit nfa_node(char, std::weak_ptr<nfa_node>);
    
    bool getFinish() const;
    
    bool isEps() const;
    
    void setFinish(bool);
    
    size_t size() const;
    
    const std::weak_ptr<regex::nfa_node> operator[](size_t i) const;
    
    void addEps(std::weak_ptr<regex::nfa_node>);
    
    size_t getSymbol() const;
    
    size_t getStart() const;
    
    size_t getEnd() const;
    
    void setStart(size_t);
    
    void setEnd(size_t);
    
    void addEdge(size_t, std::weak_ptr<regex::nfa_node>);
    
};


}


#endif /* nfa_node_hpp */
