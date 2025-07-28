//
//  nfa.cpp
//  lab2
//
//  Created by Владислав Агибалов on 19.07.2025.
//

#include "nfa.hpp"

regex::nfa::nfa(): start_(nullptr), end_(nullptr){}

regex::nfa::nfa(size_t symbol_){
    
    end_ = std::make_shared<nfa_node>(nfa_node(1));
    
    start_ = std::make_shared<nfa_node>(nfa_node(symbol_, end_));
    
    all_nodes_.emplace(start_);
    
    all_nodes_.emplace(end_);
    
}

void regex::nfa::nfaGenerate(std::string text_){
    
    char const* text = text_.data();
    
    std::vector<nfa> automats;
    
    automats.push_back(nfa());
    
    automats.push_back(nfa());
    
    automats.push_back(nfa());
    
    size_t group_id_ = 0;
    
    std::stack<std::pair<bool, size_t>> current_id_stack_;
    
    while(text[0] != 0){
        
        switch (text[0]) {
                
            case '(':
                
                if(text[1] != '?' && text[2] != ':'){
                    
                    ++group_id_;
                    
                    current_id_stack_.push(std::pair<bool, size_t>(1, group_id_));
                    
                } else{
                    
                    ++text;
                    
                    ++text;
                    
                    current_id_stack_.push(std::pair<bool, size_t>(0, 0));
                    
                }
                
                automats[automats.size() - 2].concatenation(automats.back());
                
                automats.back() = nfa();
                
                automats.push_back(nfa());
                
                automats.push_back(nfa());
                
                break;
                
            case ')':
                
                automats[automats.size() - 2].concatenation(automats.back());
                
                automats[automats.size() - 3].alternation(automats[automats.size() - 2]);
                
                if(!current_id_stack_.size())
                    
                    throw std::runtime_error("Не все скобки открыты.");
                
                if(current_id_stack_.top().first && !automats[automats.size() - 3].empty()){
                    
                    nfa group_start_ = nfa(current_id_stack_.top().second, 0);
                    
                    nfa group_end_ = nfa(0, current_id_stack_.top().second);
                    
                    group_start_.concatenation(automats[automats.size() - 3]);
                    
                    group_start_.concatenation(group_end_);
                    
                    automats[automats.size() - 3] = group_start_;
                    
                }
                
                automats.pop_back();
                
                automats.pop_back();
                
                current_id_stack_.pop();
                
                break;
                
            case '|':
                
                automats[automats.size() - 2].concatenation(automats.back());
                
                automats.back() = nfa();
                
                automats[automats.size() - 3].alternation(automats[automats.size() - 2]);
                
                automats[automats.size() - 2] = nfa();
                
                break;
                
            case '*':
                
                automats.back().kleene();
                
                break;
                
            case '[':
                
                automats[automats.size() - 2].concatenation(automats.back());
                
                automats.back() = nfa();
                
                ++text;
                
                while(text[0] != ']'){
                    
                    nfa new_graph_ = nfa(text[0]);
                    
                    automats.back().alternation(new_graph_);
                    
                    ++text;
                    
                }
                
                break;
                
            case ']':
                
                throw std::runtime_error("неэкранированный символ ].");
                
            case '{':{
                
                ++text;
                
                size_t times_first_ = 0;
                
                size_t times_second_ = 0;
                
                size_t* current = &times_first_;
                
                bool point_ = 0;
                
                while(text[0] != '}'){
                    
                    if(!std::isdigit(text[0])){
                        
                        if(point_ || text[0] != ',')
                            
                            throw std::runtime_error("не цифра внутри {...}.");
                        
                        if(!point_ && text[0] == ','){
                            
                            point_ = 1;
                            
                            current = &times_second_;
                            
                            ++text;
                            
                            continue;
                            
                        }
                        
                    }
                    
                    *current = *current * 10 + text[0] - '0';
                    
                    ++text;
                    
                }
                
                if(point_ && times_second_ != 0 && times_second_ <= times_first_)
                    
                    throw std::runtime_error("второе количество повторений должно быть больше первого.");
                
                if(point_)
                    
                    automats.back().repeat(times_first_, times_second_);
                
                else
                    
                    automats.back().repeat(times_first_);
                
                break;
                
            }
                
            case '}':
                
                throw std::runtime_error("неэкранированный символ }.");
                
            case '+':
                
                automats.back().repeat(1, 0);
                
                break;
                
            case '?':
                
                automats.back().question();
                
                break;
                
            case '$':
                
                automats[automats.size() - 2].concatenation(automats.back());
                
                automats.back() = nfa();
                
                automats.back().makevoid();
                
                break;
                
            case '\\':
                
                ++text;
                
                if(!text[0])
                    
                    throw std::runtime_error("метасимвол '\' не может экранировать '\0'.");
                
            default:
                
                automats[automats.size() - 2].concatenation(automats.back());
                
                automats.back() = nfa();
                
                automats.back() = nfa(text[0]);
                
                break;
                
        }
        
        ++text;
        
    }
    
    if(automats.size() != 3)
        
        throw std::runtime_error("Не все скобки открыты или закрыты.");
    
    automats[automats.size() - 2].concatenation(automats.back());
    
    automats[automats.size() - 3].alternation(automats[automats.size() - 2]);
    
    automats.pop_back();
    
    automats.pop_back();
    
    *this = automats.back();
    
    size_ = group_id_;
    
    return;
}


