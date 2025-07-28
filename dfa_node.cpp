//
//  dfa_node.cpp
//  lab2
//
//  Created by Владислав Агибалов on 19.07.2025.
//

#include "dfa_node.hpp"

regex::dfa_node::dfa_node(): finish_(0){}

void regex::dfa_node::setFinish(bool f_){
    
    finish_ = f_;
    
}

bool regex::dfa_node::getFinish() const{
    
    return finish_;
    
}

void regex::dfa_node::addEdge(size_t symbol_, std::weak_ptr<dfa_node> next_){
    
    if(next_dfa_states_.find(symbol_) == next_dfa_states_.end()){
        
        next_dfa_states_.emplace(symbol_, next_);
        
    } else{
        
        if(next_dfa_states_.find(symbol_)->second.lock() != next_.lock())
            
            throw std::runtime_error("переход по такому символу уже есть.");
        
    }
    
}

std::map<size_t, std::weak_ptr<regex::dfa_node>> const& regex::dfa_node::getnextstates() const{
    
    return next_dfa_states_;
    
}

std::weak_ptr<regex::dfa_node> regex::dfa_node::operator[](size_t symbol_) const{
    
    if(next_dfa_states_.contains(symbol_))
    
        return next_dfa_states_.find(symbol_)->second;
    
    return null_node_;
    
}
