//
//  tests.m
//  tests
//
//  Created by Владислав Агибалов on 26.07.2025.
//

#import <XCTest/XCTest.h>
#import "regex.hpp"


@interface tests : XCTestCase

@end

@implementation tests

- (void)testMatchOneLetter {
    
    regex::regex pattern_;
    
    pattern_.compile("a");
    
    XCTAssertTrue(pattern_.rmatch("a"));
    
    XCTAssertFalse(pattern_.rmatch(""));
    
    XCTAssertFalse(pattern_.rmatch("b"));
    
    XCTAssertFalse(pattern_.rmatch("ab"));
    
    XCTAssertFalse(pattern_.rmatch("ba"));
    
    XCTAssertFalse(pattern_.rmatch("aa"));
    
}

- (void)testMatchKlenee {
    
    regex::regex pattern_;
    
    pattern_.compile("a*");
    
    XCTAssertTrue(pattern_.rmatch(""));
    
    XCTAssertTrue(pattern_.rmatch("a"));
    
    XCTAssertTrue(pattern_.rmatch("aa"));
    
    XCTAssertTrue(pattern_.rmatch("aa"));
    
    XCTAssertTrue(pattern_.rmatch("aaa"));
    
    XCTAssertTrue(pattern_.rmatch("aaaa"));
    
    XCTAssertFalse(pattern_.rmatch("baa"));
    
    XCTAssertFalse(pattern_.rmatch("aab"));
    
    XCTAssertFalse(pattern_.rmatch("b"));
    
    XCTAssertFalse(pattern_.rmatch("bb"));
    
}

- (void)testMatchAlt{
    
    regex::regex pattern_("a*b|cd*");
    
    XCTAssertTrue(pattern_.rmatch("b"));
    
    XCTAssertTrue(pattern_.rmatch("ab"));
    
    XCTAssertTrue(pattern_.rmatch("aab"));
    
    XCTAssertTrue(pattern_.rmatch("c"));
    
    XCTAssertTrue(pattern_.rmatch("cddd"));
    
    XCTAssertFalse(pattern_.rmatch("bc"));
    
    XCTAssertFalse(pattern_.rmatch("aaac"));
    
    XCTAssertFalse(pattern_.rmatch("bddd"));
    
    XCTAssertFalse(pattern_.rmatch("aaaadddd"));
    
    XCTAssertFalse(pattern_.rmatch("abcd"));
    
}

- (void)testMatchSet{
    
    regex::regex pattern_("[abcde]");
    
    XCTAssertTrue(pattern_.rmatch("a"));
    
    XCTAssertTrue(pattern_.rmatch("b"));
    
    XCTAssertTrue(pattern_.rmatch("c"));
    
    XCTAssertTrue(pattern_.rmatch("d"));
    
    XCTAssertTrue(pattern_.rmatch("e"));
    
    XCTAssertFalse(pattern_.rmatch("f"));
    
    XCTAssertFalse(pattern_.rmatch("g"));
    
    XCTAssertFalse(pattern_.rmatch("h"));
    
    XCTAssertFalse(pattern_.rmatch("k"));
    
    XCTAssertFalse(pattern_.rmatch("l"));
    
}

- (void)testMatchtimes1{
    
    regex::regex pattern_("(abc){1,5}");
    
    XCTAssertTrue(pattern_.rmatch("abc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabcabc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch(""));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabcabcabc"));
    
}

- (void)testMatchtimes2{
    
    regex::regex pattern_("(abc){0,4}");
    
    XCTAssertTrue(pattern_.rmatch(""));
    
    XCTAssertTrue(pattern_.rmatch("abc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabcabc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabcabcabc"));
    
}

- (void)testMatchtimes3{
    
    regex::regex pattern_("(abc){5,}");
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabcabc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabcabcabc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabcabcabcabc"));
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabcabcabcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch(""));
    
    XCTAssertFalse(pattern_.rmatch("abc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabc"));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabc"));
    
}

- (void)testGRMatchOneLetter {
    
    regex::regex pattern_;
    
    pattern_.compile("(a)");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("a", match_));
    
    XCTAssertTrue("a" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("", match_));
    
    XCTAssertFalse(pattern_.rmatch("b", match_));
    
    XCTAssertFalse(pattern_.rmatch("ab", match_));
    
    XCTAssertFalse(pattern_.rmatch("ba", match_));
    
    XCTAssertFalse(pattern_.rmatch("aa", match_));
    
}