regex::nfa::nfa(size_t start__, size_t end__){
    
    if(start__ != 0 && end__ != 0)
        
        throw std::runtime_error("новый граф не может быть одновременно и началом, и концом группы.");
    
    end_ = std::make_shared<nfa_node>(nfa_node(1));
    
    start_ = std::make_shared<nfa_node>(nfa_node(start__, end__));
    
    all_nodes_.emplace(start_);
    
    all_nodes_.emplace(end_);
    
    start_->addEps(end_);
    
}

void regex::nfa::concatenation(nfa& second_){
    
    if(second_.empty())
        
        return;
    
    if(empty()){
        
        *this = second_;
        
        return;
        
    }
    
    all_nodes_.merge(second_.all_nodes_);
    
    *end_.get() = *second_.start_;
    
    end_ = second_.end_;
    
    all_nodes_.erase(second_.start_);
    
    return;
    
}

bool regex::nfa::empty() const{
    
    return start_ == nullptr;
    
}

void regex::nfa::makevoid(){
    
    all_nodes_.clear();
    
    end_ = std::make_shared<nfa_node>(nfa_node(1));
    
    start_ = std::make_shared<nfa_node>(nfa_node(0));
    
    start_->addEps(end_);
    
    all_nodes_.emplace(start_);
    
    all_nodes_.emplace(end_);
    
    return;
    
}

void regex::nfa::alternation(nfa& second_){
    
    if(second_.empty())
        
        return;
    
    if(empty()){
        
        *this = second_;
        
        return;
        
    }
    
    std::shared_ptr<nfa_node> new_start_ = std::make_shared<nfa_node>(nfa_node(0));
    
    all_nodes_.emplace(new_start_);
    
    new_start_->addEps(start_);
    
    new_start_->addEps(second_.start_);
    
    std::shared_ptr<nfa_node> new_end_ = std::make_shared<nfa_node>(nfa_node(1));
    
    all_nodes_.emplace(new_end_);
    
    end_->setFinish(0);
    
    second_.end_->setFinish(0);
    
    end_->addEps(new_end_);
    
    second_.end_->addEps(new_end_);
    
    start_ = new_start_;
    
    end_ = new_end_;
    
    all_nodes_.merge(second_.all_nodes_);
    
    return;
    
}

void regex::nfa::kleene(){
 
    if(empty())
        
        return;
    
    end_->addEps(start_);
    
    std::shared_ptr<nfa_node> new_start_ = std::make_shared<nfa_node>(nfa_node(0));
    
    all_nodes_.emplace(new_start_);
    
    new_start_->addEps(start_);
    
    start_ = new_start_;
    
    std::shared_ptr<nfa_node> new_end_ = std::make_shared<nfa_node>(nfa_node(1));
    
    all_nodes_.emplace(new_end_);
    
    end_->setFinish(0);
    
    end_->addEps(new_end_);
    
    end_=new_end_;
    
    start_->addEps(end_);
    
    return;
    
}

void regex::nfa::repeat(size_t times_){
    
    if(empty())
        
        return;
    
    if(!times_){
        
        *this = nfa();

        return;
    }
    
    nfa copied_ = copy();
    
    for(size_t i = 0; i < times_ - 1; ++i){
        
        nfa graph_new_ = copied_.copy();
        
        concatenation(graph_new_);
    }
    
    return;
    
}

void regex::nfa::repeat(size_t times_first_, size_t times_second_){
    
    if(empty())
        
        return;
    
    nfa copied_ = copy();

    repeat(times_first_);
    
    if(times_second_){
        
        copied_.question();
        
        copied_.repeat(times_second_ - times_first_);
        
    } else{
        
        copied_.kleene();
        
    }
    
    concatenation(copied_);
    
    return;
    
}

void regex::nfa::question(){
    
    if(empty())
        
        return;
    
    std::shared_ptr<nfa_node> new_start_ = std::make_shared<nfa_node>(nfa_node(0));
    
    all_nodes_.emplace(new_start_);
    
    new_start_->addEps(start_);
    
    new_start_->addEps(end_);
    
    start_ = new_start_;
    
    return;
    
}

regex::nfa regex::nfa::copy() const{
    
    nfa new_nfa_;
    
    new_nfa_.size_ = size_;
    
    std::map<std::shared_ptr<nfa_node>, std::shared_ptr<nfa_node>> new_nodes_;
    
    for(auto i: all_nodes_){
       
        new_nodes_[i] = std::make_shared<nfa_node>(nfa_node(0));
        
        new_nfa_.all_nodes_.emplace(new_nodes_[i]);
        
    }
    
    new_nfa_.start_ = new_nodes_[start_];
    
    new_nfa_.end_ = new_nodes_[end_];
    
    for(auto i: all_nodes_){
        
        if(i->isEps()){
            
            new_nodes_[i]->setFinish(i->getFinish());
            
            new_nodes_[i]->setStart(i->getStart());
            
            new_nodes_[i]->setEnd(i->getEnd());
            
            for(size_t j = 0; j < i->size(); ++j){
                
                new_nodes_[i]->addEps(new_nodes_[(*i)[j].lock()]);
                
            }
            
        } else{
            
            new_nodes_[i]->addEdge(i->getSymbol(), (new_nodes_[(*i)[0].lock()]));
            
        }
        
    }
    
    return new_nfa_;
    
}

