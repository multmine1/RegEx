//
//  dfa.cpp
//  lab2
//
//  Created by Владислав Агибалов on 19.07.2025.
//

#include "dfa.hpp"

regex::dfa::dfa(): start_(nullptr){}

void regex::dfa::dfaGenerate(nfa const& nfa_){
    
    std::map<std::set<std::shared_ptr<nfa_node>>, std::shared_ptr<dfa_node>> new_dfa_nodes_;
    
    std::queue<std::set<std::shared_ptr<nfa_node>>> queue_;
    
    std::set<std::set<std::shared_ptr<nfa_node>>> set_;
    
    std::set<std::shared_ptr<nfa_node>> start_set_;
    
    start_set_.emplace(nfa_.getStart());
    
    start_ = std::make_shared<dfa_node>(dfa_node());
    
    new_dfa_nodes_.emplace(start_set_, start_);
    
    queue_.push(start_set_);
    
    while(!queue_.empty()){
        
        size_t old_size = set_.size();
        
        set_.emplace(queue_.front());
        
        size_t new_size = set_.size();
        
        if(old_size == new_size){
            
            queue_.pop();
            
            continue;
            
        }
            
        std::shared_ptr<dfa_node> current_dfa_node_ = new_dfa_nodes_.find(queue_.front())->second;
        
        std::queue<std::shared_ptr<nfa_node>> future_nfa_;
        
        for(auto i: new_dfa_nodes_.find(queue_.front())->first){
            future_nfa_.push(i);
        }
        
        std::set<std::shared_ptr<nfa_node>> passed_nfa_;
        
        std::map<size_t, std::set<std::shared_ptr<nfa_node>>> new_sets_;
        
        std::set<std::shared_ptr<nfa_node>> passed_starts_;
        
        while(!future_nfa_.empty()){
            
            old_size = passed_nfa_.size();
            
            passed_nfa_.emplace(future_nfa_.front());
            
            new_size = passed_nfa_.size();
            
            if(old_size == new_size){
                
                future_nfa_.pop();
                
                continue;
                
            }
                
            std::shared_ptr<nfa_node> current_nfa_ = future_nfa_.front();
            
            if(current_nfa_->isEps()){
                
                current_dfa_node_->setFinish(current_dfa_node_->getFinish() + current_nfa_->getFinish());
                
                for(size_t i = 0; i < current_nfa_->size(); ++i){
                    
                    future_nfa_.push((*current_nfa_)[i].lock());
                    
                }
                    
            } else{
                
                size_t symbol_ = current_nfa_->getSymbol();
                
                std::shared_ptr<nfa_node> next_ = (*current_nfa_)[0].lock();
                
                if(new_sets_.find(symbol_) == new_sets_.end()){
                    
                    std::set<std::shared_ptr<nfa_node>> new_set_;
                    
                    new_set_.emplace(next_);
                    
                    new_sets_.emplace(symbol_, new_set_);
                    
                    passed_starts_.emplace(current_nfa_);
                    
                } else{
                    
                    new_sets_.find(symbol_)->second.emplace(next_);
                    
                }
                
            }
            
            future_nfa_.pop();
            
        }
        
        for(auto i: new_sets_){
            
            if(new_dfa_nodes_.find(i.second) == new_dfa_nodes_.end())
                
                new_dfa_nodes_.emplace(i.second, new dfa_node);
            
            current_dfa_node_->addEdge(i.first, new_dfa_nodes_.find(i.second)->second);
            
        }
        
        if(current_dfa_node_->getFinish()){
            
            finish_nodes_.emplace(current_dfa_node_);
            
        } else{
            
            common_nodes_.emplace(current_dfa_node_);
            
        }
        
        all_nodes_.emplace(current_dfa_node_);
        
        for(auto i: new_sets_){
            
            queue_.push(i.second);
            
        }
        
        queue_.pop();
        
    }
    
    return;
}
    
