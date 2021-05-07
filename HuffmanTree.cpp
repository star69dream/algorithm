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
  
void PrintHuffmanTree(struct MinHeapNode* root, string str)  // print Huffmantree
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << " " << str << "\n";
    PrintHuffmanTree(root->left, str + "0");
    PrintHuffmanTree(root->right, str + "1");
}
  
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
  
void storeCodes(struct MinHeapNode* root, string str)  // utility function to store characters at codes using stl map
{
    if (root==NULL)
        return;
    if (root->data != '$')
        codes[root->data]=str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}
  
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


  
void calcFreq(string str, int n)   // calculate frequency in input string
{
    for (int i=0; i<str.size(); i++)
        freq[str[i]]++;
}
  
int main()
{
    string str1, str2, data_str;
    
    string encodedString, decodedString;
    
	getline(cin, str1); /// input like this               char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	getline(cin, str2);/// input like this               char freq[] = { 5, 9, 12, 13, 16, 45};
	int is_char = 0, is_num = 0, num = 0, cnt = 0, sum = 0, start_num = 0;
	for(int i = 0 ; i < str1.length() ; i ++) {
		if(str1[i] == '\'') {
			if(is_char == 1) is_char = 0;
			else is_char = 1;
		}
		if(is_char == 1 && (str1[i] >= 'a' && str1[i] <= 'z') || (str1[i] >= 'A' && str1[i] <= 'Z')) {
			data_str += str1[i];
		} 
	}	
	for(int i = 0 ; i < str2.length() ; i ++) {
		if(str2[i] == '{') start_num = 1;
		if(str2[i] == '}') {
			freq[data_str[cnt]] = num;
			cnt++;
			sum += num;
			num = 0;
			start_num = 0;
		}
		if(start_num == 1) {
			if(str2[i] == ' ' || str2[i] == '{') {
				is_num = 1;
			}
			if(str2[i] == ',') {
				is_num = 0;	
				freq[data_str[cnt]] = num;
				cnt++;
				sum += num;
				num = 0;
				
			}
		}
		if(is_num == 1 && (str2[i] >= '0' && str2[i] <= '9')) {
			num = num * 10 + (str2[i] - '0');
		}
	}
    buildHuffmanTree(sum);
    PrintHuffmanTree(minHeap.top(), "");
}
