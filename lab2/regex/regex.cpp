//
//  regex.cpp
//  lab2
//
//  Created by Владислав Агибалов on 15.07.2025.
//

#include "regex.hpp"

regex::regex::regex(){}

regex::regex::regex(std::string pat_): pattern_(pat_){}

void regex::regex::compile(){
    
    if(!compiled_){
        
        nfa_.nfaGenerate(pattern_);
        
        dfa_.dfaGenerate(nfa_);
        
        min_dfa_.minimization(dfa_);
        
        compiled_ = 1;
        
    }
    
    return;
}

void regex::regex::compile(std::string new_pattern_){
    
    compiled_ = 0;
    
    pattern_ = new_pattern_;
    
    compile();
    
    return;
}

bool regex::regex::rmatch(std::string text_){
    
    compile();
    
    recognazing_text_ = text_;
    
    current_pos_ = 0;
    
    end_pos_ = text_.size() + 1;
    
    match new_match_(0);
    
    size_t step = min_dfa_.find(recognazing_text_, new_match_);
    
    if(!new_match_.isMatched() || step != end_pos_)
        
        return addition_;
    
    //match_ = new_match_;
    
    return !addition_;
    
}

size_t regex::regex::findAll(std::string text_, std::vector<match>& matches_){
    
    matches_.clear();

    compile();
    
    size_t res_ = 0;
    
    match result_;
    
    recognazing_text_ = text_;
    
    current_pos_ = 0;
    
    end_pos_ = text_.size() + 1;
    
    while(find(result_)){
        
        res_ += 1;
        
        matches_.push_back(result_);
        
        result_ = match();
        
    }
    
    return res_;
}

bool regex::regex::find(std::string text_, match& match_){
    
    recognazing_text_ = text_;
    
    current_pos_ = 0;
    
    end_pos_ = text_.size() + 1;
    
    return find(match_);
    
}

bool regex::regex::find(match& match_){
    
    match_ = match();

    compile();
    
    while(current_pos_ != end_pos_){
        
        if(addition_){
            
            if(rmatch(recognazing_text_))
                
                match_.setMatched(recognazing_text_);
            
            current_pos_ = end_pos_;
            
            return match_.isMatched();
            
        }
        
        size_t step = min_dfa_.find(std::string(recognazing_text_.begin() + current_pos_, recognazing_text_.end()), match_);
        
        if(!match_.isMatched())
            
            ++current_pos_;
        
        else{
            
            current_pos_ += step;
            
            return match_.isMatched();
            
        }
        
        
    }
    return match_.isMatched();
    
}

bool regex::regex::rmatch(std::string text_, match& match_){
    
    if(addition_)
    
        throw std::runtime_error("у дополнения не может быть групп захвата.");
        
    
    match_ = match();

    compile();
    
    recognazing_text_ = text_;
    
    current_pos_ = 0;
    
    end_pos_ = text_.size() + 1;
    
    match new_match_(0);
    
    size_t step = nfa_.find(recognazing_text_, new_match_);
    
    if(!new_match_.isMatched() || step != end_pos_)
        
        return 0;
    
    match_ = new_match_;
    
    return 1;
    
}

size_t regex::regex::findAllWithGroups(std::string text_, std::vector<match>& matches_){
    
    matches_.clear();

    compile();
    
    if(addition_)
    
        throw std::runtime_error("у дополнения не может быть групп захвата.");
    
    size_t res_ = 0;
    
    match result_;
    
    recognazing_text_ = text_;
    
    current_pos_ = 0;
    
    end_pos_ = text_.size() + 1;
    
    while(findWithGroups(result_)){
        
        res_ += 1;
        
        matches_.push_back(result_);
        
        result_ = match();
        
    }
    
    return res_;
}

bool regex::regex::findWithGroups(std::string text_, match& match_){
    
    recognazing_text_ = text_;
    
    current_pos_ = 0;
    
    end_pos_ = text_.size() + 1;
    
    return findWithGroups(match_);
    
}

bool regex::regex::findWithGroups(match& match_){
    
    if(addition_)
    
        throw std::runtime_error("у дополнения не может быть групп захвата.");
    
    match_ = match();
    
    compile();
    
    while(current_pos_ != end_pos_){
        
        size_t step = nfa_.find(std::string(recognazing_text_.begin() + current_pos_, recognazing_text_.end()), match_);
        
        if(!match_.isMatched())
            
            ++current_pos_;
        
        else{
            
            current_pos_ += step;
            
            return match_.isMatched();
            
        }
        
        
    }
    
    return match_.isMatched();
    
}

regex::regex regex::regex::addition(){
    

    compile();
    
    regex new_regex_;
    
    new_regex_.addition_ = !addition_;
    
    new_regex_.compiled_ = 1;
    
    new_regex_.pattern_ = pattern_;
    
    new_regex_.nfa_ = nfa_.copy();
    
    new_regex_.dfa_ = dfa_.copy();
    
    new_regex_.min_dfa_ = min_dfa_.copy();
    
    return new_regex_;
    
    
}

regex::regex regex::regex::combine(std::string first_str_, std::string second_str_){
    
    regex first_reg_(first_str_);
    
    return first_reg_.combine(second_str_);
    
}

regex::regex regex::regex::combine(std::string second_str_){
    
    regex second_reg_(second_str_);
    
    return combine(second_reg_);
    
}

regex::regex regex::regex::combine(regex second_){
    
    if(addition_ || second_.addition_)
        
        throw std::runtime_error("дополнение нельзя совместить");
    
    regex new_regex_;
    
    compile();
    
    second_.compile();
    
    new_regex_.pattern_ = pattern_ + "|" + second_.pattern_;
    
    new_regex_.nfa_ = nfa_.copy();
    
    nfa second_nfa_;
        
    second_nfa_ = second_.nfa_.copy();
    
    new_regex_.nfa_.alternation(second_nfa_);
    
    new_regex_.dfa_.dfaGenerate(new_regex_.nfa_);
    
    new_regex_.min_dfa_.minimization(new_regex_.dfa_);

    new_regex_.compiled_ = 1;
    
    return new_regex_;
    
}

std::string regex::regex::rebirth(){
    
    compile();
    
    return dfa_.rebirth();
}

void regex::regex::print(std::string name_){
    

    compile();
    
    nfa_.print(name_ + "_nfa");
    
    dfa_.print(name_ + "_dfa");
    
    min_dfa_.print(name_ + "_min_dfa");
    
}

bool regex::regex::operator==(regex second_){
    
    compile();

    second_.compile();
    
    return (min_dfa_ == second_.min_dfa_);
    
}

regex::regex regex::regex::intersection(std::string first_str_, std::string second_str_){
    
    regex first_reg_(first_str_);
    
    return first_reg_.intersection(second_str_);
    
}

regex::regex regex::regex::intersection(std::string second_str_){
    
    regex second_reg_(second_str_);
    
    return intersection(second_reg_);
    
}

regex::regex regex::regex::intersection(regex second_){
    
    compile();
    
    second_.compile();
    
    regex new_regex_;
    
    new_regex_.compiled_ = 1;
    
    new_regex_.dfa_ = dfa_.intersection(second_.dfa_);
    
    new_regex_.pattern_ = new_regex_.dfa_.rebirth();
    
    new_regex_.nfa_.nfaGenerate(new_regex_.pattern_);
    
    dfa dfa_v2_;
    
    dfa_v2_.dfaGenerate(new_regex_.nfa_);
    
    new_regex_.min_dfa_.minimization(dfa_v2_);
    
    return new_regex_;
    
}