void regex::dfa::minimization(dfa const& dfa_){
    
    std::map<std::shared_ptr<dfa_node>, std::set<std::shared_ptr<dfa_node>>> included_in_set_ = generateSets(dfa_);
    
    std::set<std::set<std::shared_ptr<dfa_node>>> passed_sets_;
    
    std::queue<std::set<std::shared_ptr<dfa_node>>> sets_queue_;
    
    std::map<std::set<std::shared_ptr<dfa_node>>, std::shared_ptr<dfa_node>> new_nodes_;
    
    std::set<std::shared_ptr<dfa_node>> start_set_ = included_in_set_.find(dfa_.start_)->second;
    
    sets_queue_.push(start_set_);
    
    start_ = std::make_shared<dfa_node>(dfa_node());
    
    new_nodes_.emplace(start_set_, start_);
    
    while(!sets_queue_.empty()){
        
        size_t old_size_ = passed_sets_.size();
        
        passed_sets_.emplace(sets_queue_.front());
        
        size_t new_size_ = passed_sets_.size();
        
        if(old_size_ != new_size_){
            
            std::set<std::shared_ptr<dfa_node>> current_set_ = sets_queue_.front();
            
            std::shared_ptr<dfa_node> current_dfa_ = new_nodes_.find(current_set_)->second;
            
            for(auto i: current_set_){
                
                current_dfa_->setFinish(current_dfa_->getFinish() + i->getFinish());
                
            }
            
            std::shared_ptr<dfa_node> current_node_ = *current_set_.begin();
            
            std::map<size_t, std::weak_ptr<dfa_node>> next_nodes_ = current_node_->getnextstates();
            
            for(auto i: next_nodes_){
                
                std::set<std::shared_ptr<dfa_node>> next_set_ = included_in_set_.find(i.second.lock())->second;
                
                if(new_nodes_.find(next_set_) == new_nodes_.end()){
                    
                    new_nodes_.emplace(next_set_, new dfa_node);
                    
                }
                
                current_dfa_->addEdge(i.first, new_nodes_.find(next_set_)->second);
                
                
                if(next_set_ != sets_queue_.front())
                    
                    sets_queue_.push(next_set_);
                
            }
            
            if(current_dfa_->getFinish())
                
                finish_nodes_.emplace(current_dfa_);
            
            else
                
                common_nodes_.emplace(current_dfa_);
            
            all_nodes_.emplace(current_dfa_);
            
        }
        
        sets_queue_.pop();
        
    }
    
    return;
}

std::map<std::shared_ptr<regex::dfa_node>, std::set<std::shared_ptr<regex::dfa_node>>> regex::dfa::generateSets(dfa const& dfa_) const{
    
    std::map<std::shared_ptr<dfa_node>, std::set<std::shared_ptr<dfa_node>>> included_in_set_;
    
    std::set<std::set<std::shared_ptr<dfa_node>>> set_of_set_;
     
     std::queue<std::set<std::shared_ptr<dfa_node>>> queue_;
     
     if(dfa_.common_nodes_.size())
     
     set_of_set_.emplace(dfa_.common_nodes_);
     
     set_of_set_.emplace(dfa_.finish_nodes_);
     
     for(auto i: dfa_.common_nodes_){
     
     included_in_set_.emplace(i, dfa_.common_nodes_);
     
     }
     
     for(auto i: dfa_.finish_nodes_){
     
     included_in_set_.emplace(i, dfa_.finish_nodes_);
     
     }
     
     size_t old_size_ = (bool)(dfa_.common_nodes_.size()) + (bool)(dfa_.finish_nodes_.size()), new_size_ = 0;
     
     while (old_size_ != new_size_) {
     
     old_size_ = set_of_set_.size();
     
     for(auto i: set_of_set_){
     
     queue_.push(i);
     
     }
     
     while(!queue_.empty()){
     
         for(auto current_letter_: getAlphabet(queue_.front())){
     
     std::map<std::set<std::shared_ptr<dfa_node>>,  std::set<std::shared_ptr<dfa_node>>> new_sets_;
     
     for(auto current_node_: queue_.front()){
     
     std::map<size_t, std::weak_ptr<dfa_node>> const& next_nodes_ = current_node_->getnextstates();
     
     if(next_nodes_.find(current_letter_) == next_nodes_.end()){
     
     if(new_sets_.find(std::set<std::shared_ptr<dfa_node>>()) == new_sets_.end()){
     
     new_sets_.emplace(std::set<std::shared_ptr<dfa_node>>(), std::set<std::shared_ptr<dfa_node>>());
     
     }
     
     new_sets_.find(std::set<std::shared_ptr<dfa_node>>())->second.emplace(current_node_);
     
     } else{
     
     std::set<std::shared_ptr<dfa_node>> next_set_ = included_in_set_.find(next_nodes_.find(current_letter_)->second.lock())->second;
     
     if(new_sets_.find(next_set_) == new_sets_.end()){
     
     new_sets_.emplace(next_set_, std::set<std::shared_ptr<dfa_node>>());
     
     }
     
     new_sets_.find(next_set_)->second.emplace(current_node_);
     
     }
     
     }
     
     if(new_sets_.size() > 1){
     
     set_of_set_.erase(queue_.front());
     
     for(auto i: new_sets_){
     
     for(auto j: i.second){
     
     included_in_set_.find(j)->second = i.second;
     
     }
     
     queue_.push(i.second);
     
     set_of_set_.emplace(i.second);
     
     }
     
     break;
     
     }
     
     }
     
     queue_.pop();
     
     }
     
     new_size_ = set_of_set_.size();
     
     }
    
    return included_in_set_;
    
}

