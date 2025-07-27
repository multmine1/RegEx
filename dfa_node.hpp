//
//  dfa_node.hpp
//  lab2
//
//  Created by Владислав Агибалов on 19.07.2025.
//

#ifndef dfa_node_hpp
#define dfa_node_hpp

#include <stdio.h>
#include "node.hpp"

namespace regex {

class dfa_node: public node{
    
    bool finish_;
    
    std::map<size_t, std::weak_ptr<dfa_node>> next_dfa_states_;
    
    inline static std::shared_ptr<dfa_node> null_node_ = nullptr;
    
public:
    
    dfa_node();
    
    std::map<size_t, std::weak_ptr<dfa_node>> const& getnextstates() const;
    
    void setFinish(bool);
    
    bool getFinish() const;
    
    void addEdge(size_t, std::weak_ptr<dfa_node>);
    
    std::weak_ptr<dfa_node> operator[](size_t) const;
};


}


#endif /* dfa_node_hpp */
