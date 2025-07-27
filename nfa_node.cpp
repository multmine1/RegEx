//
//  nfa_node.cpp
//  lab2
//
//  Created by Владислав Агибалов on 19.07.2025.
//

#include "nfa_node.hpp"

regex::nfa_node::nfa_node(size_t isfinish_): is_finish_(isfinish_), eps_(1), symbol_(0), is_start_(0), is_end_(0){}

regex::nfa_node::nfa_node(size_t start_, size_t end_): is_finish_(0), eps_(1), symbol_(0), is_start_(start_), is_end_(end_){
    
    if(start_ != 0 && end_ != 0)
        
        throw std::runtime_error("узел не может быть одновременно и началом, и концом группы.");
    
}

regex::nfa_node::nfa_node(char sym_, std::weak_ptr<nfa_node> next_): eps_(0), symbol_(sym_), is_finish_(0), is_start_(0), is_end_(0), next_node_(next_){}

bool regex::nfa_node::getFinish() const{
    
    return is_finish_;
    
}

bool regex::nfa_node::isEps() const{
    
    return eps_;
    
}

void regex::nfa_node::setFinish(bool finish_){
    
    is_finish_ = finish_;
    
}

size_t regex::nfa_node::size() const{
    
    return eps_edges_.size() + !eps_;
    
}

const std::weak_ptr<regex::nfa_node> regex::nfa_node::operator[](size_t i) const{
    
    if(eps_)
        
        return eps_edges_[i];
    
    if(!i)
        
        return next_node_;
    
    throw std::runtime_error("такого ребра нету.");
}

void regex::nfa_node::addEps(std::weak_ptr<regex::nfa_node> const new_){
    
    if (!eps_)
        
        throw std::runtime_error("это не эпсилон узел");
    
    eps_edges_.push_back(new_);
    
}

size_t regex::nfa_node::getSymbol() const{
    
    return symbol_;
    
}

size_t regex::nfa_node::getStart() const{
    
    return is_start_;
    
}

size_t regex::nfa_node::getEnd() const{
    
    return is_end_;
    
}

void regex::nfa_node::addEdge(size_t sym_, std::weak_ptr<nfa_node> const new_){
    
    eps_ = 0;
    
    symbol_ = sym_;
    
    next_node_ = new_;
    
}

void regex::nfa_node::setStart(size_t start_){
    
    is_start_ = start_;
    
}

void regex::nfa_node::setEnd(size_t end_){
    
    is_end_ = end_;
    
}
