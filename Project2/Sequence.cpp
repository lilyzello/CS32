#include "Sequence.h"

//default constructor
Sequence::Sequence(){
    //construct an empty sequence with a dummy node
    //dummy node's next and previous pointers point to itself
    dummy = new Node;
    dummy->previous = dummy;
    dummy->next = dummy;
}

//destructor
Sequence::~Sequence(){
    Node* p = dummy->next; //create a node pointer that points to what dummy's next points to
        while(p!=dummy){    //while the list isn't empty
            Node* n = p;    //create a node pointer n to the item in the sequence
            p = p->next;    //set node point p to the next item
            delete n;       //delete the item
        }
        delete dummy;
}

bool Sequence::empty() const{
    //if dummy node points to itself, list is empty
    if(dummy->next == dummy)
        return true;
    return false;
}

int Sequence::size() const{
    int counter = 0;
    Node* p;
    p = dummy->next;
    while(p!= dummy){ //while you're not at the end of the list
        counter++;    //count the number of items in the list
        p = p->next;
    }
    return counter;
}

int Sequence::insert(int pos, const ItemType& value){
    Node* temp;
    temp = dummy; //create a pointer to the dummy node
    if(pos >= 0 && pos <= size()){ //if the parameters are valid, create a new node with the given value
        Node* newNode = new Node;
        newNode->value = value;
        if(size() == 0){    //if the list is empty, make the dummy node next and prev point to the new Node
            dummy->next = newNode;
            dummy->previous = newNode;
            newNode->next = dummy;  //make the new node next and previous point to the dummy node
            newNode->previous = dummy;
        }else if(pos == 0){ //if you're inserting at the front of the list
            newNode->next = dummy->next; //newNode's next points to what the dummy node's next points to
            newNode->previous = dummy; //newNode's previous points to dummy
            (dummy->next)->previous = newNode; //the node following the newNode points to the newNode
            dummy->next = newNode; //the dummy node's next points to the newNode
        }else{
            for(int i = 0; i<pos; i++){ //temp pointer points to the node at the spot before the given position
                temp = temp->next;
            }
            newNode->next = temp->next; //newNode's next points to the node at the next position
            newNode->previous = temp; //newNode's previous points to the node at the given position
            (temp->next)->previous = newNode; //node at the next position points to the newNode
            temp->next = newNode; //node at the given position points to newNode
        }
        return pos;
    }
    return -1;
}

int Sequence::insert(const ItemType& value){
    int pos = 0;
    if(size() == 0){
        insert(0, value); //if the seq is empty, insert the value at the beginning
        return pos;
    }
    //insert value at the first postion where the value is <= the sequence's value
    for(Node* p = dummy->next; p!= dummy; p=p->next){
        if(value <= p->value){
            insert(pos, value);
            return pos;
        }
        pos++;
    }
    insert(size(), value); //if the value is greater than all the items, insert it at the end
    return pos;
}

bool Sequence::erase(int pos){
    if(0 <= pos && pos < size()){
        Node* temp;
        temp = dummy;
        for(int i = 0; i<=pos; i++){ //get to the given position
            temp = temp->next;
        }
        (temp->previous)->next = temp->next; //previous nodes's next points to the node after the node at the given position
        (temp->next)->previous = temp->previous; //next node's previous points the node before the node at the given position
        delete temp; //delete the node
        return true;
    }
    return false; //returns false it the position is not valid
}

int Sequence::remove(const ItemType& value){
    //erases all nodes with value == given value
    int counter = 0;
        Node* p = dummy->next;
        while (p != dummy) { //while you're not at the end of the list
            if (p->value == value) { //if that node's value == the given value
                Node* next = p->next; //make a pointer to the next node
                Node* previous = p->previous; //make a pointer to the previous node
                next->previous = previous; //set the next node's previous to the be the previous node
                previous->next = next; //set the previous node's next to be the next node
                delete p; //delete the node with the given value
                p = next;
                counter++;
            } else {
                p = p->next;
            }
        }
        return counter; //returns number of nodes erased
}

