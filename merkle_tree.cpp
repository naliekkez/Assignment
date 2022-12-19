#include <bits/stdc++.h>

using namespace std;

typedef struct node{
	char data[100];
	int value;
	struct node *left, *right;
};



class hashTree{
	
	struct node *merkleRoot;
	
	int hash_function(string s){
		int sum = 0;
		for(int i = 1; i <= s.length();i++){
			sum = sum + (s[i-1]-'a'+1)*i;	
		}
		return sum;
	}	
	struct node*  buildTree(vector< struct node*> nodes){
		
		if(nodes.size()%2 == 1){
			nodes.push_back(nodes[nodes.size()-1]);
		}
		
		struct node *n;
		n = (struct node*) malloc(sizeof(struct node));
		
		string temp("");
		if(nodes.size() == 2){
			n->left = nodes[0];
			n->right = nodes[1];
			temp+=nodes[0]->data;
			temp+=nodes[1]->data;
			strcpy(n->data,temp.c_str());
			n->value = hash_function(temp);
			return n;
		}
		int half_idx = nodes.size()/2;
		
	    vector<struct node*> first_half(nodes.begin(), nodes.begin()+half_idx);
	    vector<struct node*> second_half(nodes.begin()+half_idx,nodes.end());
		n->left =  buildTree(first_half);
		n->right =  buildTree(second_half);
		temp+=n->left->data;
		temp+=n->right->data;
		
		strcpy(n->data,temp.c_str());
		n->value = hash_function(temp);
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
	
	//freopen("file.in","r",stdin); // ini untuk redirect semua input dari file.in ke scanf
	//freopen("file.out","w",stdout); // ini untuk redirect semua printf ke file.out
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
