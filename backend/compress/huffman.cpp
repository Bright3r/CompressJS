/**
 * Author: Chase Barman
 * Created: 02/17/2024
 **/

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

using std::string;

class Huffman {
  public:
    string encode(string msg) {
      std::unordered_map<char, string> huffmanCodes = getHuffmanCodes(msg);

      string encodedMsg = "";
      for (char ch : msg) {
        encodedMsg += huffmanCodes[ch];
      }
      
      return encodedMsg;
    } 

    string decode(string encodedMsg, std::unordered_map<char, string> huffmanCodes) {
      string msg = "";

      string currCode = "";
      for (char ch : encodedMsg) {
        currCode += ch;
        if (std::find(huffmanCodes.begin(), huffmanCodes.end(), currCode)) {
          msg += huffmanCodes[currCode];
          currCode = "";
        }
      }

      return msg;
    }

  private:
    struct Node {
      char val;
      int frequency;
      Node left;
      Node right;

      Node(char ch, int freq) {
        val = ch;
        frequency = freq;
      }
    };

    std::unordered_map<char, int> getFrequencyTable(string& msg) { 
      std::unordered_map<char, int> frequencyTable;
      for (const char& ch : msg) {
        frequencyTable[ch]++;
      }

      return frequencyTable;
    }

    Node buildHuffmanTree(string& msg) {
      std::unordered_map<char, int> frequencyTable = getFrequencyTable(msg);

      std::priority_queue<Node> minHeap;
      for (const auto& pair : frequencyTable) {
        Node node(pair.first, pair.second);
        minHeap.push(node);
      }

      while (minHeap.size() > 1) {
        Node node1 = minHeap.top();
        minHeap.pop();
        Node node2 = minHeap.top();
        minHeap.pop();

        Node internalNode('#', node1.frequency + node2.frequency);
        internalNode.left = node1;
        internalNode.right = node2;

        minHeap.push(internalNode);
      }

      return minHeap.top();
    }

    void getHuffmanCodesRecursiveHelper(Node& root, std::unordered_map<char, string>& codes, string currCode) {
      if (!root.left && !root.right) {
        codes[root.val] = currCode; 
        return;
      }

      getHuffmanCodesRecursiveHelper(root.left, codes, currCode + "0");
      getHuffmanCodesRecursiveHelper(root.right, codes, currCode + "1");
    }

    std::unordered_map<char, string> getHuffmanCodes(string& msg) {
      Node huffmanTree = buildHuffmanTree(msg);

      std::unordered_map<char, string> huffmanCodes;
      getHuffmanCodesRecursiveHelper(huffmanTree, huffmanCodes, "");

      return huffmanCodes;
    }
}





int main() {
  std::cout << "Enter Message: ";
  
  string msg;
  std::cin >> msg;

  Huffman encoder;
  string encodedMsg = encoder.encode(msg);
  std::cout << "Your Encoded Message: \n" << encodedMsg;

//  string decodedMsg = encoder.decode(encodedMsg);
//  std::cout << "Your Decoded Message: \n" << decodedMsg;

  return 0;
}
