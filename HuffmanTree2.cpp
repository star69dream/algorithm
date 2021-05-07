#include <bits/stdc++.h>
#define MAX_TREE_HT 256
using namespace std;
  
map<char, string> codes;  // to map each character its huffman value
  
map<char, int> freq; // to store the frequency of character of the input data
  
struct MinHeapNode // A Huffman tree node
{
    char data;            
    int freq;             
    MinHeapNode *left, *right; 
  
    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
  
struct compare  // sort operator struct for the priority queue
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};
  
void PrintHuffmanTree(struct MinHeapNode* root, string str) // print Huffmantree
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    PrintHuffmanTree(root->left, str + "0");
    PrintHuffmanTree(root->right, str + "1");
}
  
void storeCodes(struct MinHeapNode* root, string str)  // utility function to store characters at codes using stl map
{
    if (root==NULL)
        return;
    if (root->data != '$')
        codes[root->data]=str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}
  
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
  
void buildHuffmanTree(int size)  // function to build the Huffman tree and store it
{
    struct MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++)
        minHeap.push(new MinHeapNode(v->first, v->second));
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}
  
void calcFreq(string str, int n)  // calculate frequency in input string
{
    for (int i=0; i<str.size(); i++)
        freq[str[i]]++;
}
  
string decode_file(struct MinHeapNode* root, string s)          /// this function is decode function
{
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '0')
           curr = curr->left;
        else
           curr = curr->right;
  
        if (curr->left==NULL and curr->right==NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }
    return ans+'\0';
}

string encode_file(string str)                                         /// this function is encode function
{                          
	string encodedString;
    for (int i = 0; i < str.length() ; i ++)                 
        encodedString+=codes[str[i]];
	return encodedString;	
}
  
int main()
{
    string str;
    
    string encodedString, decodedString;
    
	getline(cin, str);
	
	calcFreq(str, str.length());
    buildHuffmanTree(str.length());
      
  	encodedString = encode_file(str);
    cout << "\nEncoded Huffman data:\n" << encodedString << endl;
  
    decodedString = decode_file(minHeap.top(), encodedString);
    cout << "\nDecoded Huffman Data:\n" << decodedString << endl;
    return 0;
}
