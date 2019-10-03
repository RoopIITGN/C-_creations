struct node{
    map<char, node *> children;
    bool EndOfWord;
};

node * make_trie(string words[], int n){
    node *root=new node;
    root->EndOfWord=false;
    node *curr=root;
    for(int i=0;i<n;i++){
        curr=root;
        for(int j=0;j<words[i].size();j++){
            if(curr->children.find(words[i][j])==curr->children.end()){
                node *next=new node;
                next->EndOfWord=false;
                curr->children.insert({words[i][j], next});
                curr=next;
            }
            else{
                curr=curr->children.find(words[i][j])->second;
            }
        }
        curr->EndOfWord=true;
    }
    return root;
}

void SearchPrefix(node *head, string key){
    node *curr=head;
    int n=key.size();
    for(int i=0;i<n;i++){
        if(curr->children.find(key[i])==curr->children.end()){
            cout<<"Prefix "<<key<<" not present"<<endl;
            return;
        }
        else{
            curr=curr->children.find(key[i])->second;
        }
    }
    cout<<"Prefix "<<key<<" present"<<endl;
}

void SearchWord(node *head, string word){
    node *curr=head;
    int n=word.size();
    for(int i=0;i<n;i++){
        if(curr->children.find(word[i])==curr->children.end()){
            cout<<"Word "<<word<<" not present"<<endl;
            return;
        }
        else{
            curr=curr->children.find(word[i])->second;
        }
    }
    if(curr->EndOfWord==true){
        cout<<"Word "<<word<<" is present"<<endl;
    }
    else{
        cout<<"Word "<<word<<" not present"<<endl;
    }
    return;
}

int DeleteNode(node *temp, string word, int i){
    if(i==word.size()){
        if(temp->children.empty()){
            temp=NULL;
            free(temp);
            cout<<"Word "<<word<<" was deleted"<<endl;
            return 1; //we can delete this node and check for the upper level node if we can delete them too
        }
        else{
            temp->EndOfWord=false;
            cout<<"Word "<<word<<" was deleted"<<endl;
            return 2; //we cann't delete this node as it's not empty but the word has been successfully delted
        }
    }
    else if(temp->children.find(word[i])==temp->children.end()){
        cout<<"Word "<<word<<" not present"<<endl;
        return 3; //word is not present so we need to return back to DelteWord
    }
    
    else{
        int cond=DeleteNode(temp->children.find(word[i])->second, word, i+1);
        if(cond==1){
            temp->children.erase(word[i]);
            if(temp->children.empty() && temp->EndOfWord==false){
                temp=NULL;
                free(temp);
                return 1;
            }
            else{
                return 2;
            }
        }
        else
            return 2;
    }
}

void DeleteWord(node *head, string word){
    DeleteNode(head, word, 0);
}

void traverse(node *head){
    
    node *curr=head;
    //cout<<"Children of current node: "<<endl;
    for(auto i:curr->children){
        cout<<"i="<<i.first<<endl;
    }
    cout<<"------------------------------"<<endl;
    for(auto i:curr->children){
        cout<<"children of "<<i.first<<endl;
        traverse(i.second);
    }
    if(head->EndOfWord==true){
        cout<<"End of word"<<endl;
    }
    cout<<"------------------------------"<<endl;
}

int main(){
    //cout<<"How many words you want to enter to the dictionary: "<<endl;
    int n;
    cin>>n;
    string words[n];
    //cout<<"Enter the words followed by enter"
    for(int i=0;i<n;i++){
        cin>>words[i]; //sample input(5 abc abgl cdf abcd lmn) separated by line gap.
    }
    node *head;
    head=make_trie(words, n);
    traverse(head);
    SearchPrefix(head, "ab");
    // SearchPrefix(head, "abcdef");
    // SearchPrefix(head, "lo");
    SearchWord(head, "lmn");
    // SearchWord(head, "lmncdf");
    // SearchWord(head, "gh");
    DeleteWord(head, "abcd");
    // DeleteWord(head, "abgl");
    
    traverse(head);
    return 0;
}