void regex::nfa::print(std::string const & file_name_) const{
    
    std::ofstream out_;
    
    out_.open(file_name_ + ".dot");
    
    out_<< "digraph NFA{" << std::endl;
    
    std::set<std::shared_ptr<nfa_node>> set_;
    
    std::queue<std::shared_ptr<nfa_node>> queue_;
    
    queue_.push(start_);
    
    while (!queue_.empty() ) {
        
        size_t old_size_ = set_.size();
        
        set_.insert(queue_.front());
        
        size_t new_size_ = set_.size();
        
        if(old_size_ == new_size_){
            
            queue_.pop();
            
            continue;
            
        }
        
        out_ << "  \"node" << queue_.front() << "\"";
        
        out_ << "[";
        
        if(queue_.front()->getFinish()){
            
            out_ << "shape = box, ";
            
        }
        
        out_ << "label=\"" <<  set_.size() << "\n";
        
        if(queue_.front()->getStart())
            
            out_ << "\ngroup starts: " << queue_.front()->getStart();
        
        if(queue_.front()->getEnd())
            
            out_ << "\ngroup ends: " << queue_.front()->getEnd();
        
        out_ << "\"]\n";
        
        if(queue_.front()->isEps()){
            
            for(size_t i = 0; i < queue_.front()->size(); ++i){
                
                out_ << "  \"node" << queue_.front() << "\" -> \"node" << (*queue_.front())[i].lock() << "\"";
                
                if((*queue_.front())[i].lock() != nullptr)
                
                    queue_.push((*queue_.front())[i].lock());
                
            }
            
            queue_.pop();
            
        } else{
            
            out_ << "  \"node" << queue_.front() << "\" -> \"node" << (*queue_.front())[0].lock() << "\"";
            
            out_ << std::format("[label=\"{}\"]\n", (char)queue_.front()->getSymbol());
            
            queue_.push((*queue_.front())[0].lock());
            
            queue_.pop();
            
        }
        
    }
    
    out_<< "}";
    
    out_.close();
    
    std::string siscall("/opt/homebrew/bin/dot -Tpng " + file_name_ + ".dot -o " + file_name_ + ".png");
    
    system(siscall.data());
    
    return;
    
}

size_t regex::nfa::find(std::string recognazing_text_, match& match_) const{
    
    const char* text_ = recognazing_text_.data();
    
    std::shared_ptr<nfa_node> current_nfa_ = start_;
    
    size_t begin_ = 0;
    
    size_t cur_pos_ = 0;
    
    std::set<std::tuple<std::shared_ptr<nfa_node>, match, size_t>> passed_states_;
    
    std::stack<std::tuple<std::shared_ptr<nfa_node>, match, size_t>> future_nodes_;
    
    future_nodes_.push(std::make_tuple(start_, match(size_), 0));
    
    while(!future_nodes_.empty()){
        
        std::tuple<std::shared_ptr<nfa_node>, match, size_t> current_state_ = future_nodes_.top();
        
        future_nodes_.pop();
        
        size_t old_size = passed_states_.size();
        
        passed_states_.emplace(current_state_);
        
        size_t new_size = passed_states_.size();
        
        if(old_size == new_size){
            
            continue;
            
        }
        
        std::shared_ptr<nfa_node> current_node_ = std::get<0>(current_state_);
        
        cur_pos_ = std::get<2>(current_state_);
        
        match new_match_ = std::get<1>(current_state_);
        
        if(current_node_->isEps()){
            
            if(current_node_->getFinish()){
                
                new_match_.setMatched(std::string(recognazing_text_.begin() + begin_, recognazing_text_.begin() + cur_pos_));
                
                if(!match_.length() || new_match_.length() > match_.length())
                
                    match_ = new_match_;
                
            }
            
            if(current_node_->getStart())
                
                new_match_.addGroupStart(current_node_->getStart(), cur_pos_);
            
            if(current_node_->getEnd())
                
                new_match_.addGroupEnd(current_node_->getEnd(), cur_pos_);
            
            for(size_t i = current_node_->size() - 1; i < (size_t)(-1); --i){
                
                future_nodes_.push(std::make_tuple((*current_node_)[i].lock(), new_match_, cur_pos_));
                
            }
            
        } else{
            
            size_t symbol_ = current_node_->getSymbol();
            
            if(text_[cur_pos_] == symbol_){
                
                future_nodes_.push(std::make_tuple((*current_node_)[0].lock(), new_match_, cur_pos_ + 1));
                
            }
            
        }
        
    }
    
    return match_.length() + 1;
    
}



std::shared_ptr<regex::nfa_node> regex::nfa::getStart() const{
    
    return start_;
    
}