- (void)testGRMatchKlenee {
    
    regex::regex pattern_;
    
    pattern_.compile("(a*)");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("a", match_));
    
    XCTAssertTrue("a" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aa", match_));
    
    XCTAssertTrue("aa" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaa", match_));
    
    XCTAssertTrue("aaa" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaa", match_));
    
    XCTAssertTrue("aaaa" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaa", match_));
    
    XCTAssertTrue("aaaaa" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("baa", match_));
    
    XCTAssertFalse(pattern_.rmatch("aab", match_));
    
    XCTAssertFalse(pattern_.rmatch("b", match_));
    
    XCTAssertFalse(pattern_.rmatch("bb", match_));
    
}

- (void)testGRMatchAlt{
    
    regex::regex pattern_("(a*b)|(cd*)");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("b", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue(pattern_.rmatch("ab", match_));
    
    XCTAssertTrue("ab" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue(pattern_.rmatch("aab", match_));
    
    XCTAssertTrue("aab" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue(pattern_.rmatch("c", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("c" == match_[2]);
    
    XCTAssertTrue(pattern_.rmatch("cddd", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("cddd" == match_[2]);
    
    XCTAssertFalse(pattern_.rmatch("bc", match_));
    
    XCTAssertFalse(pattern_.rmatch("aaac", match_));
    
    XCTAssertFalse(pattern_.rmatch("bddd", match_));
    
    XCTAssertFalse(pattern_.rmatch("aaaadddd", match_));
    
    XCTAssertFalse(pattern_.rmatch("abcd", match_));
    
}

- (void)testGRMatchSet{
    
    regex::regex pattern_("([abcde])");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("a", match_));
    
    XCTAssertTrue("a" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("b", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("c", match_));
    
    XCTAssertTrue("c" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("d", match_));
    
    XCTAssertTrue("d" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("e", match_));
    
    XCTAssertTrue("e" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("f"));
    
    XCTAssertFalse(pattern_.rmatch("g"));
    
    XCTAssertFalse(pattern_.rmatch("h"));
    
    XCTAssertFalse(pattern_.rmatch("k"));
    
    XCTAssertFalse(pattern_.rmatch("l"));
    
}

- (void)testGRMatchtimes1{
    
    regex::regex pattern_("(abc){1,5}");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("abc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("", match_));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabc", match_));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabc", match_));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabcabc", match_));
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabcabcabc", match_));
    
}

- (void)testGRMatchtimes2{
    
    regex::regex pattern_("(abc){0,4}");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabc", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabc", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabc", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabcabc", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabcabcabcabcabcabc", match_));
    
    XCTAssertTrue("" == match_[1]);
    
}

- (void)testGRMatchtimes3{
    
    regex::regex pattern_("(abc){5,}");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabcabcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("abcabcabcabcabcabcabcabcabc", match_));
    
    XCTAssertTrue("abc" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("abc", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("abcabc", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("abcabcabc", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("abcabcabcabc", match_));
    
    XCTAssertTrue("" == match_[1]);
    
}

- (void)testGRMatchtimes4{
    
    regex::regex pattern_("(a*|b*){1,}");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaabbbbbbbaaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbbbaaaaaaabbbbb", match_));
    
    XCTAssertTrue("bbbbb" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("ababababababababab", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("aaaabbbbcbbabab", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("klf", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("afs", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("fagze", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("GEgErgz", match_));
    
    XCTAssertTrue("" == match_[1]);
    
}

- (void)testGRMatchtimes5{
    
    regex::regex pattern_("(a{2})|(b{3})|(c{4})|(d{5})|(e{6})");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("aa", match_));
    
    XCTAssertTrue("aa" == match_[0]);
    
    XCTAssertTrue("aa" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue("" == match_[3]);
    
    XCTAssertTrue("" == match_[4]);
    
    XCTAssertTrue("" == match_[5]);
    
    XCTAssertTrue(pattern_.rmatch("bbb", match_));
    
    XCTAssertTrue("bbb" == match_[0]);
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("bbb" == match_[2]);
    
    XCTAssertTrue("" == match_[3]);
    
    XCTAssertTrue("" == match_[4]);
    
    XCTAssertTrue("" == match_[5]);
    
    XCTAssertTrue(pattern_.rmatch("cccc", match_));
    
    XCTAssertTrue("cccc" == match_[0]);
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue("cccc" == match_[3]);
    
    XCTAssertTrue("" == match_[4]);
    
    XCTAssertTrue("" == match_[5]);
    
    XCTAssertTrue(pattern_.rmatch("ddddd", match_));
    
    XCTAssertTrue("ddddd" == match_[0]);
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue("" == match_[3]);
    
    XCTAssertTrue("ddddd" == match_[4]);
    
    XCTAssertTrue("" == match_[5]);
    
    XCTAssertTrue(pattern_.rmatch("eeeeee", match_));
    
    XCTAssertTrue("eeeeee" == match_[0]);
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue("" == match_[3]);
    
    XCTAssertTrue("" == match_[4]);
    
    XCTAssertTrue("eeeeee" == match_[5]);
    
    XCTAssertFalse(pattern_.rmatch("a", match_));
    
    XCTAssertTrue("" == match_[0]);
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue("" == match_[3]);
    
    XCTAssertTrue("" == match_[4]);
    
    XCTAssertTrue("" == match_[5]);
    
    XCTAssertFalse(pattern_.rmatch("bb", match_));
    
    XCTAssertTrue("" == match_[0]);
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue("" == match_[3]);
    
    XCTAssertTrue("" == match_[4]);
    
    XCTAssertTrue("" == match_[5]);
    
    XCTAssertFalse(pattern_.rmatch("ccc", match_));
    
    XCTAssertTrue("" == match_[0]);
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue("" == match_[3]);
    
    XCTAssertTrue("" == match_[4]);
    
    XCTAssertTrue("" == match_[5]);
    
    XCTAssertFalse(pattern_.rmatch("dddd", match_));
    
    XCTAssertTrue("" == match_[0]);
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue("" == match_[3]);
    
    XCTAssertTrue("" == match_[4]);
    
    XCTAssertTrue("" == match_[5]);
    
    XCTAssertFalse(pattern_.rmatch("eeeee", match_));
    
    XCTAssertTrue("" == match_[0]);
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertTrue("" == match_[2]);
    
    XCTAssertTrue("" == match_[3]);
    
    XCTAssertTrue("" == match_[4]);
    
    XCTAssertTrue("" == match_[5]);
    
}

- (void)testGRMatchtimes6{
    
    regex::regex pattern_("(a+|b+)+");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaabbbbbbbaaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbbbaaaaaaabbbbb", match_));
    
    XCTAssertTrue("bbbbb" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("ababababababababab", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaabbbbbb", match_));
    
    XCTAssertTrue("bbbbbb" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("aaaabbbbcbbabab", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("klf", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("afs", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("fagze", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("GEgErgz", match_));
    
    XCTAssertTrue("" == match_[1]);
    
}

- (void)testGRMatchtimes7{
    
    regex::regex pattern_("(a?|b?)+");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaabbbbbbbaaaaaaa", match_));
    
    XCTAssertTrue("a" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbbbaaaaaaabbbbb", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("ababababababababab", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaabbbbbb", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("a" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("aaaabbbbcbbabab", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("klf", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("afs", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("fagze", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("GEgErgz", match_));
    
    XCTAssertTrue("" == match_[1]);
    
}

- (void)testGRMatchtimes8{
    
    regex::regex pattern_("((?:$|a)|(?:$|b))+");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaabbbbbbbaaaaaaa", match_));
    
    XCTAssertTrue("a" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbbbaaaaaaabbbbb", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("ababababababababab", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaabbbbbb", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("a" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("aaaabbbbcbbabab", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("klf", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("afs", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("fagze", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("GEgErgz", match_));
    
    XCTAssertTrue("" == match_[1]);
    
}

- (void)testGRMatchtimes9{
    
    regex::regex pattern_("(\\$|\\||\\*|\\+|\\?)");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("$", match_));
    
    XCTAssertTrue("$" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("|", match_));
    
    XCTAssertTrue("|" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("*", match_));
    
    XCTAssertTrue("*" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("+", match_));
    
    XCTAssertTrue("+" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("?", match_));
    
    XCTAssertTrue("?" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch(":", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("\\", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("a", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("b", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("c", match_));
    
    XCTAssertTrue("" == match_[1]);
    
}

- (void)testExeptions{
    
    regex::regex pattern_;
    
    XCTAssertThrows(pattern_.compile("(ab(c)"));
    
    XCTAssertThrows(pattern_.compile("(abc))"));
    
    XCTAssertThrows(pattern_.compile("[abc]]"));
    
    XCTAssertThrows(pattern_.compile("a{1}}"));
    
    XCTAssertThrows(pattern_.compile("a{{1}"));
    
    XCTAssertThrows(pattern_.compile("a{1, 2}"));
    
    XCTAssertThrows(pattern_.compile("a{1 ,3}"));
    
}

- (void)testADDition{
        
    regex::regex add_("(a*|b*){1,}");
    
    regex::regex pattern_ = add_.addition();
    
    XCTAssertFalse(pattern_.rmatch("aaaaaaabbbbbbbaaaaaaa"));
    
    XCTAssertFalse(pattern_.rmatch("bbbbbbaaaaaaabbbbb"));
    
    XCTAssertFalse(pattern_.rmatch("ababababababababab"));
    
    XCTAssertFalse(pattern_.rmatch(""));
    
    XCTAssertFalse(pattern_.rmatch("aaaaaaa"));
    
    XCTAssertTrue(pattern_.rmatch("aaaabbbbcbbabab"));
    
    XCTAssertTrue(pattern_.rmatch("klf"));
    
    XCTAssertTrue(pattern_.rmatch("afs"));
    
    XCTAssertTrue(pattern_.rmatch("fagze"));
    
    XCTAssertTrue(pattern_.rmatch("GEgErgz"));
    
}

- (void)testIntersection1{
    
    regex::regex first_("(a*b*c*d*)*");
    
    regex::regex second_("(e*f*c*d*)*");
    
    regex::regex pattern_ = first_.intersection(second_);
    
    XCTAssertTrue(pattern_.rmatch("cccccc"));
    
    XCTAssertTrue(pattern_.rmatch("dddddd"));
    
    XCTAssertTrue(pattern_.rmatch("cccccddddd"));
    
    XCTAssertTrue(pattern_.rmatch("dddddcccc"));
    
    XCTAssertTrue(pattern_.rmatch("cdcdcdcdcdcdcdc"));
    
    XCTAssertFalse(pattern_.rmatch("cddcdcdcdacdcdcd"));
    
    XCTAssertFalse(pattern_.rmatch("aaaaaaabbbbbb"));
    
    XCTAssertFalse(pattern_.rmatch("eeeeefffff"));
    
    XCTAssertFalse(pattern_.rmatch("abcd"));
    
    XCTAssertFalse(pattern_.rmatch("efcd"));
    
}

- (void)testIntersection2{
    
    regex::regex first_("(a*b*c*d*)*");
    
    regex::regex pattern_ = first_.intersection("(e*f*c*d*)*");
    
    XCTAssertTrue(pattern_.rmatch("cccccc"));
    
    XCTAssertTrue(pattern_.rmatch("dddddd"));
    
    XCTAssertTrue(pattern_.rmatch("cccccddddd"));
    
    XCTAssertTrue(pattern_.rmatch("dddddcccc"));
    
    XCTAssertTrue(pattern_.rmatch("cdcdcdcdcdcdcdc"));
    
    XCTAssertFalse(pattern_.rmatch("cddcdcdcdacdcdcd"));
    
    XCTAssertFalse(pattern_.rmatch("aaaaaaabbbbbb"));
    
    XCTAssertFalse(pattern_.rmatch("eeeeefffff"));
    
    XCTAssertFalse(pattern_.rmatch("abcd"));
    
    XCTAssertFalse(pattern_.rmatch("efcd"));
    
}

- (void)testIntersection3{
    
    regex::regex pattern_ = regex::regex::intersection("(a*b*c*d*)*", "(e*f*c*d*)*");
    
    XCTAssertTrue(pattern_.rmatch("cccccc"));
    
    XCTAssertTrue(pattern_.rmatch("dddddd"));
    
    XCTAssertTrue(pattern_.rmatch("cccccddddd"));
    
    XCTAssertTrue(pattern_.rmatch("dddddcccc"));
    
    XCTAssertTrue(pattern_.rmatch("cdcdcdcdcdcdcdc"));
    
    XCTAssertFalse(pattern_.rmatch("cddcdcdcdacdcdcd"));
    
    XCTAssertFalse(pattern_.rmatch("aaaaaaabbbbbb"));
    
    XCTAssertFalse(pattern_.rmatch("eeeeefffff"));
    
    XCTAssertFalse(pattern_.rmatch("abcd"));
    
    XCTAssertFalse(pattern_.rmatch("efcd"));
    
}

- (void)testCombine1{
    
    regex::regex first_("(a+)");
    
    regex::regex second_("(b+)");
    
    regex::regex pattern_ = first_.combine(second_);
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbb", match_));
    
    XCTAssertTrue("bbbbb" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("b", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbbb", match_));
    
    XCTAssertTrue("bbbbbb" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("aaaabbbbcbbabab", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("klf", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("afs", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("fagze", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("GEgErgz", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    
}

- (void)testCombine2{
    
    regex::regex first_("(a+)");
    
    regex::regex pattern_ = first_.combine("(b+)");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbb", match_));
    
    XCTAssertTrue("bbbbb" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("b", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbbb", match_));
    
    XCTAssertTrue("bbbbbb" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("aaaabbbbcbbabab", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("klf", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("afs", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("fagze", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("GEgErgz", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    
}

- (void)testCombine3{
    
    regex::regex pattern_ = regex::regex::combine("(a+)", "(b+)");
    
    regex::match match_;
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbb", match_));
    
    XCTAssertTrue("bbbbb" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("b", match_));
    
    XCTAssertTrue("b" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("bbbbbb", match_));
    
    XCTAssertTrue("bbbbbb" == match_[1]);
    
    XCTAssertTrue(pattern_.rmatch("aaaaaaa", match_));
    
    XCTAssertTrue("aaaaaaa" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("aaaabbbbcbbabab", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("klf", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("afs", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("fagze", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    XCTAssertFalse(pattern_.rmatch("GEgErgz", match_));
    
    XCTAssertTrue("" == match_[1]);
    
    
}

- (void)testRebirth{
    
    regex::regex first_("abc");
    
    regex::regex second_(first_.rebirth());
    
    XCTAssertTrue(first_ == second_);
    
    first_.compile("abc|def");
    
    second_.compile(first_.rebirth());
    
    XCTAssertTrue(first_ == second_);
    
    first_.compile("abc|def|m+e*p{1,5}h{0,4}(i|klmnop)*");
    
    second_.compile(first_.rebirth());
    
    XCTAssertTrue(first_ == second_);
    
    first_.compile("abc|def|m+e*p{1,5}h{0,4}(i|klmnop)*|($|k)*");
    
    second_.compile(first_.rebirth());
    
    XCTAssertTrue(first_ == second_);
    
}

- (void)testFindAll{
    
    regex::regex pattern_("a*");
    
    std::vector<regex::match> matches_;
    
    XCTAssertTrue(pattern_.findAll("alaalaaalaaaalaaaaa", matches_) == 5);
    
    XCTAssertTrue(matches_[0][0] == "a");
    
    XCTAssertTrue(matches_[1][0] == "aa");
    
    XCTAssertTrue(matches_[2][0] == "aaa");
    
    XCTAssertTrue(matches_[3][0] == "aaaa");
    
    XCTAssertTrue(matches_[4][0] == "aaaaa");
    
    std::string word = "a";
    
    for(auto match_: matches_){
        
        for(auto found_: match_){
            
            XCTAssertTrue(found_ == word);
            
            word += "a";
            
        }
        
    }
    
}

- (void)testGRFindAll{
    
    regex::regex pattern_("(a*)(b*)");
    
    std::vector<regex::match> matches_;
    
    XCTAssertTrue(pattern_.findAllWithGroups("ablaabblaaabbblaaaabbbblaaaaabbbbb", matches_) == 5);
    
    XCTAssertTrue(matches_[0][0] == "ab");
    
    XCTAssertTrue(matches_[1][0] == "aabb");
    
    XCTAssertTrue(matches_[2][0] == "aaabbb");
    
    XCTAssertTrue(matches_[3][0] == "aaaabbbb");
    
    XCTAssertTrue(matches_[4][0] == "aaaaabbbbb");
    
    XCTAssertTrue(matches_[0][1] == "a");
    
    XCTAssertTrue(matches_[1][1] == "aa");
    
    XCTAssertTrue(matches_[2][1] == "aaa");
    
    XCTAssertTrue(matches_[3][1] == "aaaa");
    
    XCTAssertTrue(matches_[4][1] == "aaaaa");
    
    XCTAssertTrue(matches_[0][2] == "b");
    
    XCTAssertTrue(matches_[1][2] == "bb");
    
    XCTAssertTrue(matches_[2][2] == "bbb");
    
    XCTAssertTrue(matches_[3][2] == "bbbb");
    
    XCTAssertTrue(matches_[4][2] == "bbbbb");
    
    std::string word = "ab";
    
    for(auto match_: matches_){
        
        //for(auto found_: match_){
            
            XCTAssertTrue(match_[0] == word);
            
            word = "a" + word + "b";
            
        //}
        
    }
    
}

- (void)testPrint{
    
    regex::regex first_("(a+)");
    
    regex::regex second_("(b+)");
    
    regex::regex combination_ = first_.combine(second_);
    
    regex::regex re_combination_(combination_.rebirth());
    
    regex::regex third_("(a+)|(b+)");
    
    third_.print("hand_made_combo");
    
    re_combination_.print("reborn_reg+reg_combo");
    
    XCTAssertTrue(third_ == re_combination_);
    
}
    
@end