std::set<size_t> regex::dfa::getAlphabet(std::set<std::shared_ptr<dfa_node>> const& nodes_set_){
    
    std::set<size_t> result_;
    
    for(auto currnet_node_: nodes_set_){
        
        for(auto current_edge_: currnet_node_->getnextstates()){
            
            result_.emplace(current_edge_.first);
            
        }
        
    }
    
    return result_;
}

void regex::dfa::print(std::string const & file_name_) const{
    
    std::ofstream out_;
    
    out_.open(file_name_ + ".dot");
    
    out_<< "digraph NFA{" << std::endl;
    
    std::set<std::shared_ptr<dfa_node>> set_;
    
    std::queue<std::shared_ptr<dfa_node>> queue_;
    
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
        
        out_ << "label=\"" <<  set_.size() << "\"]\n";
        
        for(auto i: queue_.front()->getnextstates()){
            
            out_ << "  \"node" << queue_.front() << "\" -> \"node" << i.second.lock() << "\"";
            
            out_ << "[label=\"" << (char)i.first << "\"]\n";
            
            queue_.push(i.second.lock());
            
        }
        
        queue_.pop();
    }
    
    out_<< "}";
    
    out_.close();
    
    std::string siscall("/opt/homebrew/bin/dot -Tpng " + file_name_ + ".dot -o " + file_name_ + ".png");
    
    system(siscall.data());
    
    return;
}

size_t regex::dfa::find(std::string const &recognazing_text_, match& match_) const{
    
    if(start_->getFinish() && recognazing_text_ == ""){
        
        match_.setMatched(std::string(""));
        
        return 1;
        
    }
    
    const char* text_ = recognazing_text_.data();
    
    std::weak_ptr<dfa_node> current_dfa_ = start_;
    
    size_t begin_ = 0;
    
    size_t cur_pos_ = 0;
    
    while(text_[cur_pos_] != 0){
        
        char symbol_ = text_[cur_pos_];
        
        std::weak_ptr<regex::dfa_node> next_state = (*current_dfa_.lock())[symbol_];
        
        if(next_state.lock() == nullptr && current_dfa_.lock()->getFinish()){
            
            match_.setMatched(std::string(recognazing_text_.begin() + begin_, recognazing_text_.begin() + cur_pos_));
            
            return cur_pos_ + 1;
            
        }
        
        ++cur_pos_;
        
        if(next_state.lock() == nullptr)
            
            return cur_pos_ + 1;
            
        else
            current_dfa_ = next_state;
        
    }
    
    std::weak_ptr<regex::dfa_node> next_state = (*current_dfa_.lock())[text_[cur_pos_]];
    
    if(next_state.lock() == nullptr && current_dfa_.lock()->getFinish()){
        
        match_.setMatched(std::string(recognazing_text_.begin() + begin_, recognazing_text_.begin() + cur_pos_));
        
    }
    
    return cur_pos_ + 1;
    
}

