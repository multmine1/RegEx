//
//  match.cpp
//  lab2
//
//  Created by Владислав Агибалов on 23.07.2025.
//

#include "match.hpp"

regex::groupiterator::groupiterator(const match* mat_, size_t index_): match_(mat_), group_index_(index_){}

regex::groupiterator& regex::groupiterator::operator++(){
    
    if (group_index_ < match_->size()){
        
                ++group_index_;
        
    }
    
    return *this;
    
}

regex::groupiterator regex::groupiterator::operator++(int){
    
    groupiterator tmp = *this;
    
    operator++();
    
    return tmp;
    
}

std::string_view regex::groupiterator::operator*() const{
    
    return (*match_)[group_index_];
    
}

bool regex::groupiterator::operator == (const groupiterator& second_) const {
    
    return ((match_ == second_.match_) && (group_index_ == second_.group_index_));
    
}
        
bool regex::groupiterator::operator != (const regex::groupiterator& second_) const {
    
    return !(*this == second_);
    
}

size_t regex::groupiterator::groupindex() const{
    
    return group_index_;
    
}

bool regex::groupiterator::isMatched() const{
    
    return match_->isMatched();
    
}

regex::groupiterator regex::match::begin() const{

    return groupiterator(this, 0);

}

regex::groupiterator regex::match::end() const {

    return groupiterator(this, groups_.size());

}

regex::match::match(){
    
    groups_.push_back(std::make_tuple(0, 0, 0, 0));
    
}

bool regex::match::operator<(const match& second_) const{
    
    return groups_.size() < second_.groups_.size();
    
}

bool regex::match::operator>(const match& second_) const{
    
    return groups_.size() > second_.groups_.size();
    
}

bool regex::match::operator==(const match& second_) const{
    
    return groups_.size() == second_.groups_.size();
    
}

regex::match::match(size_t size_){
    
    for(size_t i = 0; i < size_ + 1; ++i){
        
        groups_.push_back(std::make_tuple(0, 0, 0, 0));
        
    }
    
}

size_t regex::match::length() const{
    
    return matched_text_.size();
    
}

size_t regex::match::size() const{

    return groups_.size();

}

bool regex::match::isMatched() const{

    if(groups_.size())
    
        return (std::get<0>(groups_[0]));
    
    return 0;

}

void regex::match::setMatched(std::string const & matched_){

    if(!groups_.size())
        
        groups_.push_back(std::make_tuple(0, 0, 0, 0));
        
    groups_[0] = std::make_tuple(1, 0, matched_text_.size(), 0);
    
    matched_text_ = matched_;

}

void regex::match::addGroupStart(size_t group_, size_t start_){

    if(groups_.size() < (group_ + 1))
        
        for(size_t i = groups_.size(); i < group_ + 1; ++i)
            
            groups_.push_back(std::make_tuple(0, 0, 0, 0));

    std::get<3>(groups_[group_]) = start_;

}

void regex::match::addGroupEnd(size_t group_, size_t end_){

    if(groups_.size() < (group_ + 1))
        
        for(size_t i = groups_.size(); i < group_ + 1; ++i)
            
            groups_.push_back(std::make_tuple(0, 0, 0, 0));
    
    if(std::get<3>(groups_[group_]) == end_)
        
        return;
    
    std::get<0>(groups_[group_]) = 1;

    std::get<1>(groups_[group_]) = std::get<3>(groups_[group_]);
    
    std::get<2>(groups_[group_]) = end_;

}

std::string_view const regex::match::operator [](size_t i) const{

    if(!i){
        
        return std::string_view(matched_text_);
        
    }

    if(groups_.size() <= i || !std::get<0>(groups_[i])){
        
        return std::string_view(null_str_);
        
    }

    return std::string_view(matched_text_.begin() + std::get<1>(groups_[i]), matched_text_.begin() + std::get<2>(groups_[i]));

}
