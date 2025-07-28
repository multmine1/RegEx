//
//  match.hpp
//  lab2
//
//  Created by Владислав Агибалов on 23.07.2025.
//

#ifndef match_hpp
#define match_hpp

#include <stdio.h>
#include "node.hpp"

namespace regex {

class match;

class groupiterator {
    
    const match* match_;
    
    size_t group_index_;
    
public:

    groupiterator(const match*, size_t);

    groupiterator& operator++();
    
    groupiterator operator++(int);
    
    std::string_view operator*() const;
    
    bool operator == (const groupiterator &) const;
            
    bool operator != (const groupiterator &) const;
    
    size_t groupindex() const;
    
    bool isMatched() const;
    
};

class match{
    
    std::string matched_text_ = ("");
    
    std::vector<std::tuple<size_t, size_t, size_t, size_t>> groups_;
    
    std::string null_str_ = ("");
    
public:
    
    match();
    
    match(size_t size_);
    
    size_t size() const;

    groupiterator begin() const;
    
    groupiterator end() const;
    
    bool isMatched() const;
    
    void setMatched(std::string const &);
    
    void addGroupStart(size_t, size_t);
    
    void addGroupEnd(size_t, size_t);
    
    bool operator<(const match &) const;
    
    bool operator>(const match &) const;
    
    bool operator==(const match &) const;
    
    std::string_view const operator [](size_t) const;
    
    size_t length() const;
    
};

}

#endif /* match_hpp */
