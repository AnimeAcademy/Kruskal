#include "disjoint_sets.h"

//class Node implementation
Node::Node( size_t const& value ) : value(value), next() {}

Node* Node::Next() const { return next; }

void  Node::SetNext( Node* new_next ) { next = new_next; }

size_t Node::Value() const { return value; }

std::ostream& operator<< (std::ostream& os, Node const& node) {
	os << "(" << node.value << " ) -> ";
	return os;
}

//class Head implementation
Head::Head( ) : counter(), first(), last() {} 

Head::~Head() {
	/* .... */
	Node* cur = first;
	while (cur) {
		Node* temp = cur;
		cur = cur->Next();
		delete temp;
	}
	Reset();
}

size_t Head::Size() const      { return counter; }

void   Head::Reset()           { counter = 0; last = first = NULL; }

Node*  Head::GetFirst() const  { return first; }

Node*  Head::GetLast()  const  { return last; }

void   Head::Init( size_t value ) {
	first = last = new Node( value );
	counter = 1;
}

void   Head::Join( Head* pHead2 ) {
	/* .... */
	if (!pHead2 || pHead2->counter == 0)
		return;

	//move p2 to this when this is empty
	if (this->counter == 0) {
		this->first = pHead2->first;
		this->last = pHead2->last;
		this->counter = pHead2->counter;
	}
	else {//add p2 to the end of this and combine
		this->last->SetNext(pHead2->first);
		this->last = pHead2->last;
		this->counter += pHead2->counter;
	}
	//reset the p2
	pHead2->Reset();
	/*pHead2->first = nullptr;
	pHead2->last = nullptr;
	pHead2->counter = 0;*/
}

std::ostream& operator<< (std::ostream& os, Head const& head) {
	os << "[" << head.counter << " ] -> ";
	return os;
}

//class DisjointSets implementation
DisjointSets::DisjointSets( size_t const& capacity ) : 
	size(0),
	capacity(capacity),
	representatives(new size_t[capacity]),
	heads          (new Head[capacity])
{ }

DisjointSets::~DisjointSets() {
	delete [] heads;
	delete [] representatives;
}

void DisjointSets::Make( ) {
	if ( size == capacity ) throw "DisjointSets::Make(...) out of space";
	heads[size].Init( size );
	representatives[size] = size;
	++size;
}

void DisjointSets::Join( size_t const& id1, size_t const& id2 ) {
	/* .... */
	size_t rep1 = GetRepresentative(id1);
	size_t rep2 = GetRepresentative(id2);

	//return if already joined
	if (rep1 == rep2)
		return;
	
	//check to see which head is larger
	size_t smaller;
	size_t bigger;

	if (heads[rep1].Size() > heads[rep2].Size()) {
		smaller = rep2;
		bigger = rep1;
	}
	else {
		smaller = rep1;
		bigger = rep2;
	}

	//Update the represenatives
	for (Node* curr = heads[smaller].GetFirst(); curr != nullptr; curr = curr->Next()) {
		representatives[curr->Value()] = bigger;
	}

	// merge heads
	heads[bigger].Join(&heads[smaller]);
}

size_t DisjointSets::GetRepresentative( size_t const& id ) const {
	return representatives[id];
}

size_t DisjointSets::operator[]( size_t const& id ) const {
	return representatives[id];
}

std::ostream& operator<< (std::ostream& os, DisjointSets const& ds) {
	for (size_t i=0; i<ds.size; ++i ) {
		os << i << ":  ";
		Head *p_head = &ds.heads[i];
		os << *p_head;
		Node* p_node = p_head->GetFirst();
		while ( p_node ) {
			os << *p_node;
			p_node = p_node->Next();
		}
		os << "NULL (representative " << ds.representatives[i] << ")\n";
	}
	return os;
}