regex::dfa regex::dfa::copy() const{
    
    dfa new_dfa_;
    
    std::map<std::shared_ptr<dfa_node>, std::shared_ptr<dfa_node>> new_nodes_;
    
    for(auto i: all_nodes_){
       
        new_nodes_[i] = std::make_shared<dfa_node>(dfa_node());
        
        new_dfa_.all_nodes_.emplace(new_nodes_[i]);
        
    }
    
    for(auto i: common_nodes_){
        
        new_dfa_.common_nodes_.emplace(new_nodes_[i]);
        
    }
    
    for(auto i: finish_nodes_){
        
        new_nodes_[i]->setFinish(i->getFinish());
        
        new_dfa_.finish_nodes_.emplace(new_nodes_[i]);
        
    }
    
    new_dfa_.start_ = new_nodes_[start_];
    
    for(auto i: all_nodes_){
        
        std::map<size_t, std::weak_ptr<dfa_node>> next_states_ = i->getnextstates();
        
        for(auto j: next_states_){
            
            new_nodes_[i]->addEdge(j.first, (new_nodes_[j.second.lock()]));
            
        }
        
    }
    
    return new_dfa_;
}

std::string regex::dfa::rebirth() const{
    
    std::pair<std::map<std::shared_ptr<dfa_node>, size_t>, std::vector<std::vector<std::pair<bool, std::string>>>> id_s_matrix_ = matrix_generate();
    
    std::map<std::shared_ptr<dfa_node>, size_t> id_s_ = id_s_matrix_.first;
    
    std::vector<std::vector<std::pair<bool, std::string>>> matrix_ = id_s_matrix_.second;
    
    std::queue<size_t> queue_;
    
    queue_.push(id_s_[start_]);
    
    std::set<size_t> deleted_;
    
    while(!queue_.empty()){
        
        size_t node_to_be_deleted_ = queue_.front();
        
        size_t old_size_ = deleted_.size();
        
        deleted_.emplace(node_to_be_deleted_);
        
        size_t new_size_ = deleted_.size();
        
        if(old_size_ == new_size_){
            
            queue_.pop();
            
            continue;
            
        }
        
        for(size_t node_before_ = 0; node_before_ < matrix_.size(); ++node_before_){
            
            if(node_before_ == node_to_be_deleted_)
                
                continue;
            
            if(matrix_[node_before_][node_to_be_deleted_].first){
                
                std::string new_expr_ = matrix_[node_before_][node_to_be_deleted_].second;
                
                if(matrix_[node_to_be_deleted_][node_to_be_deleted_].first){
                                            
                    new_expr_ += "(?:" + matrix_[node_to_be_deleted_][node_to_be_deleted_].second + ")*";
                    
                }
                
                for(size_t node_after_ = 1; node_after_ < matrix_.size(); ++node_after_){
                    
                    if(matrix_[node_to_be_deleted_][node_after_].first){
                        
                        if(node_after_ > 1)
                        
                            queue_.push(node_after_);
                        
                        std::string str_ = new_expr_ + matrix_[node_to_be_deleted_][node_after_].second;
                        
                        if(matrix_[node_before_][node_after_].first){
                            
                            if(!matrix_[node_before_][node_after_].second.size()){
                                
                                matrix_[node_before_][node_after_].second = str_;
                                
                            } else{
                                
                                matrix_[node_before_][node_after_].second = "(?:" + matrix_[node_before_][node_after_].second + "|" + str_ + ")";
                                
                            }
                            
                        } else{
                            
                            matrix_[node_before_][node_after_].first = 1;
                            
                            matrix_[node_before_][node_after_].second = str_;
                            
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
        queue_.pop();
        
        for(size_t clear_ = 0; clear_ < matrix_.size(); ++clear_){
            
            matrix_[node_to_be_deleted_][clear_].first = 0;
            
            matrix_[clear_][node_to_be_deleted_].first = 0;
            
            matrix_[node_to_be_deleted_][clear_].second = "$";
            
            matrix_[clear_][node_to_be_deleted_].second = "$";
            
        }
        
    }
    
    return matrix_[0][1].second;
    
}

std::pair<std::map<std::shared_ptr<regex::dfa_node>, size_t>, std::vector<std::vector<std::pair<bool, std::string>>>> regex::dfa::matrix_generate() const{
    
    std::vector<std::vector<std::pair<bool, std::string>>> matrix_;
    
    std::vector<std::pair<bool, std::string>> line_;
    
    for(size_t i = 0; i < all_nodes_.size() + 2; ++i){
        
        line_.push_back(std::make_pair<bool, std::string>(0, "$"));
        
    }
    
    for(size_t i = 0; i < all_nodes_.size() + 2; ++i){
        
        matrix_.push_back(line_);
        
    }
    
    std::map<std::shared_ptr<dfa_node>, size_t> id_s_;
    
    size_t id_ = 2;
    
    for(auto current_node_: finish_nodes_){
        
        id_s_[current_node_] = id_++;
        
    }
    
    for(auto current_node_: common_nodes_){
        
        id_s_[current_node_] = id_++;
        
    }
    
    matrix_[0][id_s_[start_]].first = 1;
    
    for(auto current_finish_: finish_nodes_){
        
        matrix_[id_s_[current_finish_]][1].first = 1;
        
        for(auto next_node_: current_finish_->getnextstates()){
            
            auto& cur_pair_ = matrix_[id_s_[current_finish_]][id_s_[next_node_.second.lock()]];
            
            cur_pair_.first = 1;
            
            std::string symbol(&next_node_.first, &next_node_.first + 1);
            
            std::weak_ptr<regex::dfa_node> next_ = (*next_node_.second.lock())[next_node_.first];
            
            if((current_finish_ != next_node_.second.lock() && next_.lock() != next_node_.second.lock()) || current_finish_ == next_node_.second.lock()){
                
                if(cur_pair_.second == "$")
                    
                    cur_pair_.second = symbol;
                
                else
                    
                    cur_pair_.second += "|" + symbol;
                
            }
            
        }
        
        for(auto& cur_pair_: matrix_[id_s_[current_finish_]]){
        
            if(cur_pair_.second.size() > 1){
                
                cur_pair_.second = "(" + cur_pair_.second + ")";
                
            }
            
        }
        
    }
    
    for(auto current_node_: common_nodes_){
        
        for(auto next_node_: current_node_->getnextstates()){
            
            auto& cur_pair_ = matrix_[id_s_[current_node_]][id_s_[next_node_.second.lock()]];
            
            cur_pair_.first = 1;
            
            std::string symbol(&next_node_.first, &next_node_.first + 1);
            
            std::weak_ptr<regex::dfa_node> next_ = (*next_node_.second.lock())[next_node_.first];
            
            if((current_node_ != next_node_.second.lock() && next_.lock() != next_node_.second.lock()) || current_node_ == next_node_.second.lock()){
                
                if(cur_pair_.second == "$")
                    
                    cur_pair_.second = symbol;
                
                else
                    
                    cur_pair_.second += "|" + symbol;
                
            }
            
        }
        
        for(auto& cur_pair_: matrix_[id_s_[current_node_]]){
            
            if(cur_pair_.second.size() > 1){
                
                cur_pair_.second = "(" + cur_pair_.second + ")";
                
            }
            
        }
        
    }
    
    return std::make_pair(id_s_, matrix_);
    
}

bool regex::dfa::operator==(dfa const & second_) const{
    
    std::pair<std::shared_ptr<dfa_node>, std::shared_ptr<dfa_node>> start_pair_ = std::make_pair(start_, second_.start_);
    
    std::queue<std::pair<std::shared_ptr<dfa_node>, std::shared_ptr<dfa_node>>> queue_;
    
    std::set<std::pair<std::shared_ptr<dfa_node>, std::shared_ptr<dfa_node>>> visited_;
    
    queue_.push(start_pair_);
    
    while(!queue_.empty()){
        
        size_t old_size = visited_.size();
        
        visited_.emplace(queue_.front());
        
        size_t new_size = visited_.size();
        
        if(old_size == new_size){
            
            queue_.pop();
            
            continue;
            
        }
        
        std::map<size_t, std::weak_ptr<dfa_node>> next_nodes_first_ = queue_.front().first->getnextstates();
        
        std::map<size_t, std::weak_ptr<dfa_node>> next_nodes_second_ = queue_.front().second->getnextstates();
        
        if(next_nodes_first_.size() != next_nodes_second_.size())
            
            return 0;
        
        auto first_ = next_nodes_first_.begin();
        
        auto second_ = next_nodes_second_.begin();
        
        for(size_t i = 0; i < next_nodes_first_.size(); ++i){
            
            if(first_->first == second_->first){
                
                queue_.push(std::make_pair(first_->second.lock(), second_->second.lock()));
                
                first_++;
                
                second_++;
                
            } else
                
                return 0;
                
        }
        
        queue_.pop();
        
    }
    
    return 1;
    
}

regex::dfa regex::dfa::intersection(regex::dfa const & second_){
    
    dfa new_dfa_;
    
    std::pair<std::shared_ptr<dfa_node>, std::shared_ptr<dfa_node>> start_pair_ = std::make_pair(start_, second_.start_);
    
    std::map<std::pair<std::shared_ptr<dfa_node>, std::shared_ptr<dfa_node>>, std::shared_ptr<dfa_node>> new_nodes_;
    
    std::queue<std::pair<std::shared_ptr<dfa_node>, std::shared_ptr<dfa_node>>> queue_;
    
    std::set<std::pair<std::shared_ptr<dfa_node>, std::shared_ptr<dfa_node>>> vizited_;
    
    queue_.push(start_pair_);
    
    new_nodes_.emplace(start_pair_, std::make_shared<dfa_node>(dfa_node()));
    
    new_dfa_.start_ = new_nodes_[start_pair_];
    
    while(!queue_.empty()){
        
        size_t old_size_ = vizited_.size();
        
        vizited_.emplace(queue_.front());
        
        size_t new_size_ = vizited_.size();
        
        if(old_size_ == new_size_){
            
            queue_.pop();
            
            continue;
            
        }
        
        std::shared_ptr<dfa_node> current_node_ = new_nodes_[queue_.front()];
        
        std::shared_ptr<dfa_node> first_node_ = queue_.front().first;
        
        std::map<size_t, std::weak_ptr<dfa_node>> first_next_nodes_ = first_node_->getnextstates();
        
        std::shared_ptr<dfa_node> second_node_ = queue_.front().second;
        
        std::map<size_t, std::weak_ptr<dfa_node>> second_next_nodes_ = second_node_->getnextstates();
        
        size_t min_count_ = std::min(first_next_nodes_.size(), second_next_nodes_.size());
        
        auto current_edge_it_ = first_next_nodes_.begin();
        
        for(size_t edge_ = 0; edge_ < min_count_; ++edge_){
            
            auto current_edge_ = *current_edge_it_;
            
            if(second_next_nodes_.contains(current_edge_.first)){
                
                std::pair<std::shared_ptr<dfa_node>, std::shared_ptr<dfa_node>> next_pair_  = std::make_pair(current_edge_.second.lock(), second_next_nodes_[current_edge_.first].lock());
                
                if(!new_nodes_.contains(next_pair_))
                    
                    new_nodes_.emplace(next_pair_, std::make_shared<dfa_node>(dfa_node()));
                
                std::shared_ptr<dfa_node> next_node_ = new_nodes_[next_pair_];
                
                next_node_->setFinish(next_pair_.first->getFinish() * next_pair_.second->getFinish());
                
                current_node_->addEdge(current_edge_.first, next_node_);
                
                queue_.push(next_pair_);
                
            }
            
            ++current_edge_it_;
            
        }
        
        new_dfa_.all_nodes_.emplace(current_node_);
        
        if(current_node_->getFinish())
            
            new_dfa_.finish_nodes_.emplace(current_node_);
        
        else
            
            new_dfa_.common_nodes_.emplace(current_node_);
        
        queue_.pop();
        
    }
    
    return new_dfa_;
    
}
