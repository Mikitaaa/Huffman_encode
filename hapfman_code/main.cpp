#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>

struct Node
{
    char simv;
    int freq;
    Node *left, *right;
};

Node* create_Node(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();

    node->simv = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp{
    bool operator()(Node* l, Node* r){
        return l->freq > r->freq;
    }
};


void count_latters(std::map<char,int>& m,std::string& str){
    for(auto &i : str){
        m[i]++;
    }
    //получен массив количества каждой буквы в строке
}

void encode(Node* root, std::string str,std::unordered_map<char, std::string> &code_){
    if (root == nullptr){return;} //нет корня дерева
        
    if (root->left == NULL && root->right == NULL){ //если нашли лист
        code_[root->simv] = str;                    //в дерево code_ по индексу символа из
            return;                                 //текущей ноды дерева кодировки
        }                                           //присвоим строку, которую наклепали по пути рекурсии
    
    encode(root->left,str+'0',code_);
    encode(root->right,str+'1',code_);
}

int main() {
    std::string str="",out_str="";
    getline(std::cin,str);
    std::map<char,int> count;
    std::unordered_map<char,std::string> output_code;
    
    count_latters(count,str);
    
    std::priority_queue<Node*, std::vector<Node*>, comp> output_tree;

    for (auto &it : count) {
        output_tree.push(create_Node(it.first, it.second, nullptr, nullptr));
    }//получили очередь с приоритетом
    
    while (output_tree.size() != 1){
        Node *left = output_tree.top();
        output_tree.pop();
        Node *right = output_tree.top();
        output_tree.pop();

        output_tree.push(create_Node('\0', left->freq + right->freq, left, right));
    }
    //получили дерево
    if(str.size()==1)encode(output_tree.top(),"0",output_code);
    else encode(output_tree.top(),"",output_code);
    
    
    for (char ch : str) {out_str += output_code[ch];}
    
    std::cout<<count.size()<<" "<<out_str.size()<<std::endl;
            
    for(auto &i : output_code){std::cout<<i.first<<": "<< i.second <<std::endl;}
    
    std::cout<<out_str<<std::endl;
}
