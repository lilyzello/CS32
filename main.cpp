#include <iostream>
using namespace std;
#include "Sequence.h"
#include <cassert>

int main() {
    //default constructor
    Sequence test1; //empty
    Sequence test2; //one item Sequence
    Sequence test3; //multi-item Sequence
    Sequence test4; //ordered mutli-item Sequence

    assert(test1.empty() == 1);
    assert(test1.size() == 0);

    assert(test2.insert("a") == 0);
    assert(test2.size() == 1);
    assert(test2.empty() == 0);

    assert(test3.insert(0, "a") == 0);
    for(int i = 1; i<10 ; i++){
        assert(test3.insert(i, "b") != -1); //should be size 10
    }
    assert(test3.empty() == 0);
    assert(test3.size() == 10);

    assert(test1.erase(0) == 0); //erase on empty seq
    assert(test2.erase(0) == 1); //erase on one item seq
    test2.insert("a"); //to return it to a one item seq
    assert(test2.erase(1) == 0); //out of range call
    assert(test3.erase(10) == 0); //out of range call
    assert(test3.erase(9) == 1); //testing erase function at end of sequence
    assert(test3.size() == 9);

    //testing remove function
    assert(test3.remove("b") == 8);
    assert(test3.remove("a") == 1);
    assert(test3.empty() == 1);
    assert(test3.remove("b") == 0); //remove on empty seq
    assert(test2.remove("a") == 1); //remove for one item seq
    test2.insert("a");

    //testing one parameter insert function
    test4.insert("a");
    assert(test4.insert("b")==1); //make sure ordering works correctly
    test4.insert("c");
    test4.insert("d");
    test4.insert("e");
    assert(test4.insert("f")==5);
    test4.insert("g");

    //testing get function
    string x = "x";
    assert(test4.get(15, x) == 0);
    assert(x == "x");
    assert(test4.get(0, x) == 1); //front of seq
    assert(x == "a");
    assert(test4.get(5, x) == 1); //middle of seq
    assert(x == "f");
    assert(test4.get(6, x) == 1); //end of seq
    assert(x == "g");
    assert(test1.get(0, x) == 0); //empty seq
    assert(test2.get(0, x) == 1); //one item seq
    assert(x == "a");

    //testing set function
    assert(test1.set(0, "b") == 0); //empty seq
    assert(test2.set(0, "b") == 1); //one-item seq
    test2.get(0, x);
    assert(x == "b");
    assert(test4.set(10, "z") == 0); //out of range call
    assert(test4.set(0, "z") == 1); //front of seq
    test4.get(0, x);
    assert(x == "z");
    assert(test4.set(3, "z") == 1); //middle of seq
    test4.get(3, x);
    assert(x == "z");
    assert(test4.set(6, "z") == 1); //end of seq
    test4.get(6, x);
    assert(x == "z");
    assert(test4.set(7, "z") == 0); //out of range

    //testing find function
    assert(test1.find("a") == -1); //empty seq
    assert(test2.find("a") == -1); //item not in seq
    assert(test2.find("b") == 0); //one item seq
    assert(test4.find("z") == 0); //makes sure finds first instance
    test4.insert(7, "x");
    assert(test4.find("x") == 7); //end of seq

    //testing swap function
    test4.swap(test1); //swap w empty seq
    assert(test1.empty() == 0);
    assert(test4.empty() == 1); //test4 is now the empty seq
    test1.swap(test2); //swap w one item seq
    assert(test1.size() == 1); //test1 is now one item seq
    assert(test2.size() == 8); //test2 is now multi-item seq
    assert(test2.find("z") == 0);
    assert(test2.find("x") == 7); //makes sure items are the same
    test2.swap(test2);
    assert(test2.size() == 8); //makes sure swap works if the sequences are the same
    assert(test2.find("x") == 7);

    //copy constructor test
    Sequence test5(test2); //multi item seq
    Sequence test6(test4); //w empty seq
    Sequence test7(test1); //w one-item seq
    assert(test5.size() == 8);
    assert(test5.find("z") == 0); //ensures items were copied correctly
    assert(test6.size() == 0);
    assert(test7.size() == 1);
    test7.get(0,x);
    assert(x == "b"); //esnures items were copied correctly

    //assignment operator tests
    Sequence test8 = test2;
    assert(test8.size() == 8); //multi-item seq
    assert(test8.find("x") == 7);
    test8 = test4; //empty seq
    assert(test8.size() == 0);
    assert(test8.find("x") == -1); //should be no items left in  seq
    test5 = test1; //one-item seq
    assert(test5.size() == 1);
    test5 = test4; //seq w items already
    assert(test5.size() == 0); //ensure all items previously in seq are deleted
    test2 = test2;
    assert(test2.size() == 8); //makes sure assignment operator works with itself

    //concatReverse tests;
    Sequence test9;
    Sequence test10;
    Sequence result;
    test9.insert(0,"a");
    test9.insert(1,"b");
    test9.insert(2,"c");
    test10.insert(0,"d");
    test10.insert(1,"e");
    test10.insert(2,"f");
    concatReverse(test9, test10, result); //tests concatRevrse w multi-item seqs and empty result seq
    assert(result.find("c")==0);
    assert(result.find("b")==1);
    assert(result.find("a")==2);
    assert(result.find("f")==3);
    assert(result.find("e")==4);
    assert(result.find("d")==5);
    concatReverse(test10, test9, result); //tests concatRevrse w multi-item seqs and non-empty result seq
    assert(result.find("f")==0);
    assert(result.find("e")==1);
    assert(result.find("d")==2);
    assert(result.find("c")==3);
    assert(result.find("b")==4);
    assert(result.find("a")==5);
    concatReverse(test10, test4, result); //test w empty seq2
    assert(result.size() == 3);
    assert(result.find("f")==0);
    assert(result.find("e")==1);
    assert(result.find("d")==2);
    concatReverse(test4, test10, result); //test w empty seq1
    assert(result.find("f")==0);
    assert(result.find("e")==1);
    assert(result.find("d")==2);
    concatReverse(result, test9, result); //test when seq1 == result
    assert(result.find("d")==0);
    assert(result.find("e")==1);
    assert(result.find("f")==2);
    assert(result.find("c")==3);
    assert(result.find("b")==4);
    assert(result.find("a")==5);
    concatReverse(test8, test4, result); //test with two empty seqs
    assert(result.empty() == 1);

    //subsequence tests
    Sequence sub1;
    Sequence sub2;
    Sequence sub3;
    sub1.insert("a");
    sub1.insert("b");
    sub1.insert("c");
    sub1.insert("d");
    sub1.insert("e");
    sub1.insert("f");
    sub1.insert(5, "c");
    sub1.insert(6, "d");
    sub2.insert("c");
    sub2.insert("d");
    sub3.insert("a");
    sub3.insert("b");
    assert(subsequence(sub1, sub2) == 2); //middle of seq test
    assert(subsequence(sub1, sub3) == 0); //front of seq
    sub1.erase(3); //gets rid of first d
    assert(subsequence(sub1, sub2) == 4); //ensures first "c" isn't caught by fxn, also end of seq test
    assert(subsequence(sub1, result) == -1); //empty seq test
    assert(subsequence(sub1, test10) == -1); //test for subseq not in main seq

    cout << "everything passed" << endl;
}