bool Sequence::get(int pos, ItemType& value) const{
    //get the value at the given position and store it in a variable of item type
    if(0 <= pos && pos < size()){
        Node* temp;
        temp = dummy;
        for(int i = 0; i<=pos; i++){
            temp = temp->next;
        }
        value = temp->value;
        return true;
    }
    return false; //returns false if the position is invalid
}

bool Sequence::set(int pos, const ItemType& value){
    //set the value at the given positon equal to the given value
    if(0 <= pos && pos < size()){
        Node* temp;
        temp = dummy;
        for(int i = 0; i<=pos; i++){
            temp = temp->next;
        }
        temp->value = value;
        return true;
    }
    return false; //returns false if the position is invalid
}

int Sequence::find(const ItemType& value) const{
    //if the value is found, return the position it's at
    //return -1 if the sequence is empty or if the value isn't found
    int pos = 0;
    if(size() == 0){
        return -1;
    }
    for(Node* p = dummy->next; p!= dummy; p=p->next){
        if(value == p->value){
            return pos;
        }
        pos++;
    }
    return -1;
}

void Sequence::swap(Sequence& other){
    //swaps two sequences by swapping the dummy nodes
    //the dummy node's next and previous of the current sequence points to that of the other sequence and vice versa
    Node* temp = dummy;
    this->dummy = other.dummy;
    other.dummy = temp;
}

void Sequence::dump() const{
    for(Node* p = dummy->next; p!= dummy; p=p->next){
        std::cerr << p->value << " ";
    }
    std::cerr << std::endl;
}

//copy constructor
Sequence::Sequence(const Sequence &other){
    //creates a new dummy node that points to itself
    //inserts the items of the other sequence to the new sequence
    dummy = new Node;
    dummy->next = dummy;
    dummy->previous = dummy;
    Node* p = (other.dummy)->next;
    int pos = 0;
    while (p != other.dummy) {
        insert(pos, p->value);
        pos++;
        p = p->next;
    }
}


//assignment operator
Sequence& Sequence::operator=(const Sequence &other){
    //uses copy and swap technique
    //copies other sequence into a temporary sequence
    //swaps this sequence with the temporary sequence
    if(this != &other)
    {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}


//additional functions
int subsequence(const Sequence& seq1, const Sequence& seq2){
    //if seq2 is a subsequence of seq1, returns the position that sequence 2 starts at
    //otherwise returns false
    if(seq1.empty() == 1 || seq2.empty() == 1)
        return -1; //if either sequence is empty, return -1
    ItemType x;
    ItemType y;
    //for each position in sequence 1, check if the sequence begins with sequence2
    //if it doesn't move onto the next sequence
    for(int i = 0; i <= (seq1.size()-seq2.size()); i++){
        for(int j = 0; j<seq2.size(); j++){
            seq1.get(i+j, x);
            seq2.get(j, y);
            if(x!=y){
                break;
            }
           //if all the values in sequence2 are in a row in sequence 1 (sequence2 is a subsequence of sequence 1, return the position that sequence 2 starts at)
            if(j==seq2.size()-1)
                return i;
        }
    }
    return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    //creates a temporary sequence
    //inserts items of seq1 in reverse order into result
    //inserts items of seq2 in reverse order into result
    Sequence temp;
    ItemType x;
    int pos = 0;
    if(seq1.size()>0){
        for(int i = seq1.size()-1; i>=0 ; i--){
            seq1.get(i, x);
            temp.insert(pos, x);
            pos++;
        }
    }
    if(seq2.size()>0){
        for(int i = seq2.size()-1; i>=0 ; i--){
            seq2.get(i, x);
            temp.insert(pos, x);
            pos++;
        }
    }
    result = temp;
}
