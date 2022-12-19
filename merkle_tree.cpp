#include <bits/stdc++.h>

using namespace std;

typedef struct node{
	char data[100];
	int value;
	struct node *left, *right;
};



class hashTree{
	
	struct node *merkleRoot;
	// simple hash function which will calculate based on the char and it's position. with position as a magnitude
	int hash_function(string s){
		int sum = 0;
		for(int i = 1; i <= s.length();i++){
			sum = sum + (s[i-1]-'a'+1)*i;	
		}
		return sum;
	}	
	struct node*  buildTree(vector< struct node*> nodes){
		
		if(nodes.size()%2 == 1){ // if the element is not even, we make a duplicate pair.
			nodes.push_back(nodes[nodes.size()-1]);
		}
		
		struct node *n;
		n = (struct node*) malloc(sizeof(struct node));
		
		string temp("");
		if(nodes.size() == 2){ // if there is exactly 2 element, then create a new parent node with those two as it's child
			n->left = nodes[0];
			n->right = nodes[1];
			temp+=nodes[0]->data;
			temp+=nodes[1]->data;
			strcpy(n->data,temp.c_str());
			n->value = hash_function(temp);
			// return the set of the tree (BST)
			return n;
		}
		int half_idx = nodes.size()/2; // if not, divide and conquer, find half point
		
	    vector<struct node*> first_half(nodes.begin(), nodes.begin()+half_idx); // get the first half
	    vector<struct node*> second_half(nodes.begin()+half_idx,nodes.end()); // get the second half
		n->left =  buildTree(first_half); // set the left node with the root from the first half element
		n->right =  buildTree(second_half); // set the left node with the root from the second half element
		temp+=n->left->data; // construct the string data
		temp+=n->right->data; // construct the string data
		
		strcpy(n->data,temp.c_str());
		n->value = hash_function(temp); // construct the hash value based on data.
		return n;
		
	}
	public:
	hashTree(vector<string> elems){
		
		vector< node* > nodes; 
		
		for(vector<string>::iterator t=elems.begin(); t != elems.end();t++ ){
			
			struct node *n;
			n = (struct node*) malloc(sizeof(struct node));
			
			strcpy(n->data,t->c_str());
			n->left = n->right = NULL;
			n->value = hash_function(*t);
			nodes.push_back(n);
		}
		struct node *root;
		merkleRoot = buildTree(nodes);
		for(vector<struct node*>::iterator t=nodes.begin(); t != nodes.end();t++ ){
			free(*t);
		}	
	}
	
	struct node* getMerkleRoot(){
		return merkleRoot;
	}
};

int main(){
	
	vector<string> transactions;
	transactions.push_back("aaa");
	transactions.push_back("bbb");
	transactions.push_back("ccc");
	transactions.push_back("ddd");
	transactions.push_back("eee");
	hashTree tree(transactions);
	struct node *root = tree.getMerkleRoot();
	cout << "Merkle Root Hash: " << root->data << endl;
	cout << "Merkle Root Value: " << root->value << endl;
	
	return 0;
}
